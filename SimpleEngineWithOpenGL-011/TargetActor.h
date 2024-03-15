#pragma once
#include "Actor.h"

class TargetActor : public Actor
{
public:
	TargetActor();

	void Hit(Vector3 dir);

private:
	class TargetMoveComponent* targetMove;

	
};
