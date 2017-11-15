#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

using namespace std;

class Texture
{
private:
	unsigned int texture;
public:
	unsigned int getTexture();

	Texture(const char* filename);
	~Texture();
};

