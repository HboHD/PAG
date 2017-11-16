#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Transform
{
private:
	glm::mat4 transform;
public:
	void rotate(glm::vec3 vector3, float speed);
	void move(glm::vec3 vector3);
	void recreate(glm::vec3 moveVec3, glm::vec3 rotateVec3);
	void scale(glm::vec3 vector3);

	glm::mat4 getTransform();

	Transform();
	~Transform();
};

