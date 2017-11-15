#pragma once
#include <Windows.h>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class Core
{
private:
	Window *window;
	Texture *texture;
	Texture *texture2;
	Mesh *mesh;
	Shader *shader;
	bool game_is_running;
	const int TICKS_PER_SECOND = 50;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 10;

	unsigned int *VBO, *VAO, *EBO;

	void init();
	void updateGame();
	void processInput(GLFWwindow *window);
	void renderGame();
public:
	Core();
	~Core();
};
