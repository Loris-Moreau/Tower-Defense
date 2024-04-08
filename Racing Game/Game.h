#pragma once
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Vector2.h"
#include "RendererOGL.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "PlaneActor.h"

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
	void unload() const;
	void close();

	GameState getState() const { return state; }
	void setState(GameState stateP);
	
	void addActor(Actor* actor);
	void removeActor(const Actor* actor);
	RendererOGL& getRenderer() { return renderer; }
	PhysicsSystem& getPhysicsSystem() { return physicsSystem; }
	
	InputSystem& getInputSystem() { return inputSystem; }
	
	const vector<class UIScreen*>& getUIStack() { return UIStack; }
	void pushUI(UIScreen* screen);
	
	// Game-specific
	void addPlane(PlaneActor* plane);
	void removePlane(const PlaneActor* plane);
	vector<PlaneActor*>& getPlanes() { return planes; }


private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	RendererOGL renderer;
	InputSystem inputSystem;
	PhysicsSystem physicsSystem;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	GameState state;
	
	// Game specific
	class FPSActor* fps;
	class FollowActor* follow;
	class OrbitActor* orbit;
	class SplineActor* path;
	class SpriteComponent* crosshair;
	vector<PlaneActor*> planes;

	vector<UIScreen*> UIStack;
};
