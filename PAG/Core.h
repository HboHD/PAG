#pragma once
#include <Windows.h>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class Core
{
private:
	Window *window;
	Texture *texture;
	Texture *texture2;
	Mesh *mesh;
	Shader *shader;
	Transform *transform;
	Camera camera;
	bool game_is_running;
	const int TICKS_PER_SECOND = 50;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 10;

	unsigned int *VBO, *VAO, *EBO;
	float *cameraSpeed;
	bool firstMouse;
	GLfloat lastX, lastY;
	float yaw, pitch;

	void init();
	void updateGame();
	void processInput(GLFWwindow *window);
	void renderGame();
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
public:
	Core();
	~Core();
};
