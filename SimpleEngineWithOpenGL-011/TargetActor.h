#pragma once
#include "Actor.h"
#include "FPSActor.h"

class TargetActor : public Actor
{
public:
	TargetActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void Hit();
	float offset = 0.0f;
	float tPower;

private:
	class TargetMoveComponent* targetMove;
	//class FPSActor* fpsActor = new FPSActor();

	
};
