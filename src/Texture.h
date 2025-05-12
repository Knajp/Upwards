#pragma once
#include "stb_image.h"

class Texture
{
public:
	Texture(const char* filePath);
	unsigned int ID;
	int width, height, numColCh;
};