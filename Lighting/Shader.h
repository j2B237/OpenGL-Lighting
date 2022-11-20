#ifndef SHADER_H

#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


class Shader
{
public:
	unsigned int ID;

	Shader(const char* vsPath, const char* fsPath);
	~Shader();

	void UseProgram();
	void UseTextureUnit(GLenum type, int value);
	void SetMat4(const std::string& name, glm::mat4 mat);
	void SetVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z);

private:
	GLint CreateShaderFromSrc(const char* shaderPath, GLenum type);
	std::string LoadShaderFromSrc(const char* filename);
};

#endif

