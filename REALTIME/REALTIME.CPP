
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                     *
 *                       REALTIME CONTROL SYSTEM                       *
 *                       version 1.0                                   *
 *                       by Daniel Green                               *
 *                       Mindscape, Inc.                               *
 *                       December 1995                                 *
 *                                                                     *
 * DESCRIPTION:                                                        *
 *    This implements all the classes as declared in "realtime.h"      *
 *                                                                     *
 * BUGS:                                                               *
 *    Motion weight is not yet implemented                             *
 *                                                                     *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "realtime.h"
#include "vec.h"
#include "viewmath.h"

using namespace std;

// Factors used to weight the factors contributing to the
// percieved benifit of rendering particular LOD objects.
//
// NOTE: These are currently global variables so that they
// can be tuned during testing, but will likely be turned
// into constants by ship time.
// 
double SIZE_WEIGHT        = 1.0;       
double ACCURACY_WEIGHT    = 0.0;   
double SEMANTIC_WEIGHT    = 0.0;   
double FOCUS_WEIGHT       = 0.0;      
double MOTION_WEIGHT      = 0.0;     
double HYSTERESIS_WEIGHT  = 0.0;

double BEST_LIST_SIZE = 50;

static const double BASE_ERROR = 0.5;
static const double SIZE_THRESHOLD_HYSTERESIS = 0.5; // acceptable deviation 

// For debugging
//#include <afx.h>
#define MAX_LOOPS 10
int FrameCount=0, FramesWhichBroke=0;
int TotalLoops=0;
double AverageLoops;

#ifndef ABS_VAL
#	define ABS_VAL(a) (((a) > 0) ? (a) : -(a))
#endif
#define IN_RANGE(val, low, high) ((low) <= (val) && (val) <= (high))


/*
	The following contains private implementation data types used
	by the RealtimeView class.
*/

struct LODChoice {
	LODChoice(){}
	LODChoice(double v, double t, const ROI *r, int w, int lw):
			value(v), render_time(t), roi(r), which(w), last_which(lw) {}
	double value;
	double render_time;
	const ROI *roi;
	int which;
	int last_which;
};

template <class Compare>
class LODChoiceQueue : public priority_queue<vector<const LODChoice*>, Compare>
{
public:
	LODChoiceQueue() {}
	void erase(const LODChoice* pLODChoice)
	{
		c.erase(find(c.begin(), c.end(), pLODChoice));
		make_heap(c.begin(), c.end(), comp);
	}
	// Iterators for peeking at the entries.
	// Note: doesn't iterate in sorted order
	typedef vector<const LODChoice*>::const_iterator const_iterator;
	const_iterator begin() { return c.begin(); }
	const_iterator end() { return c.end(); }
};

struct LODChoiceLess
{
	bool operator() (const LODChoice* pLODChoice1, const LODChoice* pLODChoice2) const
	{
		return pLODChoice2->value < pLODChoice1->value;
	}
};

struct LODChoiceGreater
{
	bool operator() (const LODChoice* pLODChoice1, const LODChoice* pLODChoice2) const
	{
		return pLODChoice2->value > pLODChoice1->value;
	}
};

typedef LODChoiceQueue< LODChoiceGreater > BigChoiceFirst;


/*
 * Implementation of Realtime classes
 */

RealtimeView::RealtimeView(const ROI &r): scene(r)
{
	pov_source = 0;
	view_angle = 45;
	front = -.1;
	back = -500;
	eye_sep = 0;
	width = 400;
	height = 400;
	position[0] = 0; position[1] = 0; position[2] = 0;
	direction[0] = 0; direction[1] = 0; direction[2] = 1;
	up[0] = 0; up[1] = 1; up[2] = 0;  // positive Y is up by default
	persp_data_dirty = 1;
	cost_adjustment = 1.0;
	seconds_expected_last_frame = 0.01; // must be non-zero
	maxed_last_frame = false;

	s = new LittleChoiceFirst;
	last_s = new ROI2Choice;
}

