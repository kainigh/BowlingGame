#include "TargetActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"
#include "Assets.h"
#include "TargetMoveComponent.h"

#include <iostream>

using namespace std;

TargetActor::TargetActor()
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
	// Add collision box
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
	targetMove = new TargetMoveComponent(this);

	
}

void TargetActor::Hit(Vector3 dir)
{
	//setState(ActorState::Dead);

	//setPosition(dir);

	cout << "Pin hit" << endl;

	//targetMove->

	

}