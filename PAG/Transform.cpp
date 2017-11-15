#include "Transform.h"

// create transform
Transform::Transform()
{
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
}

Transform::~Transform()
{
}

void Transform::move(glm::vec3 vector3)
{
	transform = glm::translate(transform, vector3);
}

void Transform::rotate(glm::vec3 vector3)
{
	transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, vector3);
}

void Transform::recreate(glm::vec3 moveVec3, glm::vec3 rotateVec3)
{
	transform = glm::mat4(1.0f);
	move(moveVec3);
	rotate(rotateVec3);
}

void Transform::scale(glm::vec3 vector3)
{
	transform = glm::scale(transform, vector3);
}

glm::mat4 Transform::getTransform()
{
	return transform;
}