#include "Log.h"

#include <SDL_log.h>
#include <SDL_error.h>

void Log::info(const string& message)
{
	SDL_Log(message.c_str()); //c_str() ends a String with the \0 character, wich makes it c compatible
}

void Log::error(LogCategory category, const string& message)
{
	SDL_LogError(static_cast<int>(category), "%s | SDL; %s", message.c_str(), SDL_GetError());
}
