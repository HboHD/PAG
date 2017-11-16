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

	// mouse things
	firstMouse = true;
	lastX = window->getScrWidth() / 2.0f;
	lastY = window->getScrHeight() / 2.0f;

	// create camera
	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f,  0.0f);

	// build and compile our shader program
	// ------------------------------------
	shader = new Shader("Shaders/vertex.txt", "Shaders/fragment.txt");

	// create own texture
	texture = new Texture("wall.jpg");
	stbi_set_flip_vertically_on_load(true);
	texture2 = new Texture("car.jpg");

	// create mesh
	mesh = new Mesh(VBO, VAO, EBO);

	// create transform
	transform = new Transform();
	transform->scale(glm::vec3(0.5f, 0.5f, 0.5f));

	shader->use();

	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	//glfwSetCursorPosCallback(window->window, mouse_callback);
	//glfwSetScrollCallback(window->window, scroll_callback);
	// world space positions of our cubes

}

// render loop
void Core::renderGame()
{
	glm::vec3 cubePositions[] = {
		glm::vec3(-8.0f,  -0.9f,  0.0f),
		glm::vec3(-6.0f,  -0.6f, 0.0f),
		glm::vec3(-4.0f,  2.0f,  0.0f),
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f,  -0.3f, 0.0f),
		glm::vec3(4.0f,  1.4f, 0.0f),
		glm::vec3(6.0f,  -1.9f, 0.0f),
		glm::vec3(8.0f,  0.0f, 0.0f),
		glm::vec3(10.0f,  -1.4f, 0.0f)
	};

	// input
	// -----
	processInput(window->window);

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	shader->use();

	// applying textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2->getTexture());

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)window->getScrWidth() / (float)window->getScrHeight(), 0.1f, 100.0f);
	shader->setMat4("projection", projection);

	// camera/view transformation
	glm::mat4 view = camera.GetViewMatrix();
	shader->setMat4("view", view);

	// render boxes
	glBindVertexArray(*VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i == 4)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);;
			float angle = 20.0f;
			//model = glm::rotate(model, glm::radians(angle) * (GLfloat)glfwGetTime() * 0.3f, glm::vec3(0.0f, 0.5f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			//model = glm::rotate(model, glm::radians(angle * i) * (GLfloat)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.7f, 0.7f));
			shader->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		else
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);;
			float angle = 20.0f;
			model = glm::rotate(model, glm::radians(angle) * (GLfloat)glfwGetTime() * 0.3f, glm::vec3(0.0f, 0.5f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle * i) * (GLfloat)glfwGetTime() * 0.1f, glm::vec3(0.0f, 0.7f, 0.7f));
			shader->setMat4("model", model);

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
		camera.ProcessKeyboard(camera.FORWARD, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.BACKWARD, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.LEFT, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.RIGHT, 1.0f);
}

void Core::updateGame()
{
	//transform->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 0.01f);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Core::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if (firstMouse)
	//{
	//	lastX = xpos;
	//	lastY = ypos;
	//	firstMouse = false;
	//}

	//float xoffset = xpos - lastX;
	//float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	//lastX = xpos;
	//lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Core::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

Core::~Core()
{
}