RealtimeView::~RealtimeView()
{
	if(s)
		delete s;
	if(last_s)
		delete last_s;
}


void RealtimeView::SetPOVSource(const OrientableROI *obj)
{
	pov_source = obj;
}

void RealtimeView::SetFOV(double deg, double neer, double phar)
{
	if(
		view_angle != deg ||
		front != neer     ||
		back != phar)
	{
		view_angle = deg;
		front = neer;
		back = phar;
		persp_data_dirty = 1;
	}
}

void RealtimeView::SetResolution(int w, int h)
{
	if(
		width  != w ||
		height != h)
	{
		width = w;
		height = h;
		persp_data_dirty = 1;
	}
}

BoxVisibility RealtimeView::BoxVisible(const BoundingBox &box) const
{
	((RealtimeView*)this)->update_viewing_data();
	return box_visible(box);
}

BoxVisibility RealtimeView::box_visible(const BoundingBox &box) const
{
	ViewIntersectionType result = test_box_intersect_view(
			(double*)&box.Min(),
			(double*)&box.Max(),
			ARRAY3 view_box);
	switch(result) {
		case HEXA_OUTSIDE:
			return BOX_OUTSIDE;
		case HEXA_CONTAINS_BOX:
			return BOX_CONTAINED;
		default:
			return BOX_INTERSECTS;
	}
}


bool RealtimeView::inside_roi(const ROI *roi) const
{
	const Vector3 &roi_min = roi->GetWorldBoundingBox().Min();
	const Vector3 &roi_max = roi->GetWorldBoundingBox().Max();
	if(
		IN_RANGE(position[0], roi_min[0], roi_max[0]) &&
		IN_RANGE(position[1], roi_min[1], roi_max[1]) &&
		IN_RANGE(position[2], roi_min[2], roi_max[2]))
	{
		return true;
	}
	return false;
}


double RealtimeView::ProjectedSize(const BoundingSphere &sphere) const
{
	((RealtimeView*)this)->update_viewing_data();
	return projected_size(sphere);
}


// Returns the fraction of the view covered by the given sphere.
// E.G.: returns 0.5 if the sphere covers half the pixels.
//
double RealtimeView::projected_size(const BoundingSphere &sphere) const
{
	// The algorithm projects the radius of bounding sphere onto the perpendicular
	// plane one unit in front of the camera. That value is simply the ratio of the
	// radius to the distance from the camera to the sphere center. The projected size
	// is then the ratio of the area of that projected circle to the view surface area
	// at Z == 1.0.
	//
	double sphere_projected_area = M_PI * SQR(sphere.Radius());
	double square_dist_to_sphere = DISTSQRD3(sphere.Center(), position);
	return sphere_projected_area / view_area_at_one / square_dist_to_sphere;
}


// Traverses an ROI tree rooted at "from" and returns a set of visible ROIs.
// Recursion terminates at and returns leaf nodes encountered of course,
// but is also terminated early (i.e. is pruned) at nodes whose projected
// sizes are smaller than the given threshold and which have LODs.
// Returns "true" if any such early pruning was done, "false" otherwise.
//
bool RealtimeView::GetVisibleObjects(
		const ROI *from,
		ROIList &into,
		double size_threshold,
		bool known_totally_contained) const
{
	((RealtimeView*)this)->update_viewing_data();
	return get_visible_objects(from, into, size_threshold, known_totally_contained);
}

