#include "Game.h"
#include "..\Actors and Components\Actors\Actor.h"
#include "..\Maths\Timer.h"
#include "..\Main\Assets.h"
#include "..\Actors and Components\Components\MeshComponent.h"
#include "..\Actors and Components\Actors\CubeActor.h"
#include "..\Actors and Components\Actors\SphereActor.h"
#include "..\Actors and Components\Actors\PlaneActor.h"
#include "..\Actors and Components\Actors\FPSActor.h"
#include "..\Actors and Components\Actors\FollowActor.h"
#include "..\Actors and Components\Actors\OrbitActor.h"
#include "..\Actors and Components\Actors\SplineActor.h"
#include "..\Actors and Components\Actors\TargetActor.h"
#include "..\UI\PauseScreen.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();
	bool isFontInit = Font::initialize();

	return isWindowInit && isRendererInit && isInputInit && isFontInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	//FilePaths
	const string filePath = "..\\Assets\\";
	string filePathRes1 = filePath + "Res_005-011\\";
	string filePathRes2 = filePath + "Res_012-015\\";
	const string filePathRes3 = filePath + "Res_016-025\\";
	const string filePathRes4 = filePath + "Res_036-042\\";
	const string filePathRes5 = filePath + "Res_043-044\\";

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
	Assets::loadTexture(renderer, filePathRes5 + "Textures\\CatWarrior.png", "CatWarrior");
	
	//UI Textures
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, filePathRes3 + "Textures\\Crosshair.png", "Crosshair");

	Assets::loadTexture(renderer, filePathRes4 + "Textures\\ButtonYellow.png", "ButtonYellow");
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\ButtonBlue.png", "ButtonBlue");
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\DialogBG.png","DialogBG");

	//Radar
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\Crosshair.png","Crosshair");
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\CrosshairRed.png",	"CrosshairRed");
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\Radar.png",	"Radar");
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\Blip.png", "Blip");
	Assets::loadTexture(renderer, filePathRes4 + "Textures\\RadarArrow.png",	"RadarArrow");
	
	//Meshes
	Assets::loadMesh(filePathRes3 + "Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh(filePathRes3 + "Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh(filePathRes3 + "Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh(filePathRes3 + "Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh(filePathRes3 + "Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	Assets::loadMesh(filePathRes3 + "Meshes\\Target.gpmesh", "Mesh_Target");
	//Assets::loadMesh(filePathRes5 + "Meshes\\CatWarrior.gpmesh", "Mesh_CatWarrior");
	
	//Fonts
	Assets::loadFont(filePathRes4 + "Fonts\\Carlito-Regular.ttf", "Carlito");
	//Assets::loadFont(filePathRes4 + "Fonts\\feet.ttf", "Carlito");

	//Localisation
	Assets::loadText(filePathRes4 + "Localization\\English.gptext");
	//Assets::loadText(filePathRes4 + "Localization\\Russian.gptext");

	//Animations
	Assets::loadSkeleton(filePathRes5 + "Animations\\CatWarrior.gpskel", "Skel_CatWarrior");
	Assets::loadAnimation(filePathRes5 + "Animations\\CatActionIdle.gpanim", "CatActionIdle");
	Assets::loadAnimation(filePathRes5 + "Animations\\CatRunMOBA.gpanim", "CatRunMOBA");
	Assets::loadAnimation(filePathRes5 + "Animations\\CatRunSprint.gpanim", "CatRunSprint");
	
	fps = new FPSActor();

	CubeActor* a = new CubeActor();
	a->setPosition(Vector3(225.0f, 105.0f, 0.0f));
	a->setScale(100.0f);
	Quaternion q(Vector3::unitY, -Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
	a->setRotation(q);

	SphereActor* b = new SphereActor();
	b->setPosition(Vector3(225.0f, -75.0f, 0.0f));
	b->setScale(3.0f);

	// Floor and walls
	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, start - size, 0.0f));
		p->setRotation(q);

		p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->setRotation(q);
	}

	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start - size, start + i * size, 0.0f));
		p->setRotation(q);

		p = new PlaneActor();
		p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
		p->setRotation(q);
	}

	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	//HUD
	hud = new HUD();
	
	// Crosshair
	Actor* crosshairActor = new Actor();
	crosshairActor->setScale(1.75f);
	crosshair = new SpriteComponent(crosshairActor, Assets::getTexture("Crosshair"));
	
	TargetActor* t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 100.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 400.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, -500.0f, 200.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 500.0f, 200.0f));
}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		bool isRunning = inputSystem.processEvent(event);
		if (!isRunning) state = GameState::Quit;
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	if (state == GameState::Gameplay)
	{
		// Escape: pause game
		if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
		{
			new PauseScreen();
			return;
		}

		// Actor input
		isUpdatingActors = true;
		for (auto actor : actors)
		{
			actor->processInput(input);
		}
		isUpdatingActors = false;
	}
	else
	{
		if (!UIStack.empty())
		{
			UIStack.back()->processInput(input);
		}
	}
}

void Game::update(float dt)
{
	if (state == GameState::Gameplay)
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

	// Update UI screens
	for (auto ui : UIStack)
	{
		if (ui->getState() == UIState::Active)
		{
			ui->update(dt);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = UIStack.begin();
	while (iter != UIStack.end())
	{
		if ((*iter)->getState() == UIState::Closing)
		{
			delete* iter;
			iter = UIStack.erase(iter);
		}
		else
		{
			++iter;
		}
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
	while (state != GameState::Quit)
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
	Font::close();
	inputSystem.close();
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::setState(GameState stateP)
{
	state = stateP;
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

void Game::pushUI(UIScreen* screen)
{
	UIStack.emplace_back(screen);
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
