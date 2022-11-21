/*
	Deuxieme partie du livre Learn OpenGL
	Dans cette partie, je vais tester les 
	couleurs, comment gérer l'éclairage 
	d'une scene à partir d'une source 
	lumineuse et gérer le rendu de couleur
	sur les objets éclairés.
	Pour faire simple, tout le code sera dans
	le fichier main.cpp

*/


// TODO : ADD ANIMATION AND DEAR IMGUI
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "GameObject.h"
#include "Camera.h"

/****************************************************/

void frameBufferCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void sroll_callBack(GLFWwindow* window, double xOffset, double yOffset);

/****************************************************/

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// Timing 
float deltaTime = 0.0f;
float lastFrame = 0.0f;


// Create a camera and place object at 5cm away from it
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), -90.0f, 0.0f, 45);


/***************************************************/
int main(int argc, char* argv[])
{
	std::cout << "Hello OpenGL World !!!\n";


	Window window;
	GLFWwindow* win = window.CreateWindow("Lighting tutorial");

	if (win == NULL)
	{
		std::cout << "Echec lors de la création de la fénètre" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(win);
	glfwSetFramebufferSizeCallback(win, frameBufferCallback);
	
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetScrollCallback(win, sroll_callBack);
	
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	if (!window.InitGlad())
	{
		std::cout << "GLAD: Echec lors du chargement des fonctions de pointeurs" << std::endl;
	}


	glEnable(GL_DEPTH_TEST);

	// Creation de programme shader
	Shader cubeShader("assets/lighting_object_vertex_shader.glsl", "assets/lighting_object_fragment_shader.glsl");
	Shader lightShader("assets/light_source_vertex_shader.glsl", "assets/light_source_fragment_shader.glsl");

	// Creation de buffers

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

	};

	GLfloat normals[] = {

			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,

			0.0f,  0.0f, 1.0f,
			0.0f,  0.0f, 1.0f,
			0.0f,  0.0f, 1.0f,
			0.0f,  0.0f, 1.0f,
			0.0f,  0.0f, 1.0f,
			0.0f,  0.0f, 1.0f,

			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,

			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,

			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,

			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f
	};


	GameObject cubeObject(vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeObject.VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	GameObject lightObject(vertices);						// Represent light source object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(lightObject.VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals attributes pointer 
	// Use it here bc instanciation of lightObject create a new Vertex buffer object so the first call to store vertex array data is redefine
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	
	// Game loop
	while (!glfwWindowShouldClose(win))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input
		processInput(win);

		// Render stuff
		glClearColor(0.1f, 0.1f, 0.1f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Transformation matrix
		glm::mat4 model			= glm::mat4(1.0f);
		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);

		glm::vec3 lightPos		= glm::vec3(1.2f, 1.0f, 2.0f);


		// Active uniform for cube object
		cubeShader.UseProgram();
		cubeShader.SetVec3("objectColor", 0.3f, 0.5f, 0.31f);
		cubeShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		cubeShader.SetVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

		projection	=	glm::perspective(glm::radians(camera.Zoom_), (float)(WIDTH / HEIGHT), 0.1f, 200.0f);
		view		=	camera.GetViewMatrix();

		cubeShader.SetMat4("projection", projection);
		cubeShader.SetMat4("view", view);

		// World transformation
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		cubeShader.SetMat4("model", model);

		// Draw cube object
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Active uniform for light source object
		lightShader.UseProgram();

		projection	=	glm::perspective(glm::radians(camera.Zoom_), (float)(WIDTH / HEIGHT), 0.1f, 200.0f);
		view		=	camera.GetViewMatrix();

		lightShader.SetMat4("projection", projection);
		lightShader.SetMat4("view", view);

		model		=	glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.5f));
		model		=	glm::translate(model, lightPos);
		model		=	glm::scale(model, glm::vec3(0.5f));

		lightShader.SetMat4("model", model);
		

		// Draw light source
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Catch events
		glfwSwapBuffers(win);
		glfwPollEvents();

	}
	
	cubeObject.DeleteBuffers();
	lightObject.DeleteBuffers();

	glfwTerminate();
	return EXIT_SUCCESS;
}

/******************************************************/

void frameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/************************************************************/

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(MOVEMENT::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(MOVEMENT::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(MOVEMENT::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(MOVEMENT::RIGHT, deltaTime);
	}
}

/***********************************************************/

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	float xPosIn = static_cast<float>(xPos);
	float yPosIn = static_cast<float>(yPos);

	if (firstMouse)
	{
		lastX = xPosIn;
		lastY = yPosIn;
		firstMouse = false;
	}

	float xOffset = xPosIn - lastX;
	float yOffset = lastY - yPosIn;

	lastX = xPosIn;
	lastY = yPosIn;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

/*******************************************************/
void sroll_callBack(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yOffset));
}


/******************************************************/