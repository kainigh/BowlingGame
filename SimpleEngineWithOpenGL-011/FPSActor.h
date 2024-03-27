#pragma once
#include "Actor.h"
//#include "SoundEvent.h"
#include "Vector3.h"
#include <algorithm>


class FPSActor : public Actor
{
public:
	FPSActor();

	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;
	void shoot();

	void setFootstepSurface(float value);
	void setVisible(bool isVisible);
	void fixCollisions();
	void Power(const InputState& inputState);
	float getPower();
	float modelScale = 7.75f;


private:
	class MoveComponent* moveComponent;
	class AudioComponent* audioComponent;
	class MeshComponent* meshComponent;
	class FPSCameraComponent* cameraComponent;
	class Actor* FPSModel;
	//SoundEvent footstep;
	float lastFootstep;
	class BoxComponent* boxComponent;
	
	float moveSpeed = 0.1f;
	float move = 0.0f;
	float forwardOffset = 0.0f;

	bool power = false;
	bool launch = false;
	
	float powerSpeed = 0.05f;

	Vector3 pos = Vector3(100.0f, 100.0f, -100.0f);
	

};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 10.0f, -10.0f);
