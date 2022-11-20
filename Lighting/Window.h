#ifndef WINDOW_H

#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

// Constantes 
const int WIDTH		= 800;
const int HEIGHT	= 600;

class Window
{
public:

	Window();
	~Window();
	GLFWwindow* CreateWindow(const std::string& title);
	bool InitGlad();
};

#endif
