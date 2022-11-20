#ifndef GAMEOBJECT_H

#define GAMEOBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// Array of vertices

class GameObject
{
public:
	unsigned int VAO, VBO;
	GameObject(float* tab);
	~GameObject();
	void DeleteBuffers();
};

#endif

