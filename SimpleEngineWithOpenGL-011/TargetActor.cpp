#include "TargetActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"
#include "Assets.h"
#include "TargetMoveComponent.h"


#include <iostream>

using namespace std;

TargetActor::TargetActor() : Actor(), targetMove(nullptr)
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
	// Add collision box
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
	targetMove = new TargetMoveComponent(this);
	
	
}

void TargetActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	if (offset > 0)
	{
		targetMove->setForwardSpeed(-offset);
		//targetMove->setAngularSpeed(offset);
		
		offset -= 1.0f;
		
	}
	if (offset < 0)
		offset = 0.0f;

	cout << "offset = " << offset << endl;

	//lifetimeSpan -= dt;

}

void TargetActor::setPlayer(Actor* player)
{
	targetMove->setPlayer(player);
}

void TargetActor::Hit()
{
	//setState(ActorState::Dead);

	//setPosition(dir);
	targetMove = new TargetMoveComponent(this);
	targetMove->setForwardSpeed(0.0f);
	cout << "Pin hit" << endl;

	//targetMove->

	

}