#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader
{
public:
	// ID program object
	unsigned int ID;

	// konstruktor czyta plik shadera z dysku i tworzy go
	Shader(const char* vertexPath, const char* fragmentPath);
	// aktywuj shader
	void use();
	// funkcje operuj¹ce na uniformach
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;

	~Shader();

private:
	void checkCompileErrors(unsigned int shader, string type);
};