bool RealtimeView::get_visible_objects(
		const ROI *from,
		ROIList &into,
		double size_threshold,
		bool known_totally_contained) const
{
	assert(from);

	if( ! known_totally_contained) {
		BoxVisibility visibility = box_visible(from->GetWorldBoundingBox());
		if(BOX_OUTSIDE == visibility) // prune away invisible branches
			return false;
		if(BOX_CONTAINED == visibility)
			known_totally_contained = true; // now known to be contained
	}

	const CompoundObject *co = from->GetComp();
	bool has_lods = from->GetLODs() != NULL && from->GetLODCount() > 0; 

	// if there is no compound version for this ROI we've recursed to
	// a leaf node therefore add this object to the list (only if it
	// has any LODs), and return false.
	//
	if(!co) {
		if(has_lods)
			into.insert(into.end(), from);
		return false;
	}

	// if the given ROI object has LODs, is not inside the object, and its
	// size is smaller than the given threshold, terminate recursion and add
	// it to the given list.
	// Note that the logic for this test is in the form of cascading "if"
	// statements for effeciency.
	//

	if(has_lods) {
		if( ! inside_roi(from)) {
			double size_in_view = projected_size(from->GetWorldBoundingSphere()); 
			if(size_in_view < size_threshold)
			{
				into.insert(into.end(), from);
				return true;
			}
		}
	}

	// A compound version exists and will be used.
	// This loop recurses into each part and returns true if any
	// of the parts also does. That signifies that somewhere lower down,
	// a node was pruned.
	//
	bool size_pruned = false;
	WALK_STL_OBJECT(*co, CompoundObject, ci)
		if(get_visible_objects(*ci, into, size_threshold,
			known_totally_contained))
		{
			size_pruned = true;
		}

	return size_pruned;
}


double RealtimeView::apparent_speed(const ROI *roi) const
{
	return 0.0; // stubbed for testing
}


static inline void project_vector_onto_plane(Vector3 &vec, const Vector3 &plane_nrm)
{
	double frac = DOT3(vec, plane_nrm) / NORMSQRD3(plane_nrm);
	Vector3 component_along_nrm;
	VXS3(component_along_nrm, plane_nrm, frac);
	VMV3(vec, vec, component_along_nrm);
}

// Fills in the "render_time" and "value" fields of the given choice
//
void RealtimeView::calculate_values(LODChoice &choice) const
{
	double view_fraction_covered = projected_size(choice.roi->GetWorldBoundingSphere());
	double pixels_covered = view_fraction_covered * SQR(width);
	if(pixels_covered > view_pixels)
		pixels_covered = view_pixels; // clamped to keep factor between 0 and 1
	const LODObject *lod = choice.roi->GetLOD(choice.which);
	choice.render_time = lod->Cost(pixels_covered) * cost_adjustment;
	double n_vertices = lod->NVerts();
	Vector3 to_object;
	VMV3(to_object, choice.roi->GetWorldBoundingSphere().Center(), position);
	project_vector_onto_plane(to_object, up); // makes angle independant of vertical component
	double cos_angle = DOT3(direction, to_object) / sqrt(NORMSQRD3(to_object));
	double angle_to_object = acos(cos_angle); // Note: may want to casche this
	double object_speed = apparent_speed(choice.roi);
	double ave_poly_size = lod->AveragePolyArea();
	double n_lod_changes = ABS_VAL(choice.last_which - choice.which);
	if(-1 == choice.last_which)
		n_lod_changes = 0; // should be no additional penalty for newly visible ROIs
	double total_lods = choice.roi->GetLODCount();
	double benifit =
		SIZE_WEIGHT       * (pixels_covered / view_pixels)      +  // bigger is better
		ACCURACY_WEIGHT   * (1.0 - BASE_ERROR/SQR(n_vertices))  +  // more detail is better
		SEMANTIC_WEIGHT   * (choice.roi->IntrinsicImportance()) +  // more important is better
		FOCUS_WEIGHT      * (1.0 - (angle_to_object/M_PI))      +  // more centered is better
		MOTION_WEIGHT     * (object_speed / ave_poly_size)      +  // slower is better
		HYSTERESIS_WEIGHT * (1.0 - (n_lod_changes / total_lods));  // less change is better
	choice.value = benifit / choice.render_time;
}


