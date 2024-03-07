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
#include <algorithm>
#include "Random.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();

	Random::init();
	return isWindowInit && isRendererInit && isInputInit; // Return bool && bool && bool ...to detect error
	
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	//FilePaths
	string filePath = "..\\Assets\\";
	string filePathRes1 = filePath + "Res_005-011\\";
	string filePathRes2 = filePath + "Res_012-015\\";
	string filePathRes3 = filePath + "Res_016-025\\";

	//Shaders
	Assets::loadShader(filePathRes3 + "Shaders\\Sprite.vert", filePathRes3 + "Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader(filePathRes3 + "Shaders\\BasicMesh.vert", filePathRes3 + "Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");
	Assets::loadShader(filePathRes3 + "Shaders\\Phong.vert", filePathRes3 + "Shaders\\Phong.frag", "", "", "", "Phong");

	//Textures
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Sphere.png", "Sphere");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Rifle.png", "Rifle");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\RacingCar.png", "RacingCar");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Target.png", "Target");

	//UI Textures
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Crosshair.png", "Crosshair");

	//Meshes
	Assets::loadMesh(filePathRes3 + "Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh(filePathRes3 + "Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh(filePathRes3 + "Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh(filePathRes3 + "Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh(filePathRes3 + "Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	Assets::loadMesh(filePathRes3 + "Meshes\\Target.gpmesh", "Mesh_Target");

	//fps = new FPSActor();
	//orbit = new OrbitActor();
	//path = new SplineActor();
	follow = new FollowActor();
	follow->setSpeed(700.0f); // Changer vitesse 

	Random rando;
	// Cube for Boat
	for (int i = 0; i < 50; i++)
	{
		CubeActor* a = new CubeActor();
		a->setPosition(Vector3(rando.getFloatRange(2000, 50000), rando.getFloatRange(-2500, 2500), rando.getFloatRange(-0.1f,2.0f)));

		//float randScale = rand() % 50 + 450;
		float randScale = rando.getFloatRange(200, 950);
		a->setScale(randScale);
	}

	// Floor and walls
	// Setup floor
	const float start = -10000.0f;
	const float size = 1000.0f;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(-200 + i * size, start + j * size, 0));
		}
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	/*
	// Corsshair
	Actor* crosshairActor = new Actor();
	crosshairActor->setScale(2.0f);
	crosshair = new SpriteComponent(crosshairActor, Assets::getTexture("Crosshair"));


	TargetActor* t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 100.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 400.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, -500.0f, 200.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 500.0f, 200.0f));
	*/
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

	// Escape: quit game
	if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		isRunning = false;
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
	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
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