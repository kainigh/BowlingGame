#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
//#include "AudioComponent.h"
#include "BallMoveComponent.h"
#include "Game.h"

#include <iostream>

using namespace std;

BallActor::BallActor(float power) : Actor(), lifetimeSpan(2.0f), audio(nullptr), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	//audio = new AudioComponent(this);
	ballMove = new BallMoveComponent(this);
	
	ballMove->setForwardSpeed(7.0f * power * power);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	//if (lifetimeSpan < 0.0f)
	//{
	if (ballMove->getOwner().getPosition().x >= 2000)
	{
		setState(ActorState::Dead);
		getGame().numberOfTries += 1;
		getGame().waiting = false;
	}
	else if(ballMove->getOwner().getPosition().x < 2000)
		getGame().waiting = true;
	//}

	
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget()
{
	//setState(ActorState::Dead);
	//cout << "boom" << endl;
	//audio->playEvent("event:/Ding");
}