#define HASH_CHOICE(roi, index) ((unsigned long)(roi) * ((index)+3))
	

const LODChoice* RealtimeView::add_choice(const ROI* roi, int which, int last_which,
								   Pair2Choice &store) const
{
	const LODObject* pLODObject = roi->GetLOD(which);
	LODChoice choice(1, 0, roi, which, last_which);
	calculate_values(choice);
	Pair2Choice::value_type val(HASH_CHOICE(roi, which), choice);
	Pair2Choice::const_iterator	pi = store.insert(val).first;
	const Pair2Choice::value_type& mapEntry = *pi;
	unsigned long key = mapEntry.first;
	const LODChoice& stored_choice = mapEntry.second;

	// Make sure there was no hash collision
	//
	assert(stored_choice.which == which);
	assert(stored_choice.roi == roi);

	return &stored_choice;
}


// Either finds and returns an LODChoice from the given store,
// or creates and returns a new one. When a new LODChoice was created
// it is also added to the given store as a side-effect.
// On completion, the bool* argument (if non-NULL) will contain "true"
// if a new LODChoice was created, "false" otherwise.
//
const LODChoice* RealtimeView::get_choice(const ROI* roi, int which, int last_which,
				Pair2Choice& store, bool* new_choice) const
{
	assert(which >= 0);
	const LODObject *lod = roi->GetLOD(which);
	Pair2Choice::const_iterator pi = store.find(HASH_CHOICE(roi, which));
	if(pi != store.end())
	{
		const Pair2Choice::value_type& mapEntry= *pi;
		unsigned long key = mapEntry.first;
		const LODChoice& stored_choice = mapEntry.second;
		assert(stored_choice.roi == roi);
		assert(stored_choice.which == which);
		if(new_choice)
			*new_choice = false;
		return &stored_choice;
	}
	else
	{
		const LODChoice* pLODChoice = add_choice(roi, which, last_which, store);
		if(new_choice)
			*new_choice = true;
		return pLODChoice;
	}
}


// The RealtimeView::SelectLODs method (or the internal "select_lods" method
// it calls) is the heart of the real-time control system. Except for the first
// step which attempts to tune the visible object selection functionality,
// this is a direct implementation of the optimization algorithm described in
// the SIGGRAPH '93 paper by Funkhouser and Sequin.

void RealtimeView::SelectLODs(double seconds_allowed, double seconds_used_last_frame,
		ROIList &draw_list, IntList &which_lods) const
{
	((RealtimeView*)this)->update_viewing_data();
	select_lods(seconds_allowed, seconds_used_last_frame, draw_list, which_lods);
}

