#pragma once
#include <Windows.h>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"

#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "ImGui\imgui_impl_glfw_gl3.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdio.h>

using namespace std;

class Core
{
private:
	Window *window;
	Texture *texture;
	Texture *texture2;
	Texture *texture3;
	Mesh *mesh;
	Shader *shader;
	Transform *transform;
	Camera *camera;
	Model *ownModel;
	Model *treeModel;
	Model *houseModel;
	bool game_is_running;
	const int TICKS_PER_SECOND = 50;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 10;

	unsigned int *VBO, *VAO, *EBO;
	float *cameraSpeed;
	float yaw, pitch;
	float deltaTime, lastFrame;
	char buf[64];
	bool show_test_window;
	bool show_another_window;
	ImGuiIO io;

	void init();
	void updateGame();
	void processInput(GLFWwindow *window);
	void renderGame();
public:
	Core();
	~Core();
};
