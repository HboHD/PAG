#include "Core.h"

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

	//char buf[64];

	// timing
	deltaTime = 0.0f;	// time between current frame and last frame
	lastFrame = 0.0f;

	// cam speed
	cameraSpeed = new float(0.05f);

	window = new Window();

	ImGui_ImplGlfwGL3_Init(window->window, false);

	show_test_window = true;
	show_another_window = false;

	// create camera
	camera = new Camera(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f);

	// build and compile our shader program
	// ------------------------------------
	shader = new Shader("Shaders/vertex.txt", "Shaders/fragment.txt");

	// load models
	// -----------
	ownModel = new Model("Models/nanosuit/nanosuit.obj");
	treeModel = new Model("Models/treeS/models/tree.obj");
	houseModel = new Model("Models/house/House.obj");

	shader->use();

	//shader->setInt("texture1", 0);
	//shader->setInt("texture2", 1);
	//shader->setInt("texture3", 2);

	//glfwSetCursorPosCallback(window->window, camera->mouse_callback);
	//glfwSetScrollCallback(window->window, camera->scroll_callback);
	// world space positions of our cubes

}

// render loop
void Core::renderGame()
{
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui_ImplGlfwGL3_NewFrame();

	static float scale = 1.0f;
	static float rotate = 1.0f;
	ImGui::Text("Hello, world!");
	ImGui::SliderFloat("scale", &scale, 0.0f, 10.0f);
	ImGui::Spacing();
	static int e = 0;
	ImGui::RadioButton("X", &e, 0); ImGui::SameLine();
	ImGui::RadioButton("Y", &e, 1); ImGui::SameLine();
	ImGui::RadioButton("Z", &e, 2);
	ImGui::SliderFloat("rotation", &rotate, 0.0f, 360.0f);
	ImGui::Spacing();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	// per-frame time logic
	// --------------------
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// input
	// -----
	processInput(window->window);

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
	// zatrzymac uklad, ruch kamery do plaszczyzny xz, macierz rotacji w stronê kamery
	shader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)window->getScrWidth() / (float)window->getScrHeight(), 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
	shader->setMat4("model", model);
	ownModel->Draw(*shader);

	// render the loaded model
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.0f, -1.5f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
	shader->setMat4("model", model);
	ownModel->Draw(*shader);

	// render the loaded model
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, -1.5f, -4.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
	shader->setMat4("model", model);
	ownModel->Draw(*shader);

	// render the loaded model
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-2.0f, -1.5f, -2.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(scale, scale, scale));	// it's a bit too big for our scene, so scale it down
	glm::vec3 rotateVector;
	switch (e)
	{
	case 0:
		rotateVector = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 1:
		rotateVector = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case 2:
		rotateVector = glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	default:
		rotateVector = glm::vec3(0.0f);
		break;
	}
	model = glm::rotate(model, glm::radians(rotate), rotateVector);
	shader->setMat4("model", model);
	treeModel->Draw(*shader);

	// render the loaded model
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(5.0f, -1.5f, -8.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));	// it's a bit too big for our scene, so scale it down
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 0.8f, 0.0f));
	shader->setMat4("model", model);
	houseModel->Draw(*shader);

	ImGui::Render();

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
		ImGui_ImplGlfwGL3_Shutdown();
		glfwSetWindowShouldClose(window, true);
		glfwTerminate();
	}

	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
	//	// Convert "i", the integer mesh ID, into an RGB color
	//	int r = (i & 0x000000FF) >> 0;
	//	int g = (i & 0x0000FF00) >> 8;
	//	int b = (i & 0x00FF0000) >> 16;

	//	// OpenGL expects colors to be in [0,1], so divide by 255.
	//	glUniform4f(pickingColorID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	//}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->ROTUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->ROTDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->ROTLEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->ProcessKeyboard(camera->ROTRIGHT, deltaTime);

}

void Core::updateGame()
{
	//ImGui::Text("Hello %d", 123);

	//if (ImGui::Button("PRESSME"))
	//{
	//	//dosmth
	//}

	//ImGui::InputText("string", buf, 256);
	//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

	//transform->rotate(glm::vec3(0.0f, 0.0f, 1.0f), 0.01f);
}

Core::~Core()
{
}