void RealtimeView::select_lods(double seconds_allowed, double seconds_used_last_frame,
		ROIList &draw_list, IntList &which_lods) const
{
	static double size_thresh = 0.01; // initial value should come from registry
	double total_seconds = 0.0;	// running total expected rendering time
	Pair2Choice choices; // all possible lod choices as they become known
	BigChoiceFirst nexts; // valid next lod choices

	if(0 == draw_list.size()) { // caller wants us to select visible objects
		bool size_pruned = get_visible_objects(&scene, draw_list, size_thresh, false);
		// Use what we learned this time to set size threshold for next time
		// Might also want to scale resulting threshold larger when too many
		// visible objects end up with no LODs being selected. This would
		// increase likelyhood of their parent being chosen instead. Other
		// possible strateies include explicitly taking a parent to avoid that.
		int n_selected = draw_list.size();
		bool got_too_many = n_selected > (BEST_LIST_SIZE / SIZE_THRESHOLD_HYSTERESIS); 
		bool got_too_few  = n_selected < (BEST_LIST_SIZE * SIZE_THRESHOLD_HYSTERESIS); 
		if(n_selected &&  // to avoid scaling threshold to zero
			(got_too_many || (got_too_few && size_pruned ))) // needs adjustment
		{
			size_thresh *= n_selected / BEST_LIST_SIZE;
		}
	}
	int ndraw = draw_list.size(); // for debugging

/*
// for viewing under the debugger:
const LODChoice* dc[50][10];
{
	int roi=0;
	WALK_STL_OBJECT(draw_list, ROIList, di)
	{
		for(int i=0; i<(*di)->GetLODCount(); i++)
			dc[roi][i] = get_choice(*di, i, -1, choices);
		roi++;
	}
	roi = roi;
}
*/

	// A seconds_used_last_frame value of 0.0 signifies that there really
	// was no last frame in the animation sequence about to begin.
	// Another reason to pass a zero would be because the caller chose not to
	// use the objects selected last frame.
	//
	if(seconds_used_last_frame < 0.01)
		seconds_used_last_frame = seconds_expected_last_frame;

	// Must beware of empty views which have zero expected costs
	//
	if(seconds_expected_last_frame < 0.01)
		((RealtimeView*)this)->seconds_expected_last_frame = seconds_used_last_frame = 0.1;
	
	// Tune the "cost_adjustment" member used to scale incoming cost values
	// in order to better fit the expected frame rates. The assumption is that
	// the any amount that the actual rendering time is different from the
	// expected amount is due to inaccurate LOD cost estimates.
	//
	double overage_last_frame =
		(seconds_expected_last_frame * 10 + seconds_used_last_frame) / 
		(11. * seconds_expected_last_frame);
	bool under_budget = overage_last_frame < 1.0;
	if( ! (under_budget && maxed_last_frame))
		//&& (overage_last_frame < 0.8 || 1.2 < overage_last_frame))
	{
		((RealtimeView*)this)->cost_adjustment *= overage_last_frame;
	}

	// Build "s" which is the set of visible ROIs and their LOD choices.
	// Initially s is empty. Also build "nexts" which is the set of
	// choices available which are the next most complex LOD versions
	// for all choices in "s" which are not already at their max LOD.
	// "s" and "nexts" are priority queues kept sorted by overall value
	// where "s" is sorted with the least valuable at the top, and "nexts"
	// keeps the most valuable at the top. All the choice objects are
	// stored in an LOD-to-choice map called "choices" which grows with
	// each unique choice being examined. "s" and "nexts" only store
	// pointers to those choices.

	// Step 1 (initialization):
	// for each visible object, add it to s along with an initial LOD choice
	// which is either the choice used the last time if it was visible last
	// time, or its lowest LOD otherwise. "last_s" contains all the ROIs
	// and the LOD choices they used last time.
	//
	WALK_STL_OBJECT(draw_list, ROIList, vi)
	{
		const ROI *roi = *vi;

		// Make sure there is at least one valid choice for this ROI
		//
		if(0 == roi->GetLODCount())
			continue;

		// Pick an initial choice of LOD for this ROI.
		// If this ROI wasn't drawn last time,
		// start with the lowest (ID == 0) LOD,
		// otherwise start with the same LOD as was used
		// last time (assuming it's still available).
		//
		const LODChoice *starting_choice;
		ROI2Choice::const_iterator li = last_s->find(roi);
		if(li == last_s->end())
			starting_choice = get_choice(roi, 0, -1, choices);
		else {
			int last_which = (*li).second.which;
			if(last_which >= roi->GetLODCount()) // if no longer available,
				last_which = roi->GetLODCount() - 1; // use current highest
			starting_choice = get_choice(roi, last_which, last_which, choices);
			// NOTE: the third argument above might better be the real
			// last_which regardless of whether it's still available.
		}

		// save a pointer to initial choice in "s"
		// and update the total_time accumulator.
		//
		s->push(starting_choice);
		total_seconds += starting_choice->render_time;

		// if there exists a next higher LOD version of each initial choice,
		// add it to the "nexts" queue.
		int next_id = starting_choice->which + 1;
		if(next_id < roi->GetLODCount()) { // has a next version
			const LODChoice *next_choice = get_choice(roi, next_id,
				starting_choice->last_which, choices);
			nexts.push(next_choice); // save reference to next higher LOD
		}

		int nstartingchoices = choices.size(); // for debugging
	}
	// We're now done with draw_list, the saved IDs and the
	// choices from last time, so empty them all.
	//
	draw_list.erase(draw_list.begin(), draw_list.end());
	which_lods.erase(which_lods.begin(), which_lods.end());
	last_s->erase(last_s->begin(), last_s->end()); // done with saved list from last time.

    // Step 2 (optimization):
	// Calculate the best set of LOD indicies for all objects in the set
	//
	int loop_count = 0; // for emergency break
	const ROI *high=NULL, *low=NULL;
	do {
		int new_id;
		loop_count++;
		if(loop_count >= MAX_LOOPS) {
			if(0 == FramesWhichBroke) // first time
				//TRACE("emergency brake engaged\n");
			FramesWhichBroke++;
			break;
		}

		// increment highest valued choice that has a next one
		//
		int nnexts = nexts.size(); // for debugging
		if(nexts.size()) { // will be 0 when using highest LODs for all objects
			const LODChoice *high_choice = nexts.top();
			high = high_choice->roi;  // the ROI being incremented
			int current_id = high_choice->which - 1;
			if(current_id >= 0) {
				// a previous choice for this ROI is currently being used.
				// remove it from "s" and update the total_time accumulator.
				//
				bool new_choice;
				const LODChoice *current_choice = get_choice(high,
					current_id, high_choice->last_which, choices, &new_choice);
				assert( ! new_choice);
				s->erase(current_choice);
				total_seconds -= current_choice->render_time;
			}
			// add the chosen "next" choice to "s"
			// and update the total_time accumulator.
			//
			s->push(high_choice);
			total_seconds += high_choice->render_time;

			// remove the chosen one from "nexts" and add *its* next one
			// if it has one.
			//
			nexts.pop(); // remove highest valued choice from list
			int n_lods = high->GetLODCount(); // number of LODs for this ROI
			new_id = high_choice->which + 1;
			if(new_id < n_lods) { // an even higher LOD so save it in "nexts"
				const LODChoice *new_next_choice =
					get_choice(high, new_id, high_choice->last_which, choices);
				nexts.push(new_next_choice);
			}
		}
		
		// decrement lowest valued choice until within overall budget.
		// Note that it is allowed to remove even the lowest LOD and
		// draw nothing instead if that's what it takes to stay under
		// budget.
		//
		while(total_seconds > seconds_allowed) {
			if(0 == s->size())
				break; // looking into empty space or all LODs are over budget
			int ns = s->size(); // for debugging
			const LODChoice *low_choice = s->top();
			low = low_choice->roi;  // the ROI being decremented

			// remove lowest valued choice from list
			//
			s->pop();
			total_seconds -= low_choice->render_time;
			int n_lods = low->GetLODCount(); // number of LODs for this ROI
			new_id = low_choice->which - 1;
			if(new_id >= 0) { // the new lower LOD exists so save it in "s"
				const LODChoice *new_choice =
					get_choice(low, new_id, low_choice->last_which, choices);
				s->push(new_choice);
				total_seconds += new_choice->render_time;
			}

			// decrement its "next" LOD too (if it exists) and make the
			// choice being decremented *be* the new next value.
			//
			int old_next_id = low_choice->which + 1;
			if(old_next_id < n_lods) {
				bool new_choice;
				const LODChoice *nexts_next = get_choice(low,
					old_next_id, low_choice->last_which, choices, &new_choice);
				assert( ! new_choice);
				nexts.erase(nexts_next);
			}
			nexts.push(low_choice);
		}
	} while(high != low && nexts.size()); // raising and lowering same ROI == convergence

	// Some debugging statistics
	//
	if(loop_count < MAX_LOOPS) {
		FrameCount++;
		TotalLoops += loop_count;
		AverageLoops = (double)TotalLoops / FrameCount;
	}

//int will_draw[50], w=0; // for viewing under the debugger
	
	// Step 3:
	// Return the draw_list set and calculated LOD indicies
	// while saving their choice data for next time.
	//
	for(int n_to_save = s->size(); n_to_save > 0; --n_to_save)
	{
		const LODChoice *to_save = s->top();
		draw_list.push_back(to_save->roi); // so the big ones end up last in list
		which_lods.push_back(to_save->which); // index that matches ROI above
//will_draw[w++] = to_save->which; // for viewing under the debugger
		ROI2Choice::value_type val(to_save->roi, *to_save);
		last_s->insert(val).first;	// save for next time
		s->pop();
	}
	int n_to_draw = draw_list.size(); // for debugging only
 	// s is now also empty for next time

	// remember the estimated time to render the selected objects
	// so that we can compare next time with how we really did for tuning.
	//
	((RealtimeView*)this)->seconds_expected_last_frame = total_seconds;

	// If all final choices took their highest LOD versions,
	// then the "nexts" queue will be empty. We need to remember
	// this fact for next time.
	//
	((RealtimeView*)this)->maxed_last_frame = (0 == nexts.size());
}

