#include "Game.h"
#include <algorithm>
#include <sstream>
#include "Actor.h"
#include "Timer.h"
#include "Assets.h"
#include "MeshComponent.h"
#include "CubeActor.h"
#include "SphereActor.h"
#include "PlaneActor.h"
#include "FPSActor.h"
#include "TargetActor.h"
#include "PauseScreen.h"

using namespace std;

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();
	bool isFontInit = Font::initialize();

	return isWindowInit && isRendererInit && isInputInit && isFontInit; // Return bool && bool && bool ...to detect error
}

vector<vector<int>> Game::loadLevel(const string& filename)
{
	ifstream file(filename);
	vector<vector<int>> level;
	string line;
	
	if (!file.is_open())
	{
		std::cerr << "Failed to open level file" << '\n';
		return level;
	}
	
	while (getline(file, line)) 
	{
		vector<int> row;
		istringstream iss(line);
		int value;
		while (iss >> value) 
		{
			row.push_back(value);
		}
		level.push_back(row);
	}

	return level;
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");

	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	Assets::loadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res\\Textures\\RacingCar.png", "RacingCar");
	Assets::loadTexture(renderer, "Res\\Textures\\Rifle.png", "Rifle");
	Assets::loadTexture(renderer, "Res\\Textures\\Target.png", "Target");
	Assets::loadTexture(renderer, "Res\\Textures\\ButtonYellow.png", "ButtonYellow");
	Assets::loadTexture(renderer, "Res\\Textures\\ButtonBlue.png", "ButtonBlue");
	Assets::loadTexture(renderer, "Res\\Textures\\DialogBG.png", "DialogBG");
	Assets::loadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res\\Textures\\CrosshairRed.png", "CrosshairRed");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Blip.png", "Blip");
	Assets::loadTexture(renderer, "Res\\Textures\\RadarArrow.png", "RadarArrow");
	
	Assets::loadTexture(renderer, "Res\\Textures\\TheEnd.png", "TheEnd");
	Assets::loadTexture(renderer, "Res\\Textures\\Teleporter.png", "Teleporter");
	Assets::loadTexture(renderer, "Res\\Textures\\Door.png", "Door");
	
	Assets::loadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh("Res\\Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh("Res\\Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	Assets::loadMesh("Res\\Meshes\\Target.gpmesh", "Mesh_Target");

	Assets::loadFont("Res\\Fonts\\Carlito-Regular.ttf", "Carlito");
	Assets::loadText("Res\\Localization\\English.gptext");


	fps = new FPSActor();

	std::vector<std::vector<int>> level = loadLevel("Res\\Levels\\level1.txt");
	std::vector<std::vector<int>> level2 = loadLevel("Res\\Levels\\level2.txt");

	const Vector3 cubeSize = Vector3(500.0f, 500.0f, 1000.0f);
	const float startX = -1250.0f;
	const float startY = -1250.0f;

	for (size_t y = 0; y < level.size(); ++y)
	{
		for (size_t x = 0; x < level[y].size(); ++x)
		{
			if (level[y][x] == 1)
			{
				CubeActor* cube = new CubeActor();
				cube->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 0.0f));
				cube->setScale(cubeSize);
			}
			else if (level[y][x] == 2)
			{
				fps->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 100.0f));
			}
			else if (level[y][x] == 4)
			{
				Door* door = new Door();
				door->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 0.0f));
				door->setScale(Vector3(200.0f, 500.0f, 1000.0f));
			}
			else if (level[y][x] == 5)
			{
				teleporter = new Teleporter();
				teleporter->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 0.0f));
				teleporter->setScale(Vector3(50.0f, 350.0f, 450.0f));
			}
			
		}

		for (size_t y = 0; y < level2.size(); ++y)
		{
			for (size_t x = 0; x < level2[y].size(); ++x)
			{
				if (level2[y][x] == 1)
				{
					CubeActor* cube = new CubeActor();
					cube->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 1100.0f));
					cube->setScale(Vector3(500.0f, 500.0f, 1000.0f));
				}
				else if (level2[y][x] == 3)
				{
					endGame = new EndGame();
					endGame->setPosition(Vector3(startX + x * cubeSize.x, startY + y * cubeSize.y, 850.0f));
					endGame->setScale(Vector3(50.0f, 350.0f, 500.0f));
				}
			}
		}	
	}
	
	// Floor and walls

	// Setup floor
	const float start = -1250.0f;
	const float size = 550.0f;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Setup floor 2
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, 550.0f));
		}
	}

	// Setup floor 3
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, 1100.0f));
		}
	}
	
	// Setup lights
	renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
	
	// HUD
	hud = new HUD();

	/*TargetActor* t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 100.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 400.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, -500.0f, 200.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 500.0f, 200.0f));*/
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

void Game::addCubes(CubeActor* cube)
{
	cubes.emplace_back(cube);
}

void Game::addDoors(Door* door)
{
	doors.emplace_back(door);
}

void Game::removeCubes(CubeActor* cube)
{
	auto iter = std::find(begin(cubes), end(cubes), cube);
	cubes.erase(iter);
}