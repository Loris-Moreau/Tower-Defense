#pragma once
#include "IRenderer.h"
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"
#include "Vector2.h"
#include "Actor.h"

#include <vector>

class Renderer : public IRenderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	Renderer() = default;
	virtual ~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void draw();
	void endDraw();

	IRenderer::Type type() { return Type::SDL; }

	void drawRect(const Rectangle& rect) const;
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprites();
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	SDL_Renderer* SDLRenderer{ nullptr };

	std::vector<class SpriteComponent*> sprites;
};
