#include "GameObject.h"

/******************************************/
GameObject::GameObject(float* tab)			// Constructeur
{
	// Generate buffer for object position to the scene
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// Define buffer position to be the one operations will be apply on
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

}

/***************************************/

GameObject::~GameObject(){}				// Destructeur

/***************************************/

void GameObject::DeleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

/**************************************/
