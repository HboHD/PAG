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
	// buffers
	VBO = new unsigned int();
	VAO = new unsigned int();
	EBO = new unsigned int();

	// cam speed
	cameraSpeed = new float(0.05f);

	window = new Window();

	// create camera
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f,  0.0f);

	// build and compile our shader program
	// ------------------------------------
	shader = new Shader("Shaders/vertex.txt", "Shaders/fragment.txt");

	// create own texture
	texture = new Texture("sun.jpg");
	stbi_set_flip_vertically_on_load(true);
	texture2 = new Texture("car.jpg");
	texture3 = new Texture("wall.jpg");

	// create mesh
	mesh = new Mesh(VBO, VAO, EBO);

	// create transform
	transform = new Transform();
	transform->scale(glm::vec3(0.5f, 0.5f, 0.5f));

	shader->use();

	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);
	shader->setInt("texture3", 2);

	//glfwSetCursorPosCallback(window->window, camera->mouse_callback);
	//glfwSetScrollCallback(window->window, camera->scroll_callback);
	// world space positions of our cubes

}

// render loop
void Core::renderGame()
{
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  -0.6f, 0.0f),
		glm::vec3(4.0f,  2.0f,  0.0f),
		glm::vec3(6.0f, 0.0f, 0.0f),
		glm::vec3(8.0f, 0.0f, 0.0f),
		glm::vec3(10.0f,  -0.3f, 0.0f),
		glm::vec3(12.0f,  1.4f, 0.0f),
		glm::vec3(14.0f,  -1.9f, 0.0f),
		glm::vec3(16.0f,  0.0f, 0.0f),
		glm::vec3(18.0f,  -1.4f, 0.0f)
	};

	// input
	// -----
	processInput(window->window);

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	shader->use();

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)window->getScrWidth() / (float)window->getScrHeight(), 0.1f, 100.0f);
	shader->setMat4("projection", projection);

	// camera/view transformation
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("view", view);

	// render boxes
	glBindVertexArray(*VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f;
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			//model = glm::rotate(model, glm::radians(angle) * (GLfloat)glfwGetTime() * 0.3f, glm::vec3(0.0f, 0.5f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			//model = glm::rotate(model, glm::radians(angle * i) * (GLfloat)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.7f, 0.7f));
			shader->setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getTexture());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else if(i%2 == 1)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f;
			model = glm::scale(model, glm::vec3(1.0f * i/10, 1.0f * i / 10, 1.0f* i / 10));
			model = glm::rotate(model, glm::radians(angle) * (GLfloat)glfwGetTime() * 0.1f * i, glm::vec3(0.0f, 0.5f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle * i) * (GLfloat)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.7f, 0.7f));
			shader->setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture2->getTexture());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f;
			model = glm::scale(model, glm::vec3(1.0f * i / 10, 1.0f * i / 10, 1.0f* i / 10));
			model = glm::rotate(model, glm::radians(angle) * (GLfloat)glfwGetTime() * 0.1f * i, glm::vec3(0.0f, 0.5f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle * i) * (GLfloat)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.7f, 0.7f));
			shader->setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture3->getTexture());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->FORWARD, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->BACKWARD, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->LEFT, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->RIGHT, 1.0f);
}

void Core::updateGame()
{
	//transform->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 0.01f);
}

Core::~Core()
{
}
