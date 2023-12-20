#pragma once

#include <vector>

#include "Actor.h"

#include "SpriteComponent.h"

#include "Window.h"
#include "RendererSDL.h"

#include "Grid.h"

#include "Vector2.h"
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
	Game() : isRunning(true), isUpdatingActors(false), grid(nullptr), nextEnemyTimer(0.0f) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	RendererSDL& getRenderer() { return renderer; }

	//Game specific
	class Grid& getGrid() { return *grid; }
	std::vector<class Enemy*>& getEnemies() { return enemies; }
	Enemy* getNearestEnemy(const Vector2& position);

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;

	Window window;
	RendererSDL renderer;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	//Game specific
	Grid* grid;
	std::vector<class Enemy*> enemies;
	float nextEnemyTimer;
};
