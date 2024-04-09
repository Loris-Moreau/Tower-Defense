#pragma once

#include <vector>
#include "..\Actors and Components/Actors/Actor.h"
#include "..\Actors and Components/Components/Sprite/SpriteComponent.h"
#include "..\Window/Window.h"
#include "..\Maths/Vector2.h"
#include "..\Window/RendererOGL.h"
#include "..\Inputs/InputSystem.h"
#include "..\Maths/PhysicsSystem.h"
#include "..\Actors and Components/Actors/PlaneActor.h"
#include "..\UI/HUD.h"

using std::vector;

enum class GameState
{
	Gameplay, Pause, Quit
};

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
	Game() : state(GameState::Gameplay), isUpdatingActors(false), fps(nullptr), crosshair(nullptr) {}

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	GameState getState() const { return state; }
	void setState(GameState stateP);

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }
	InputSystem& getInputSystem() { return inputSystem; }
	const vector<UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(UIScreen* screen);
	HUD* getHUD() { return hud; }
	
	// Game-specific
	void addPlane(PlaneActor* plane);
	void removePlane(PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }
	
	class FPSActor* getPlayer() { return fps; }

private:
	void processInput();
	void update(float dt);
	void render();

	GameState state;
	Window window;
	RendererOGL renderer;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;
	vector<UIScreen*> UIStack;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game specific
	FPSActor* fps;
	SpriteComponent* crosshair;
	vector<PlaneActor*> planes;
	HUD* hud;
};

