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
	texture = new Texture("wall.jpg");
	stbi_set_flip_vertically_on_load(true);
	texture2 = new Texture("car.jpg");
	///////////// kwadrat, druga tekstura, jedna z tekstur do góry nogami, zwizualizowanie pozycji 
	// create mesh
	mesh = new Mesh(VBO, VAO, EBO);

	shader->use();

	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);
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

	// drawing triangle
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->getTexture());

	glBindVertexArray(*VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
