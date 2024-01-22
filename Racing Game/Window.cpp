#include "Window.h"
#include "Log.h"

#include <GL/glew.h>

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) 
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL");

		return false;
	}

	SDLWindow = SDL_CreateWindow("OpenGL Rendering", 100, 100, width, height, SDL_WINDOW_OPENGL); //0 is flag we will use later
	if (!SDLWindow)
	{
		Log::error(LogCategory::System, "Failed to create window");

		return false;
	}

	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}
