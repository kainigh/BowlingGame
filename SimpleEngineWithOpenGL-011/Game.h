#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "Camera.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true), isUpdatingActors(false), fps(nullptr), scoreboard(nullptr), follow(nullptr), orbit(nullptr), path(nullptr) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }

	// Game-specific
	void addPlane(class PlaneActor* plane);
	void removePlane(class PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }

	int numberOfTries = 0;
	int totalScore = 0;
	
	void clearPreviousScore(int score);
	void setNewScore(int score);
	void Rest();
	bool waiting = false;

	class SpriteComponent* score_0;
	class SpriteComponent* score_1;
	class SpriteComponent* score_2;
	class SpriteComponent* score_3;
	class SpriteComponent* score_4;
	class SpriteComponent* score_5;
	class SpriteComponent* score_6;
	class SpriteComponent* score_7;
	class SpriteComponent* score_8;
	class SpriteComponent* score_9;

private:
	void processInput();
	void update(float dt);
	void render();
	void changeCamera(int mode);

	bool isRunning;
	Window window;
	RendererOGL renderer;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;


	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	Camera* camera;

	class FPSActor* fps;
	class SpriteComponent* scoreboard;
	
	class FollowActor* follow;
	class OrbitActor* orbit;
	class SplineActor* path;

	vector<PlaneActor*> planes;

};

