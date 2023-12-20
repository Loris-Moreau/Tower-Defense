#pragma once

#include <string>
using std::string;

#include <SDL_log.h>

enum class LogCategory //Enums are integers, From 0 by Default
{
	Application = SDL_LOG_CATEGORY_APPLICATION,
	Assert = SDL_LOG_CATEGORY_ASSERT,
	Audio = SDL_LOG_CATEGORY_AUDIO,
	Error = SDL_LOG_CATEGORY_ERROR,
	Input = SDL_LOG_CATEGORY_INPUT,
	Render = SDL_LOG_CATEGORY_RENDER,
	System = SDL_LOG_CATEGORY_SYSTEM,
	Test = SDL_LOG_CATEGORY_TEST,
	Video = SDL_LOG_CATEGORY_VIDEO
};

class Log
{
public:
	Log() = delete;
	Log(const Log&) = delete;
	Log& operator = (const Log&) = delete; //Delete Default & Copy Constructor & Assignement Operator so they cannot be used

	static void info(const string& message);
	static void error(LogCategory category, const string& message);
};
