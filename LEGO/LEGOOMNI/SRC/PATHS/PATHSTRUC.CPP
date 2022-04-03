/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"

#include "PathStruc.h"
#include "LegoSpacePresenter.h"

#include "float.h"

LegoPathLink::LegoPathLink()
{
	m_id = NOT_A_PATHLINK;
	m_nodes = NULL;
	m_numNodes = 0;
	m_corridors = NULL;
	m_numCorridors = 0;
}

LegoPathLink::~LegoPathLink()
{
	if(m_nodes)
		delete [] m_nodes;
	m_nodes = NULL;
	if(m_corridors)
		delete [] m_corridors;
	m_corridors = NULL;
}

void LegoPathLink::SetNodes(LegoPathNodePtr * p_nodes, MxS32 p_numNodes)
{
	// Base link type will be always be attached to exactly two nodes
	m_nodes = new LegoPathNodePtr[p_numNodes];
	if(!m_nodes) return;
	
	for(int i=0; i<p_numNodes; i++)
		m_nodes[i] = p_nodes[i]; 
	m_numNodes = p_numNodes;

	// Calculate link length and link and corridor direction vectors
	m_vector = m_nodes[1]->GetLocation();
	m_vector -= m_nodes[0]->GetLocation();

	m_length = m_vector.Magnitude();
	m_vector /= m_length;
	
	// temporary hard-coded upVector
	m_upVector.SetX(0.0);
	m_upVector.SetY(1.0);
	m_upVector.SetZ(0.0);

	// m_outVector = m_vector X m_upVector
	// when facing in the direction of m_vector the out vector is positive to the right
	m_outVector.SetX((m_vector.GetY()*m_upVector.GetZ() - m_vector.GetZ()*m_upVector.GetY()));
	m_outVector.SetY((m_vector.GetZ()*m_upVector.GetX() - m_vector.GetX()*m_upVector.GetZ()));
	m_outVector.SetZ((m_vector.GetX()*m_upVector.GetY() - m_vector.GetY()*m_upVector.GetX()));
	m_outVector *= CORRIDOR_HANDEDNESS;
}

void LegoPathLink::SetCorridors(LegoCorridorPtr * p_corridors, MxS32 p_numCorridors)
{
	m_corridors = new LegoCorridorPtr[p_numCorridors];
	if(!m_corridors) return;
	
	for(int i=0; i<p_numCorridors; i++)
		m_corridors[i] = p_corridors[i]; 
	m_numCorridors = p_numCorridors;
}

void LegoPathNode::SetLinks(LegoPathLinkPtr * p_links, MxS32 p_numLinks)
{
	m_links = new LegoPathLinkPtr[p_numLinks];
	if(!m_links) return;
	
	for(int i=0; i<p_numLinks; i++)
		m_links[i] = p_links[i]; 
	m_numLinks = p_numLinks;
}

LegoPathNode::LegoPathNode()
{
	m_id = NOT_A_PATHNODE;
	m_links = NULL;
	m_numLinks = 0;
	m_location = Mx3DPointDouble(0,0,0);
}

LegoPathNode::~LegoPathNode()
{
	if(m_links)
		delete [] m_links;
	m_links = NULL;
}

MxBool LegoPathLink::SelectCorridor(MxS32 p_direction, MxS32 p_type, LegoCorridorPtr & p_corridorPtr)
{
	MxBool result = FALSE;
	p_corridorPtr = NULL;

	MxU32 admissionFlags;
	if(p_direction >= 0)
		admissionFlags = PATH_DIRECTION_FORWARD;
	else if(p_direction < 0)
		admissionFlags = PATH_DIRECTION_BACKWARD;
	admissionFlags |= p_type;
	if(admissionFlags & PATH_PRIVILEGE_BITS)
	{   // first try privileged corridors if this presenter has any privilege bits
		for(int i=0; i<m_numCorridors && !result; i++)
		{
			LegoCorridorPtr corridor = m_corridors[i];
			MxU32 corridorFlags = corridor->GetAdmissionFlags();
			// If corridor requires a special privilege, make sure we have it first.
			// We can ignore these bits if none are set for the corridor.  
			// This is a little different from the other admission flags which
			// must always have at least one matching bit in each group.
			// Having any one of the privilege bits is sufficient.   
			if(corridorFlags & PATH_PRIVILEGE_BITS & admissionFlags)
			{
				admissionFlags &= ~PATH_PRIVILEGE_BITS; // done with these bits
				// Are all of the remaining bits set in admissionFlags 
				// also set for the corridor?  Ie. is the traveler
				// in an acceptable direction and is it an acceptable 
				// traveler type
				if((corridorFlags & admissionFlags) == admissionFlags) 
				{
					p_corridorPtr = corridor;
					result = TRUE;
				}
			}
		}
		admissionFlags &= ~PATH_PRIVILEGE_BITS; // done with these bits
	}
	for(int i=0; i<m_numCorridors && !result; i++)
	{
		LegoCorridorPtr corridor = m_corridors[i];
		MxU32 corridorFlags = corridor->GetAdmissionFlags();
		// If corridor requires a special privilege, make sure we have it first.
		// We can ignore these bits if none are set for the corridor.  
		// This is a little different from the other admission flags which
		// must always have at least one matching bit in each group.
		// Having any one of the privilege bits is sufficient.   
		if(corridorFlags & PATH_PRIVILEGE_BITS)
		{
			if(corridorFlags & PATH_PRIVILEGE_BITS & admissionFlags)
				result = TRUE;  // should never get to this line after code after testing in preceding loop
		}
		else
			result = TRUE;
		admissionFlags &= ~PATH_PRIVILEGE_BITS; // done with these bits
		if(result)
		{
			// Are all of the remaining bits set in admissionFlags 
			// also set for the corridor?  Ie. is the traveler
			// in an acceptable direction and is it an acceptable 
			// traveler type
			if((corridorFlags & admissionFlags) == admissionFlags) 
				p_corridorPtr = corridor;
			else
				result = FALSE;
		}
	}
	return result;
}

