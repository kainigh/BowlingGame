#include "TargetActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"
#include "Assets.h"
#include "TargetMoveComponent.h"
#include "Game.h"


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
	bc->setShouldRotate(false);
	
	
}

void TargetActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	if (offset >= 0)
	{
		targetMove->setForwardSpeed(-offset);
		//targetMove->setAngularSpeed(0.1f);
		
		offset -= 10.0f;
		
	}
	if (offset < 0)
	{
		offset = 0.0f;
		targetMove->setForwardSpeed(0.0f);
		targetMove->setAngularSpeed(0.0f);
	}
	

	//lifetimeSpan -= dt;

}

void TargetActor::setPlayer(Actor* player)
{
	targetMove->setPlayer(player);
}

void TargetActor::Hit()
{

	//setPosition(dir);
	targetMove = new TargetMoveComponent(this);
	targetMove->setForwardSpeed(0.0f);
	cout << "Pin hit" << endl;


}