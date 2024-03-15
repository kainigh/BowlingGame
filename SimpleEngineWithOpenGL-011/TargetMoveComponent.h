#pragma once
#include "MoveComponent.h"
class TargetMoveComponent : public MoveComponent
{
public:
	TargetMoveComponent(class Actor* ownerP);

	void setPlayer(class Actor* playerP);

	void update(float dt) override;

	bool oceanHit = false;

protected:
	class Actor* player;
};


