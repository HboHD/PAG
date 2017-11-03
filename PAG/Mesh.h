#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh
{
private:
	unsigned int VBO, VAO, EBO;
public:
	Mesh(unsigned int *VBO, unsigned int *VAO, unsigned int *EBO);
	~Mesh();
};