void RealtimeView::update_viewing_data()
{
	int persp_was_dirty = persp_data_dirty;

	if(persp_data_dirty) {
		// compute and store projection dependant data
		//
		persp_data_dirty = 0;
		persp_was_dirty = 1;
		view_pixels = width * height;
		build_perspective_mat(persp, width, height, front, back);
		tan_half_angle = tan(DTOR(view_angle) / 2.0);
		double view_width_at_one = 2 * tan_half_angle;
		view_area_at_one = SQR(view_width_at_one);
	}

	if( ! pov_source)
		return;

	// Get the current camera data
	//
	int camera_changed = 0;
	const double* src_pos = pov_source->GetWorldPosition();
	const double* src_dir = pov_source->GetWorldDirection();
	const double* src_up = pov_source->GetWorldUp();

	// ??? either do not normalize and save
	//     or normalize before compare
	if(
		! EQVEC3(position, src_pos) ||
		! EQVEC3(direction, src_dir) ||
		! EQVEC3(up, src_up))
	{
		// The camera moved	since last time.
		// Save the new values, and compute camera matricies
		//
		camera_changed = 1;
		SET3(position, src_pos);	 // copy the new position
		NORMALIZE_VEC3(direction, src_dir)	 // normalize and copy new dir
		NORMALIZE_VEC3(up, src_up);		 // normalize and copy new up
		Vector3 new_x, new_y;
		VXV3(new_x, up, direction);
		NORMALIZE_VEC3(new_x, new_x);
		VXV3(new_y, direction, new_x);
		NORMALIZE_VEC3(new_y, new_y);
		SET4from3(cam_xfm[0], new_x,     0);
		SET4from3(cam_xfm[1], new_y,     0);
		SET4from3(cam_xfm[2], direction, 0); // dir becomes new Z axis
		SET4from3(cam_xfm[3], position,  1);
		INVERTMAT4d(cam_inv, cam_xfm);
		MXM4(wcs_to_npc, cam_inv, persp);
	}

	// If any setting changed, compute new world-space viewbox corners
	//
	if(persp_was_dirty || camera_changed) {
		double cam_trans[4][4];
		TRANSPOSE4(cam_trans, cam_xfm);	 // view math expects column vectors
		double ratio = (double)width/height;
		double narrow_angle =
			RTOD(atan(tan(DTOR(view_angle)) * (width > height) ? 1.0/ratio : ratio));
		get_persp_view_corners(view_box,
			ARRAY4 cam_trans,
			width > height ? view_angle : narrow_angle,
			width > height ? narrow_angle : view_angle,
			front, back);
	}
}

