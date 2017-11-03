#include "Core.h"
using namespace std;
#include <stdio.h>

Core::Core()
{
	DWORD next_game_tick = GetTickCount();
	int loops;
	
	init();

	// GAME LOOP
	game_is_running = true;
	while (game_is_running) {
		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			updateGame();
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		renderGame();
	}
}

void Core::init()
{
	VBO = new unsigned int();
	VAO = new unsigned int();
	EBO = new unsigned int();

	window = new Window();

	// build and compile our shader program
	// ------------------------------------
	shader = new Shader("Shaders/vertex.txt", "Shaders/fragment.txt");

	// create own texture
	texture = new Texture();

	// create mesh
	mesh = new Mesh(VBO, VAO, EBO);
}

// render loop
void Core::renderGame()
{
	// input
	// -----
	processInput(window->window);

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//glBindTexture(GL_TEXTURE_2D, texture->getTexture());

	// drawing triangle
	shader->use();
	glBindVertexArray(*VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window->window);
	glfwPollEvents();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Core::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		cout << "WYCHODZE" << endl;
		glfwSetWindowShouldClose(window, true);
		glfwTerminate();
	}
}

void Core::updateGame()
{
	//TODO
}

Core::~Core()
{
}
