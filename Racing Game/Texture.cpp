#pragma once

#include <map>

#include <string>

#include "Texture.h"

using std::map;
using std::string;


Texture::~Texture()
{
}

void Texture::unload()
{
}

bool Texture::load(Renderer& rendererP, const string& filenameP)
{
    return false;
}

void Texture::updateInfo(int& widthOut, int& heightOut)
{
}
