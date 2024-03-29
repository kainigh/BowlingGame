#include "Game.h"
#include "Actor.h"
#include "Timer.h"
#include "Assets.h"
#include "MeshComponent.h"
#include "CubeActor.h"
#include "SphereActor.h"
#include "PlaneActor.h"
#include "FPSActor.h"
#include "FollowActor.h"
#include "OrbitActor.h"
#include "SplineActor.h"
#include "TargetActor.h"
#include <algorithm>

#include <iostream>

using namespace std;

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();

	return isWindowInit && isRendererInit && isInputInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");

	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\arrow.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "Res\\Textures\\floor.jpg", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	Assets::loadTexture(renderer, "Res\\Textures\\scoreboard.png", "Scoreboard");
	Assets::loadTexture(renderer, "Res\\Textures\\0.png", "0");
	Assets::loadTexture(renderer, "Res\\Textures\\1.png", "1");
	Assets::loadTexture(renderer, "Res\\Textures\\2.png", "2");
	Assets::loadTexture(renderer, "Res\\Textures\\3.png", "3");
	Assets::loadTexture(renderer, "Res\\Textures\\4.png", "4");
	Assets::loadTexture(renderer, "Res\\Textures\\5.png", "5");
	Assets::loadTexture(renderer, "Res\\Textures\\6.png", "6");
	Assets::loadTexture(renderer, "Res\\Textures\\7.png", "7");
	Assets::loadTexture(renderer, "Res\\Textures\\8.png", "8");
	Assets::loadTexture(renderer, "Res\\Textures\\9.png", "9");

	Assets::loadTexture(renderer, "Res\\Textures\\RacingCar.png", "RacingCar");
	Assets::loadTexture(renderer, "Res\\Textures\\Rifle.png", "Rifle");
	Assets::loadTexture(renderer, "Res\\Textures\\Target.png", "Target");

	


	Assets::loadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh("Res\\Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh("Res\\Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	Assets::loadMesh("Res\\Meshes\\Target.gpmesh", "Mesh_Target");

	
	
	fps = new FPSActor();
	follow = new FollowActor();
	orbit = new OrbitActor();
	path = new SplineActor();

	/*CubeActor* a = new CubeActor();
	a->setPosition(Vector3(200.0f, 105.0f, 0.0f));
	a->setScale(100.0f);
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->setRotation(q);*/

	/*SphereActor* b = new SphereActor();
	b->setPosition(Vector3(200.0f, -75.0f, 0.0f));
	b->setScale(3.0f);*/

	// Floor and walls

	// Setup floor
	const float start = -500.0f;
	const float size = 250.0f;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	/*q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, start - size, 0.0f));
		p->setRotation(q);

		p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->setRotation(q);
	}*/

	//q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	//// Forward/back walls
	//for (int i = 0; i < 10; i++)
	//{
	//	PlaneActor* p = new PlaneActor();
	//	p->setPosition(Vector3(start - size, start + i * size, 0.0f));
	//	p->setRotation(q);

	//	p = new PlaneActor();
	//	p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
	//	p->setRotation(q);
	//}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// Create spheres with audio components playing different sounds
	//SphereActor* soundSphere = new SphereActor();
	//soundSphere->setPosition(Vector3(500.0f, -75.0f, 0.0f));
	//soundSphere->setScale(1.0f);
	//AudioComponent* ac = new AudioComponent(soundSphere);
	//ac->playEvent("event:/FireLoop");
	

	// Scoreboard
	Actor* Scoreboard = new Actor();
	Scoreboard->setScale(1.0f);
	Scoreboard->setPosition(Vector3(0.0f, 350.0f, 0.0f));
	scoreboard = new SpriteComponent(Scoreboard, Assets::getTexture("Scoreboard"));

	Actor* number_0 = new Actor();
	number_0->setScale(0.50f);
	number_0->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_0 = new SpriteComponent(number_0, Assets::getTexture("0"));

	Actor* number_1 = new Actor();
	number_1->setScale(0.50f);
	number_1->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_1 = new SpriteComponent(number_1, Assets::getTexture("1"));

	Actor* number_2 = new Actor();
	number_2->setScale(0.50f);
	number_2->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_2 = new SpriteComponent(number_2, Assets::getTexture("2"));

	Actor* number_3 = new Actor();
	number_3->setScale(0.50f);
	number_3->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_3 = new SpriteComponent(number_3, Assets::getTexture("3"));

	Actor* number_4 = new Actor();
	number_4->setScale(0.50f);
	number_4->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_4 = new SpriteComponent(number_4, Assets::getTexture("4"));

	Actor* number_5 = new Actor();
	number_5->setScale(0.50f);
	number_5->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_5 = new SpriteComponent(number_5, Assets::getTexture("5"));

	Actor* number_6 = new Actor();
	number_6->setScale(0.50f);
	number_6->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_6 = new SpriteComponent(number_6, Assets::getTexture("6"));

	Actor* number_7 = new Actor();
	number_7->setScale(0.50f);
	number_7->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_7 = new SpriteComponent(number_7, Assets::getTexture("7"));

	Actor* number_8 = new Actor();
	number_8->setScale(0.50f);
	number_8->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_8 = new SpriteComponent(number_8, Assets::getTexture("8"));

	Actor* number_9 = new Actor();
	number_9->setScale(0.50f);
	number_9->setPosition(Vector3(0.0f, 300.0f, 0.0f));
	score_9 = new SpriteComponent(number_9, Assets::getTexture("9"));


	TargetActor* t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1000.0f, 0.0f, -75.0f));
	
	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1050.0f, 20.0f, -75.0f));
	
	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1050.0f, -20.0f, -75.0f));

	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1100.0f, 0.0f, -75.0f));

	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1100.0f, 40.0f, -75.0f));

	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1100.0f, -40.0f, -75.0f));
	
	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1150.0f, 20.0f, -75.0f));

	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1150.0f, -20.0f, -75.0f));

	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1150.0f, -60.0f, -75.0f));

	t = new TargetActor();
	t->setScale(55.0f);
	t->setPosition(Vector3(1150.0f, 60.0f, -75.0f));

	
	changeCamera(1);
}

