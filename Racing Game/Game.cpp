#include "Game.h"

#include "Actor.h"

#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"

#include "Timer.h"

#include "Assets.h"
#include "Enemy.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; //Return bool && bool && bool ...to detect error
}

void Game::load()
{
	//Load textures
	//Load Textures
	string filePath = "..\\Assets\\";
	string filePathRes1 = filePath + "Res_005-011\\";
	string filePathRes2 = filePath + "Res_012-015\\";
	string filePathRes3 = filePath + "Res_016-025\\";

	Assets::loadTexture(renderer, (filePathRes2 + "Airplane.png"), "Airplane");
	Assets::loadTexture(renderer, (filePathRes2 + "Base.png"), "Base");

	Assets::loadTexture(renderer, (filePathRes2 + "Missile.png"), "Missile");
	Assets::loadTexture(renderer, (filePathRes2 + "Projectile.png"), "Projectile");

	Assets::loadTexture(renderer, (filePathRes2 + "Tower.png"), "Tower");
	//Tiles
	Assets::loadTexture(renderer, (filePathRes2 + "TileBrown.png"), "TileBrown");
	Assets::loadTexture(renderer, (filePathRes2 + "TileBrownSelected.png"), "TileBrownSelected");

	Assets::loadTexture(renderer, (filePathRes2 + "TileGreen.png"), "TileGreen");
	//Assets::loadTexture(renderer, (filePathRes2 + "TileGreenSelected.png"), "TileGreenSelected");

	Assets::loadTexture(renderer, (filePathRes2 + "TileGrey.png"), "TileGrey");
	Assets::loadTexture(renderer, (filePathRes2 + "TileGreySelected.png"), "TileGreySelected");

	Assets::loadTexture(renderer, (filePathRes2 + "TileTan.png"), "TileTan");
	//Assets::loadTexture(renderer, (filePathRes2 + "TileTanSelected.png"), "TileTanSelected");

	Assets::loadTexture(renderer, (filePathRes2 + "TileRed.png"), "TileRed");
	Assets::loadTexture(renderer, (filePathRes2 + "TileRedSelected.png"), "TileRedSelected");

	grid = new Grid();
}

Enemy* Game::getNearestEnemy(const Vector2& position)
{
	Enemy* best = nullptr;

	if (enemies.size() > 0)
	{
		best = enemies[0];
		//Save the distance squared of first enemy, and test if others are closer
		float bestDistSq = (position - enemies[0]->getPosition()).lengthSq();
		for (size_t i = 1; i < enemies.size(); ++i)
		{
			float newDistSq = (position - enemies[i]->getPosition()).lengthSq();
			if (newDistSq < bestDistSq)
			{
				bestDistSq = newDistSq;
				best = enemies[i];
			}
		}
	}

	return best;
}

void Game::processInput()
{
	//SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	//Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	//Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	if (keyboardState[SDL_SCANCODE_B])
	{
		grid->buildTower();
	}

	//Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;

	//Process mouse
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		grid->processClick(x, y);
	}
}

void Game::update(float dt)
{
	//Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	//Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//Delete dead actors
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
	//Delete actors
	//Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	//Resources clear
	Assets::clear();
}

void Game::close()
{
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
	//Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		//Swap to end of vector and pop off (avoid erase copies)
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