void LegoPathLink::AddPresenter(LegoSpacePresenter* p_spacePresenter)
{
	m_residents.Append(p_spacePresenter);
	p_spacePresenter->SetPathLinkPtr(this);
}

void LegoPathLink::RemovePresenter(LegoSpacePresenter* p_spacePresenter)
{
	LegoSpacePresenterListCursor cursor(&(m_residents));
	if(cursor.Find(p_spacePresenter))
		cursor.Detach();
}

void LegoPathNode::AddPresenter(LegoSpacePresenter* p_spacePresenter, MxBool p_setLocation)
{
	m_residents.Append(p_spacePresenter);
	p_spacePresenter->SetPathNodePtr(this);
	if(p_setLocation)
		p_spacePresenter->SetWorldTransform(m_location, p_spacePresenter->GetWorldDirection(), p_spacePresenter->GetWorldUp());
}

void LegoPathNode::RemovePresenter(LegoSpacePresenter* p_spacePresenter)
{
	LegoSpacePresenterListCursor cursor(&(m_residents));
	if(cursor.Find(p_spacePresenter))
		cursor.Detach();
}

void LegoPathLink::CheckProximity(LegoSpacePresenter* p_spacePresenter, BOOL p_checkNodes)
{
	MxDouble r2 = ACTOR_PROXIMITY_DISTANCE*ACTOR_PROXIMITY_DISTANCE;	
	LegoSpacePresenterPtr presenter;
	LegoSpacePresenterListCursor cursor(&(m_residents));
	MxS8 eventSent = FALSE;
	while (cursor.Next(presenter))
	{
		if((presenter != p_spacePresenter)
			&& ((presenter->GetWorldLocation()-p_spacePresenter->GetWorldLocation()).Magnitude2() < r2))
		{
			presenter->OnActorProximityEvent(p_spacePresenter);
			p_spacePresenter->OnActorProximityEvent(presenter);
			eventSent = TRUE;
		}
	}
	if(p_checkNodes)
		for(int i=0; i<m_numNodes; i++)
			m_nodes[i]->CheckProximity(p_spacePresenter);
}

void LegoPathNode::CheckProximity(LegoSpacePresenter* p_spacePresenter)
{
	MxDouble r2 = ACTOR_PROXIMITY_DISTANCE*ACTOR_PROXIMITY_DISTANCE;	
	LegoSpacePresenterPtr presenter;
	LegoSpacePresenterListCursor cursor(&(m_residents));
	while (cursor.Next(presenter))
	{
		if((presenter != p_spacePresenter)
			&& ((presenter->GetWorldLocation()-p_spacePresenter->GetWorldLocation()).Magnitude2() < r2))
		{
			presenter->OnActorProximityEvent(p_spacePresenter);
			p_spacePresenter->OnActorProximityEvent(presenter);
		}
	}
	for(int i=0; i<m_numLinks; i++)
		m_links[i]->CheckProximity(p_spacePresenter, FALSE);
}

