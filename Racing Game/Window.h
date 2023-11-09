#pragma once

#include <SDL.h>

//Screen Dimensions
constexpr int WINDOW_WIDTH = 1024;
constexpr int WINDOW_HEIGHT = 768;

class Window
{
public:
	Window() = default;
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;

	bool initialize();
	void close();

	SDL_Window* getSDLWindow() const { return SDLWindow; } //const Correctness : getters do not modify the object

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow{ nullptr };

	int width{ WINDOW_WIDTH };
	int height{ WINDOW_HEIGHT };
};