void Game::Rest()
{

	clearPreviousScore(totalScore);
	setNewScore(0);
	numberOfTries = 0;
	totalScore = 0;

	

	actors.at(61)->setPosition(Vector3(1000.0f, 0.0f, -75.0f));
	actors.at(62)->setPosition(Vector3(1050.0f, 20.0f, -75.0f));
	actors.at(63)->setPosition(Vector3(1050.0f, -20.0f, -75.0f));
	actors.at(64)->setPosition(Vector3(1100.0f, 0.0f, -75.0f));
	actors.at(65)->setPosition(Vector3(1100.0f, 40.0f, -75.0f));
	actors.at(66)->setPosition(Vector3(1100.0f, -40.0f, -75.0f));
	actors.at(67)->setPosition(Vector3(1150.0f, 20.0f, -75.0f));
	actors.at(68)->setPosition(Vector3(1150.0f, -20.0f, -75.0f));
	actors.at(69)->setPosition(Vector3(1150.0f, -60.0f, -75.0f));
	actors.at(70)->setPosition(Vector3(1150.0f, 60.0f, -75.0f));

}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		isRunning = inputSystem.processEvent(event);
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	if (input.mouse.getButtonState(1) == ButtonState::Pressed)
	{
		Vector2 mousePosition = input.mouse.getPosition();
	}
	
	// Escape: quit game
	if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		isRunning = false;
	}

	if (input.keyboard.getKeyState(SDL_SCANCODE_1) == ButtonState::Pressed)
	{
		changeCamera(1);
	}
	else if (input.keyboard.getKeyState(SDL_SCANCODE_2) == ButtonState::Pressed)
	{
		changeCamera(2);

	}
	else if (input.keyboard.getKeyState(SDL_SCANCODE_3) == ButtonState::Pressed)
	{
		changeCamera(3);
	}
	else if (input.keyboard.getKeyState(SDL_SCANCODE_4) == ButtonState::Pressed)
	{
		changeCamera(4);
	}


	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(input);
	}
	isUpdatingActors = false;
}

void Game::update(float dt)
{
	if (numberOfTries >= 2)
		Rest();

	// Update actors 
	isUpdatingActors = true;
	for(auto actor: actors) 
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor: pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::changeCamera(int mode)
{
	// Disable everything
	fps->setState(Actor::ActorState::Paused);
	fps->setVisible(false);
	scoreboard->setVisible(false);
	follow->setState(Actor::ActorState::Paused);
	follow->setVisible(false);
	orbit->setState(Actor::ActorState::Paused);
	orbit->setVisible(false);
	path->setState(Actor::ActorState::Paused);

	// Enable the camera specified by the mode
	switch (mode)
	{
	case 1:
	default:
		fps->setState(Actor::ActorState::Active);
		fps->setVisible(true);
		scoreboard->setVisible(true);
		if (totalScore == 0)
			score_0->setVisible(true);
		break;
	case 2:
		follow->setState(Actor::ActorState::Active);
		follow->setVisible(true);
		break;
	case 3:
		orbit->setState(Actor::ActorState::Active);
		orbit->setVisible(false);
		break;
	case 4:
		path->setState(Actor::ActorState::Active);
		path->restartSpline();
		break;
	}
}

void Game::clearPreviousScore(int score)
{



		switch (totalScore)
		{

		case 0:
			score_0->setVisible(false);
			break;

		case 1:
			score_1->setVisible(false);
			break;

		case 2:
			score_2->setVisible(false);
			break;

		case 3:
			score_3->setVisible(false);
			break;

		case 4:
			score_4->setVisible(false);
			break;

		case 5:
			score_5->setVisible(false);
			break;

		case 6:
			score_6->setVisible(false);
			break;

		case 7:
			score_7->setVisible(false);
			break;

		case 8:
			score_8->setVisible(false);
			break;

		case 9:
			score_9->setVisible(false);
			break;

		default:
			score_0->setVisible(false);
			break;


		}

	
}

void Game::setNewScore(int score)
{

	totalScore = score;

	switch (totalScore)
	{

	case 0:
		score_0->setVisible(true);
		break;

	case 1:
		score_1->setVisible(true);
		break;

	case 2:
		score_2->setVisible(true);
		break;

	case 3:
		score_3->setVisible(true);
		break;

	case 4:
		score_4->setVisible(true);
		break;

	case 5:
		score_5->setVisible(true);
		break;

	case 6:
		score_6->setVisible(true);
		break;

	case 7:
		score_7->setVisible(true);
		break;

	case 8:
		score_8->setVisible(true);
		break;

	case 9:
		score_9->setVisible(true);
		break;

	default:
		score_0->setVisible(true);
		totalScore = 0;
		break;


	}
}


void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	inputSystem.close();
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::addPlane(PlaneActor* plane)
{
	planes.emplace_back(plane);
}

void Game::removePlane(PlaneActor* plane)
{
	auto iter = std::find(begin(planes), end(planes), plane);
	planes.erase(iter);
}