// Searches for the link pointing closest to the right direction.
// Small percent of calls return a random link.
// If velocity vector is zero then fail.
MxBool LegoPathNode::SelectLink(const Mx3DPointDouble & p_velocity, LegoPathLinkPtr & p_linkPtr)
{
	MxBool result = FALSE;
	p_linkPtr = NULL;
	const RANDOM_PERCENT = 20;
	if(p_velocity.GetX()==0 && p_velocity.GetY()==0 && p_velocity.GetZ()==0)
		result = FALSE;  // should never reach this line
	else if(RANDOM_PERCENT >= 100*rand()/RAND_MAX)
	{
		int i = m_numLinks*rand()/RAND_MAX;
		if(i == m_numLinks) i--;
		result = TRUE;
		p_linkPtr = m_links[i];
	}
	else
	{
		LegoPathLinkPtr link, minLink=NULL;
		MxDouble rmin = FLT_MAX;
		MxDouble rmax = 0;
		for(int i=0; i<m_numLinks; i++)
		{
			link = m_links[i];
			Mx3DPointDouble v = link->GetVector();
			MxDouble r2;
			if(this == link->GetNodes()[0])
				v -= p_velocity;
			else
				v += p_velocity;
			r2 = v.Magnitude2();
			if(r2 < rmin)
			{
				rmin = r2;
				minLink = link;
			}
		}
		if(minLink)
		{
			result = TRUE;
			p_linkPtr = minLink;
		}
	}
	return result;
}

void LegoPathLink::AdjustMoveVector(LegoSpacePresenter* p_spacePresenter, Mx3DPointDouble &p_vector)
{
	Mx3DPointDouble resultVector = p_spacePresenter->GetWorldVelocity();

	// Calculate projected position on link.
	Mx3DPointDouble A_B = p_spacePresenter->GetWorldLocation();
	A_B += resultVector;
	A_B -= GetNodes()[0]->GetLocation();  // vector from node to location
	MxDouble newLinkDistance = (GetVector() * A_B); // scalar projection of A_B onto link
	MxDouble deltaLinkDistance = (resultVector * GetVector());  // scalar projection of move vector onto link
	
	// Calculate a vector (parallel to link) from node to projected position on link.
	Mx3DPointDouble M = GetVector();  // always a unit vector
	M *= newLinkDistance;
	
	// Calculate a vector (parallel to out-vector) from projected position on link to current location.
	Mx3DPointDouble D = A_B;
	D -= M;
	MxDouble newOutDistance = (D * GetOutVector());  // shortest distance from link to new location (perpendicular to link)
		
	// The link distance must stay between 0 and m_length.
	// It is 0 at m_node[0] and m_length at m_node[1].
	// Don't pass end of corridor and don't slide along it; 
	// just land on it and stop.
	if((newLinkDistance < 0) || (GetLength() < newLinkDistance))
	{
		MxDouble oldDelta = deltaLinkDistance;
		if(newLinkDistance < 0)	{
			deltaLinkDistance = - p_spacePresenter->GetLinkDistance();
			newLinkDistance = 0;
		}
		else {
			deltaLinkDistance = GetLength() - p_spacePresenter->GetLinkDistance();
			newLinkDistance = GetLength();
		}
		if(oldDelta)
		{
			resultVector *= deltaLinkDistance;
			resultVector /= oldDelta;
		}
	}

	MxDouble deltaOutDistance = (resultVector * GetOutVector()); // move component parallel to link

	MxDouble corridorMin = 0;
	MxDouble corridorMax = 0;
	LegoCorridorPtr corridor = p_spacePresenter->GetCorridorPtr(); 
	if(corridor && (corridor->GetWidth() >= 0)) {
		corridorMin = corridor->GetOffset();
		corridorMax = corridor->GetOffset() + corridor->GetWidth();
	}
	else if(corridor) {
		corridorMin = corridor->GetOffset() + corridor->GetWidth();
		corridorMax = corridor->GetOffset();
	}
	// don't go outside of corridor, slide along the boundary
	MxBool recalculate = FALSE;
	if(newOutDistance < corridorMin)
	{
		deltaOutDistance = corridorMin - p_spacePresenter->GetOutDistance();
		newOutDistance = corridorMin;
		recalculate = TRUE;
	}
	else if(newOutDistance > corridorMax)
	{
		deltaOutDistance = corridorMax - p_spacePresenter->GetOutDistance();
		newOutDistance = corridorMax;
		recalculate = TRUE;
	}
	if(recalculate)
	{	// calculate result from components along and across corridor; parallel and perpendicular to link
		Mx3DPointDouble tempVector;
		tempVector = GetOutVector();
		tempVector *= deltaOutDistance;  // new move component perpendicular to link

		resultVector = GetVector();
		resultVector *= deltaLinkDistance; // new move component parallel to link

		resultVector += tempVector;
	}

	p_spacePresenter->SetLinkDistance(newLinkDistance);
	p_spacePresenter->SetOutDistance(newOutDistance);

	p_vector = resultVector;
}

