#pragma once
#include "Actor.h"

class TargetActor : public Actor
{
public:
	TargetActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void Hit();
	float offset = 0.0f;

private:
	class TargetMoveComponent* targetMove;

	
};
