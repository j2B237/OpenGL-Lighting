#include "Shader.h"

/**************************************************************/

Shader::Shader(const char* vsPath, const char* fsPath)
{
	int success;
	char infoLog[512];

	GLint vsId = CreateShaderFromSrc(vsPath, GL_VERTEX_SHADER);
	GLint fsId = CreateShaderFromSrc(fsPath, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();

	// Attach shader and program
	glAttachShader(ID, vsId);
	glAttachShader(ID, fsId);

	// link programm
	glLinkProgram(ID);

	// Catch linking error
	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Shader program Error : " << infoLog << std::endl;
	}
}

/*************************************************************/
Shader::~Shader(){}				// Destructeur

/**************************************************************/

void Shader::UseProgram()
{
	glUseProgram(ID);
}

/*************************************************************/

void Shader::UseTextureUnit(GLenum type, int value)
{

}

/*************************************************************/

void Shader::SetMat4(const std::string& name, glm::mat4 mat)
{
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(mat));
}

/****************************************************************/

void Shader::SetVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z)
{
	GLint location = glGetUniformLocation(this->ID, name.c_str());
	glUniform3f(location, x, y, z);
}

/*****************************************************************/
// private
GLint Shader::CreateShaderFromSrc(const char* shaderPath, GLenum type)
{
	int success;
	char infoLog[512];

	GLint sId = glCreateShader(type);
	
	std::string shaderFromSrc = LoadShaderFromSrc(shaderPath);
	const GLchar* shader = shaderFromSrc.c_str();

	glShaderSource(sId, 1, &shader, NULL);
	glCompileShader(sId);

	glGetShaderiv(sId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(sId, 512, NULL, infoLog);
		std::cout << "Shader " << type << ", Error : " << infoLog << std::endl;
	}

	return sId;
}

/*************************************************************/

std::string Shader::LoadShaderFromSrc(const char* filename)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string rep = "";

	file.open(filename);

	if (file.is_open())
	{
		buffer << file.rdbuf();
		rep = buffer.str();
	}
	else
	{
		std::cout << "Impossible d'ouvrir le fichier : " << filename << std::endl;
	}

	return rep;
}

/***************************************************************/
