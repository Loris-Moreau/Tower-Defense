#pragma once

#include <string>

#include "Renderer.h"

using std::string;

class Texture
{
public:
	Texture() = default;
	~Texture();

	void unload();
	bool load(Renderer& rendererP, const string& filenameP);

	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }

	void updateInfo(int& widthOut, int& heightOut); //Function will be used when an other Object wants to store the Texture width & height. 
	//It will pass a Reference to those Variables & the Texture will Modify Them
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	string filename{ "" };

	SDL_Texture* SDLTexture{ nullptr };

	int width{ 0 };
	int height{ 0 };
};
