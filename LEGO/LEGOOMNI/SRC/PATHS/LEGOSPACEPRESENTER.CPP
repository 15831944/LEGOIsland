/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoSpacePresenter.h"
#include "LEntity.h"
#include "LActor.h"
#include "LWorld.h"
#include "PathStruc.h"
#include "PathCtrl.h"

LegoSpacePresenter::LegoSpacePresenter()
{
	Init();
}

void LegoSpacePresenter::Init()
{
	m_linkPtr = NULL;	
	m_nodePtr = NULL;
	m_corridorPtr = NULL;
	m_linkDistance = 0;
	m_outDistance = 0;
	m_numTransitionSteps = 0;
	m_currentTransitionStep = 0;
	m_pathTravelerType = 0;
}

LegoSpacePresenter::~LegoSpacePresenter()
{
}

MxResult LegoSpacePresenter::Create(LegoEntity* p_entity)
{
	MxResult result = FAILURE;
	LegoPathController *pathController = NULL;
		
	SetWorld(p_entity->GetWorld());
	if(m_world)
		pathController = m_world->GetPathController();
	
	if(SUCCESS != LegoEntityPresenter::Create(p_entity)) {
		goto done;
	}

	// kludge for early development
	{
		SetPathTravelerType(PATH_TRAVELER_PEDESTRIAN);
		SetWorldSpeed(-5*c_entitySpeedIncrement);
	}

	if(pathController)
		pathController->AddPresenter(this,0);
	
	m_state = e_repeating;
	result = SUCCESS;

done:
	if(SUCCESS != result) {
	}
	return result;
}

MxResult
LegoSpacePresenter::Move()
{
	MxResult result = FAILURE;

	switch (m_state) {
		case e_repeating:
			result = RegularMove();
			break;
		case e_linkTransition:
			if(m_numTransitionSteps <= m_currentTransitionStep)
			{
				m_state = e_repeating;
				m_nodePtr->RemovePresenter(this);
				m_newLinkPtr->AddPresenter(this);
				SetPathNodePtr(NULL);
				SetCorridorPtr(m_newCorridorPtr);
				if(m_entity)
					SetWorldTransform(	m_newLocation,
										m_newDirection,
										m_entity->GetWorldUp());
				#if CLEANUP
				SetWorldDirection();
				SetWorldLocation();
				#endif
				result = RegularMove();
			}
			else
			{
				result = LinkTransitionMove();	
			}
			break;
		default:
			break;
	}
	return result;
}

MxResult
LegoSpacePresenter::RegularMove()
{
	// need to set step length according to current velocity and animation
	LegoPathController *pathController = m_world->GetPathController();
	if(pathController)
	{
		/*
		Mx3DPointDouble newDirection = GetWorldDirection();
		// Add some randomness
		MxDouble r = GetWorldSpeed() / 10;
		Mx3DPointDouble vector;
		vector.SetX(r - (2*r*rand())/RAND_MAX);
		vector.SetY(0);
		vector.SetZ(r - (2*r*rand())/RAND_MAX);
		newDirection += vector;
		SetWorldDirection(newDirection);
		*/

		pathController->MovePresenter(this);
		// Path controller will call SetWorldLocation()
	}
    return SUCCESS;
}

MxResult
LegoSpacePresenter::LinkTransitionMove()
{
	// need to set step length according to current velocity and animation
	LegoPathController *pathController = m_world->GetPathController();
	if(pathController)
	{
		// Need simultaneous interpolation of location and orientation.
		// General solution requires a spline.  We fake it here.

		// Interpolate remaining change in location vector.
		// Use result to set direction vector for path controller.
		Mx3DPointDouble newDirection = m_newLocation;
		newDirection -= GetWorldLocation();
		newDirection *= GetWorldSpeed(); // need this only to get + or - sign
		newDirection.Normalize();
		SetWorldTransform(GetWorldLocation(), newDirection, GetWorldUp());

		pathController->MovePresenter(this);
		// Path controller will call SetWorldLocation()
		
		m_currentTransitionStep++;
	}
    return SUCCESS;
}

MxBool
LegoSpacePresenter::SetLinkTransition(const Mx3DPointDouble & p_newLocation, 
									  const Mx3DPointDouble & p_newDirection,
									  MxDouble p_newLinkDistance, 
									  MxDouble p_newOutDistance,
									  LegoPathLink * p_newLinkPtr,
									  LegoCorridor * p_newCorridorPtr)
{
	Mx3DPointDouble newdir = p_newLocation;
	newdir -= GetWorldLocation();  // vector from current location to new location
	m_numTransitionSteps = (MxS32)(newdir.Magnitude() / fabs(GetWorldSpeed()) + 0.5);

	if(m_numTransitionSteps)
	{
		m_state = e_linkTransition;
		m_currentTransitionStep = 1; // first step is done now; direction change here, location change by caller
		//if(m_numTransitionSteps > 1)
		//	vector /= m_numTransitionSteps;
		//SetWorldDirection(vector);
		newdir.Normalize();
		SetWorldTransform(GetWorldLocation(), newdir, GetWorldUp());

		m_oldLocation = GetWorldLocation();
		m_oldDirection = GetWorldDirection();
		m_newLocation = p_newLocation;
		m_newDirection = p_newDirection;
		SetLinkDistance(p_newLinkDistance);
		SetOutDistance(p_newOutDistance);
		m_newLinkPtr = p_newLinkPtr;
		m_newCorridorPtr = p_newCorridorPtr;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void LegoSpacePresenter::OnActorProximityEvent(LegoSpacePresenter * p_actorPresenter)
{
	if(m_entity && m_entity->IsA("LegoActor"))	
		((LegoActor*)m_entity)->OnActorProximityEvent(((LegoActor*)p_actorPresenter->m_entity));
}

void LegoSpacePresenter::OnNodeProximityEvent(MxS32 p_nodeId)
{
	if(m_entity && m_entity->IsA("LegoActor"))	
		((LegoActor*)m_entity)->OnNodeProximityEvent(p_nodeId);
}
