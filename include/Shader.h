#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string GetFileContents(const char* filePath);

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexFile, const char* fragmentFile);
	Shader() = default;

	void CreateFromFile(const char* vertexFile, const char* fragmentFile);

	void Activate();

	void Delete();
};