#include "BallMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "TargetActor.h"
#include "Game.h"

#include <iostream>

using namespace std;

BallMoveComponent::BallMoveComponent(Actor* ownerP) : MoveComponent(ownerP), player(nullptr)
{
	
}

void BallMoveComponent::setPlayer(Actor* playerP)
{
	player = playerP;
}

void BallMoveComponent::update(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;
	

	owner.setPosition(start);
	
	//cout << player->getPosition().z << endl;
	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != player)
	{
		// If we collided, reflect the ball about the normal
		dir = Vector3::reflect(dir, info.normal);
		//owner.rotateToNewForward(dir);
		
		// Did we hit a target?
		TargetActor* target = dynamic_cast<TargetActor*>(info.actor);
		
		if (target)
		{
			
			
			float ballPower = getForwardSpeed();
			target->offset += ballPower;

			
			target->getGame().clearPreviousScore(target->getGame().totalScore);
			int newScore = target->getGame().totalScore + 1;
			target->getGame().setNewScore(newScore);
				
			static_cast<BallActor*>(&owner)->hitTarget();

		}
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}
