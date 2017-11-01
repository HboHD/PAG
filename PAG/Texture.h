#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
private:
	unsigned int texture;
public:
	unsigned int getTexture();
	Texture();
	~Texture();
};