MxBool LegoPathLink::AtEndOfLink(LegoSpacePresenter* p_spacePresenter, 
							     LegoPathNodePtr & p_newNodePtr,
							     LegoPathLinkPtr & p_newLinkPtr,
							     LegoCorridorPtr & p_newCorridorPtr)

{
	MxS32 velocity_sign = p_spacePresenter->GetWorldSpeed() >= 0 ? 1 : -1;
	MxBool result = FALSE;
	LegoPathNodePtr newNodePtr = NULL;
	LegoPathLinkPtr newLinkPtr = NULL;
	LegoCorridorPtr newCorridorPtr = NULL;
	// look-ahead test: Are we near enough to begin a 
	// transition to a corridor on an adjacent link?
	// limit test: Are we at the extreme end of this corridor?
	MxDouble linkDistance = p_spacePresenter->GetLinkDistance();
	LegoCorridorPtr corridor = p_spacePresenter->GetCorridorPtr();
	MxDouble margin = 0;
	if(corridor) // hueristic; just need to start checking as we get "close" to a node
	{
		margin = fabs(corridor->GetOffset() + corridor->GetWidth());
		if(margin < fabs(corridor->GetOffset()))
			margin = fabs(corridor->GetOffset());
		margin *= 3;
	}
	if((linkDistance <= margin) || (linkDistance >= m_length-margin))
	{
		// only need the sign of the projection of velocity onto the link.
		MxDouble direction = p_spacePresenter->GetWorldVelocity() * m_vector;
		if(((linkDistance <= margin) && (direction < 0))
			|| (linkDistance == 0)) // last test redundant?
			newNodePtr = m_nodes[0];
		else if(((linkDistance >= m_length-margin) && (direction > 0))
			|| (linkDistance > m_length)) // last test redundant?
			newNodePtr = m_nodes[1];
	}

	if(newNodePtr)
	{
		if((linkDistance == 0) || (linkDistance==m_length))
			result = TRUE;  // Limit test will return true.
		if(newNodePtr->SelectLink(p_spacePresenter->GetWorldVelocity(), newLinkPtr))
		{
			// is velocity going with or against direction vector of selected link?
			MxS32 direction = newLinkPtr->IsOriginNode(newNodePtr) ? velocity_sign : -velocity_sign;
			if(newLinkPtr->SelectCorridor(direction, p_spacePresenter->GetPathTravelerType(), newCorridorPtr))
			{
				if(!result) // Don't bother with next test if result is true from above.
				{	// Still may return true if we are in space where corridors overlap.
					// Are we in the selected corridor space?

					// Find position relative to end-bounds of corridor
					Mx3DPointDouble A_B, M, D;
					MxDouble m, d;
					A_B = p_spacePresenter->GetWorldLocation();
					A_B -= newNodePtr->GetLocation();  // vector from node to current location
					M = newLinkPtr->GetVector();
					m = (newLinkPtr->GetVector() * A_B);  // scalar projection of A_B onto new link vector
				
					// Are we within end bounds of the selected corridor?
					if(newLinkPtr->IsOriginNode(newNodePtr)) {
						if(m < 0)
							goto done;
					} else if(m > 0)
						goto done;

					// Find position relative to side-bounds of corridor					
					M *= m;  // component of A_B parallel to link vector
					D = A_B;
					D -= M;  // component of A_B perpendicular to link vector
					d = (D * newLinkPtr->GetOutVector()); // scalar projection of A_B onto out vector
					MxDouble corridorMin, corridorMax;
					if(newCorridorPtr->GetWidth() >= 0) {
						corridorMin = newCorridorPtr->GetOffset();
						corridorMax = newCorridorPtr->GetOffset() + newCorridorPtr->GetWidth();
					}
					else {
						corridorMin = newCorridorPtr->GetOffset() + newCorridorPtr->GetWidth();
						corridorMax = newCorridorPtr->GetOffset();
					}
					// Tighten up min and max to the middle of the corridor.
					// Width a little larger than presenter's step length so we don't step over.
					MxDouble temp = corridorMax - corridorMin - 2*fabs(p_spacePresenter->GetWorldSpeed());
					temp /= 2;
					corridorMin += temp;
					corridorMax -= temp;
					
					// Are we within offset and width bounds of corridor?
					if((corridorMin <= d) && (d <= corridorMax))
						result = TRUE;  // Look-ahead test will return true.
				}
			}
		}
	}

done:
	if(result)
	{
		p_newNodePtr = newNodePtr;
		p_newLinkPtr = newLinkPtr;
		p_newCorridorPtr = newCorridorPtr;
	}

	return result;
}