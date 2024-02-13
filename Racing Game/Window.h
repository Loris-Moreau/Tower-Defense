#pragma once

#include <SDL.h>

const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;
//Screen Resolutions : 
//						1366 by 768
//						1600 by 900
//						1920 by 1080

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	bool initialize();
	void close();

	SDL_Window* getSDLWindow() const { return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow;
	int width;
	int height;
};
