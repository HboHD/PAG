#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"

#include <iostream>
class Window
{
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	bool init();

	int shaderProgram;

	Shader *ownShader;
	Texture *texture;

	// settings
	const unsigned int SCR_WIDTH = 1024;
	const unsigned int SCR_HEIGHT = 768;

public:
	GLFWwindow* window;
	Window();
	~Window();
};

