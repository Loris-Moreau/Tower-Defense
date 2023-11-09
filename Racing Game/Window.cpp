#include "Window.h"
#include "Log.h"

bool Window::initialize()
{
	int sdlInitResults = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResults != 0)
	{
		Log::error(LogCategory::Video, "Unable to Initialize SDL");
		return false;
	}
	SDLWindow = SDL_CreateWindow("Window of Eternity", 100, 100, width, height, 0); //0 is a flag we will use later
	if (!SDLWindow)
	{
		Log::error(LogCategory::System, "Failed to create Window");
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}