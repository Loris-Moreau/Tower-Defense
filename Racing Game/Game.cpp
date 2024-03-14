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
#include "Rectangle.h"

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

	fps = new FPSActor();
	fps->setPosition(Vector3(-50.0f, 38.0f, 55.0f));
	//orbit = new OrbitActor();
	//path = new SplineActor();
	//follow = new FollowActor();


	// Pins
	// Back line
	CubeActor* a = new CubeActor();
	a->setPosition(Vector3(700.0f, -5.0f, 15.0f)); //4
    a->setScale(Vector3(10.0f, 10.0f, 30.0f));

	CubeActor* a1 = new CubeActor();
	a1->setPosition(Vector3(700.0f, 25.0f, 15.0f)); //4
	a1->setScale(Vector3(10.0f, 10.0f, 30.0f));

	CubeActor* a2 = new CubeActor();
	a2->setPosition(Vector3(700.0f, 55.0f, 15.0f)); //4
	a2->setScale(Vector3(10.0f, 10.0f, 30.0f));

	CubeActor* a3 = new CubeActor();
	a3->setPosition(Vector3(700.0f, 85.0f, 15.0f)); //4
	a3->setScale(Vector3(10.0f, 10.0f, 30.0f));

	// Middle line
	CubeActor* a4 = new CubeActor();
	a4->setPosition(Vector3(670.0f, 10.0f, 15.0f)); //3
	a4->setScale(Vector3(10.0f, 10.0f, 30.0f));

	CubeActor* a5 = new CubeActor();
	a5->setPosition(Vector3(670.0f, 40.f, 15.0f)); //3
	a5->setScale(Vector3(10.0f, 10.0f, 30.0f));

	CubeActor* a6 = new CubeActor();
	a6->setPosition(Vector3(670.0f, 70.0f, 15.0f)); //3
	a6->setScale(Vector3(10.0f, 10.0f, 30.0f));

	// Second line
	CubeActor* a7 = new CubeActor();
	a7->setPosition(Vector3(640.0f, 25.0f, 15.0f)); //2
	a7->setScale(Vector3(10.0f, 10.0f, 30.0f));

	CubeActor* a8 = new CubeActor();
	a8->setPosition(Vector3(640.0f, 55.0f, 15.0f)); //2
	a8->setScale(Vector3(10.0f, 10.0f, 30.0f));

	// Front line
	CubeActor* a9 = new CubeActor();
	a9->setPosition(Vector3(610.0f, 40.0f, 15.0f)); //1
	a9->setScale(Vector3(10.0f, 10.0f, 30.0f));
	// End Pins

	Quaternion q(Vector3::unitZ, -Maths::piOver2/2);
	//q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));

	// Arrow for direction & Power
	arrow = new CubeActor();
	arrow->setPosition(Vector3(50.0f, 38.0f, 2.0f));
	arrow->setScale(Vector3(50.0f, 5.0f, 1.0f));
	arrow->setRotation(q);


	//a->setRotation(q);
	
	// Bowling Ball
	SphereActor* b = new SphereActor();
	b->setPosition(Vector3(4.0f, 38.0f, 0.0f));
	b->setScale(Vector3(1.0f, 1.0f, 1.0f));

	// Floor and walls

	// Setup floor
	const float start = 0.0f;
	const float size = 75.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(0 + i * size, 0 + j * size, 0.0f));
		}
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
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
	float scale = 20;
	bool positive = true;
	float rotateDire = Maths::piOver2 / 2 * dt;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();

		if(!fps->getDirectionClick())
		{
			if (arrow->getRotation().z >= -0.45 && arrow->getRotation().z <= -0.38)
			{
				rotateDire = Maths::piOver2 / 2 * dt;
			}

			if (arrow->getRotation().z >= 0.40)
			{
				rotateDire = -Maths::piOver2 / 2 * dt;
			}
			arrow->rotate(Vector3::unitZ, rotateDire);
		}
		
		if (fps->getDirectionClick() && !fps->getPowerClick())
		{

			if (scale <= 100 && positive)
			{
				scale += 20 * dt;
			}
			if (scale <= 110 && !positive)
			{
				scale -= 20 * dt;
			}
			if (scale >= 100)
			{
				positive = false;
			}
			if (scale <= 20)
			{
				positive = true;
			}
			arrow->setScale(Vector3(scale, 10, 1));
		}

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