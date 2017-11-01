#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;

	~Shader();

private:
	void checkCompileErrors(unsigned int shader, string type);
};

