/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"

#include "PathCtrl.h"
#include "LegoSpacePresenter.h"

LegoPathController::LegoPathController()
{
	m_links = NULL;
	m_nodes = NULL;
	m_corridors = NULL;
	m_numLinks = 0;
	m_numNodes = 0;
	m_numCorridors = 0;
}

MxS32 LegoPathController::Create(LegoPaths * p_rawData, const Mx3DPointDouble & p_location)
{
	MxS32 result = FAILURE;

	Init();

	// build run-time structures from raw data
    p_rawData->ParseData(p_rawData->GetData(),
					   m_numLinks, m_links, 
					   m_numNodes, m_nodes,
					   m_numCorridors, m_corridors);
	
	if(!m_links || !m_nodes || !m_corridors)
		goto done;

	int i;
	for(i=0; i<m_numNodes; i++)
	{
		Mx3DPointDouble point = m_nodes[i].GetLocation();
		point += p_location;
		m_nodes[i].SetLocation(point);
	}
		
	result = SUCCESS;

done:
	if(SUCCESS != result)
		Init();

	return result;
}

MxS32 LegoPathController::Create(MxCharString p_fileName)
{
	MxS32 result = FAILURE;

	// load all raw data in from a file
	LegoPaths	* rawData = new LegoPaths();
	if(NULL != rawData)
	{
		if(SUCCESS != rawData->Read(p_fileName))
			goto done;
	}
	else
		goto done;

	result = Create(rawData, Mx3DPointDouble(0,0,0));

done:
	delete rawData;
	return result;
}

MxS32 LegoPathController::Create()
{
//	return Create("test.pth");
	return SUCCESS;
}

void LegoPathController::Init()
{
	if(m_links)
		delete[] m_links;
	m_links = NULL;
	if(m_nodes)
		delete[] m_nodes;
	m_nodes = NULL;
	if(m_corridors)
		delete[] m_corridors;
	m_corridors = NULL;
	m_numLinks = 0;
	m_numNodes = 0;
	m_numCorridors = 0;
}

LegoPathController::~LegoPathController()
{
	Init();
}

void LegoPathController::AddPresenter(LegoSpacePresenter* p_spacePresenter, MxS32 p_nodeId)
{
	p_nodeId %= m_numNodes;
	m_nodes[p_nodeId].AddPresenter(p_spacePresenter, TRUE);
}

