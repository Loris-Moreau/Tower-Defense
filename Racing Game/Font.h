#pragma once

#include <string>
using std::string;

#include "Vector3.h"
#include "Color.h"

#include <SDL_ttf.h>
#include <unordered_map>

class Font
{
public:
	Font();
	~Font();
	
	static bool initialize();
	static void close();
	void unload();
	
	class Texture* renderText(const string& text, const Vector3& color = Color::white, int pointSize = 10);
	void addFontData(int size, TTF_Font* fontSize);
	
private:
	// Each font stores TTF fonts for all point sizes
	std::unordered_map<int, TTF_Font*> fontData;
};
