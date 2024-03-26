#pragma once
#include "MoveComponent.h"
class BallMoveComponent : public MoveComponent
{
public:
	BallMoveComponent(class Actor* ownerP);

	void setPlayer(class Actor* playerP);

	void update(float dt) override;

	bool oceanHit = false;

	//Vector3 changeTargetPosition = Vector3(100.0f, 100.0f, -100.0f);

protected:
	class Actor* player;
};

