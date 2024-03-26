#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
//#include "AudioComponent.h"
#include "BallMoveComponent.h"

#include <iostream>

using namespace std;

BallActor::BallActor() : Actor(), lifetimeSpan(10.0f), audio(nullptr), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	//audio = new AudioComponent(this);
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(300.0f);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget()
{
	setState(ActorState::Dead);
	//cout << "boom" << endl;
	//audio->playEvent("event:/Ding");
}