void LegoPathController::HandleEndOfLink(LegoSpacePresenter* p_spacePresenter)
{
	MxS32 velocity_sign = p_spacePresenter->GetWorldSpeed() >= 0 ? 1 : -1;
	LegoPathLinkPtr newLinkPtr = NULL;
	LegoCorridorPtr newCorridorPtr = NULL;
	// Are we on a link?
	if(p_spacePresenter->GetPathLinkPtr())  // are we attached to a link?
	{
		LegoPathNodePtr newNodePtr = NULL;
		// Have we reached an end node?  Look ahead to get next link and corridor.
		if(p_spacePresenter->GetPathLinkPtr()->AtEndOfLink(p_spacePresenter, newNodePtr, newLinkPtr, newCorridorPtr))
		{
			// Remove ActorPresenter from link and attach to destination node.
			p_spacePresenter->GetPathLinkPtr()->RemovePresenter(p_spacePresenter);
			newNodePtr->AddPresenter(p_spacePresenter);
			p_spacePresenter->SetPathLinkPtr(NULL);
			// Send an arrived-at-node event to ActorPresenter.
			p_spacePresenter->OnNodeProximityEvent(newNodePtr->GetId());
		}
	}
	
	// Are we on a node?
	if(p_spacePresenter->GetPathNodePtr())
	{
		// Try to move onto a link.
		LegoPathNodePtr node = p_spacePresenter->GetPathNodePtr();
		if(!newLinkPtr) // if we don't have a new link from look-ahead code above
		{
			if(node->SelectLink(p_spacePresenter->GetWorldVelocity(), newLinkPtr))
			{
				// is velocity going with or against link direction vector?
				MxS32 direction = newLinkPtr->IsOriginNode(node) ? velocity_sign : -velocity_sign;
				newLinkPtr->SelectCorridor(direction, p_spacePresenter->GetPathTravelerType(), newCorridorPtr);
			}
		}
		if(newLinkPtr) 
		{
			// Calculate the nearest suitable location in the new
			// link and corridor.

			// Calculate new projected position on new link.
			Mx3DPointDouble A_B = p_spacePresenter->GetWorldLocation();
			A_B -= node->GetLocation();  // vector from node to location
			MxDouble newLinkDistance = (newLinkPtr->GetVector() * A_B);  // scalar projection of A_B onto link
			// Adjust new link distance to be  within end-bounds of the corridor.
			if(newLinkPtr->IsOriginNode(node)) 
			{
				if(newLinkDistance < 0)
					newLinkDistance = 0;
			} 
			else if(newLinkDistance > 0)
				newLinkDistance = 0;
			// Calculate a vector (parallel to link) from node to projected position on link.
			Mx3DPointDouble M = newLinkPtr->GetVector();  // always a unit vector
			M *= newLinkDistance;
			// Calculate a vector (parallel to out-vector) from projected position on link to current location.
			Mx3DPointDouble D = A_B;  // vector from node to location
			D -= M;  // vector from nearest point on link to location (perpendicular to link)

			// Calculate new corridor side bounds.
			MxDouble corridorMin, corridorMax;
			if(newCorridorPtr) {
				if(newCorridorPtr->GetWidth() >= 0) {
					corridorMin = newCorridorPtr->GetOffset();
					corridorMax = newCorridorPtr->GetOffset() + newCorridorPtr->GetWidth();
				}
				else {
					corridorMin = newCorridorPtr->GetOffset() + newCorridorPtr->GetWidth();
					corridorMax = newCorridorPtr->GetOffset();
				}
			}
			else {
				corridorMin = corridorMax = 0;
			}
			// Tighten up min and max to the middle of the corridor.
			// Width a little larger than presenter's step length so we don't step over.
			MxDouble temp = corridorMax - corridorMin - 2*fabs(p_spacePresenter->GetWorldSpeed());
			temp /= 2;
			corridorMin += temp;
			corridorMax -= temp;
					
			// Calculate new projected position on new out-vector.
			MxDouble newOutDistance = newLinkPtr->GetOutVector() * D;
			// Adjust new out-distance to be within side bounds of the corridor.
			if((corridorMin > newOutDistance) || (newOutDistance > corridorMax))
			{
				if(newOutDistance < corridorMin)
					newOutDistance = corridorMin;
				else if(newOutDistance > corridorMax)
					newOutDistance = corridorMax;
				D = newLinkPtr->GetOutVector();
				D *= newOutDistance;
			}

			// Calculate new location by combining the new link distance and
			// new out distance from the new node.
			Mx3DPointDouble newLocation = node->GetLocation();
			newLocation += M;  // add component parallel to the link
			newLocation += D;  // add component perpendicular to the link

			// Orient new direction vector = + or - the link direction  
			Mx3DPointDouble newDirection = newLinkPtr->GetVector();
			if(!newLinkPtr->IsOriginNode(node))
			{
				newDirection *= -1;
				newLinkDistance += newLinkPtr->GetLength();
			}
			// Correct new direction vector according to sign of velocity
			if(velocity_sign < 0)
				newDirection *= velocity_sign;

			/*
			// Are transition steps needed?
			Mx3DPointDouble vector = newLocation;
			vector -= p_spacePresenter->GetWorldLocation();
			MxS32 numTransitionSteps = (MxS32)(vector.Magnitude() / fabs(p_spacePresenter->GetWorldSpeed()) + 0.5);
			if(numTransitionSteps)
			{
				// Set up presenter to execute a "nice" transition to the new location and direction.
				p_spacePresenter->SetLinkTransition
					(newLocation, newDirection, newLinkDistance, newOutDistance,
					 newLinkPtr, newCorridorPtr);
			}
			else
			*/
			// Set up presenter to execute a "nice" transition to the new location and direction.
			if(!p_spacePresenter->SetLinkTransition
					(newLocation, newDirection, newLinkDistance, newOutDistance,
					 newLinkPtr, newCorridorPtr))
			{
				// Close enough - no transition steps needed.
				// Remove ActorPresenter from old node and add it to link.
				node->RemovePresenter(p_spacePresenter);
				newLinkPtr->AddPresenter(p_spacePresenter);
				p_spacePresenter->SetPathNodePtr(NULL);
				p_spacePresenter->SetCorridorPtr(newCorridorPtr);
				p_spacePresenter->SetLinkDistance(newLinkDistance);
				p_spacePresenter->SetOutDistance(newOutDistance);
				p_spacePresenter->SetWorldTransform(newLocation, newDirection, p_spacePresenter->GetWorldUp());
				#if CLEANUP
				p_spacePresenter->SetWorldDirection(newDirection);
				p_spacePresenter->SetWorldLocation(newLocation);
				#endif
			}
		}
	}
}

void LegoPathController::MovePresenter(LegoSpacePresenter* p_spacePresenter)
{
	Mx3DPointDouble vector;
	if(p_spacePresenter->GetState() != LegoSpacePresenter::e_linkTransition)
	{
		HandleEndOfLink(p_spacePresenter);  // may modify presenter's state, direction and location
		vector = p_spacePresenter->GetWorldVelocity();
		if(p_spacePresenter->GetState() != LegoSpacePresenter::e_linkTransition)
		{
			// Final adjustment of direction vector by node, link and/or corridor.
			if(p_spacePresenter->GetPathLinkPtr())
				p_spacePresenter->GetPathLinkPtr()->AdjustMoveVector(p_spacePresenter, vector);
			//p_spacePresenter->SetWorldDirection(vector);
		}
	}
	else
	{
		vector = p_spacePresenter->GetWorldVelocity();
	}

	// Move the presenter
	vector += p_spacePresenter->GetWorldLocation();
	p_spacePresenter->SetWorldTransform(vector, p_spacePresenter->GetWorldDirection(), p_spacePresenter->GetWorldUp());
	// Run collision checking for the presenter
	if(p_spacePresenter->GetPathLinkPtr())
		p_spacePresenter->GetPathLinkPtr()->CheckProximity(p_spacePresenter, TRUE);
	else if(p_spacePresenter->GetPathNodePtr())
		p_spacePresenter->GetPathNodePtr()->CheckProximity(p_spacePresenter);
}

