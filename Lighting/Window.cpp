#include "Window.h"

/***********************************************/

Window::Window()		// Constructeur
{
	if (!glfwInit())
	{
		std::cout << "Impossible d'initialiser GLFW" << std::endl;
	}
	else
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#endif

	}
}

/*********************************************/
Window::~Window(){ }			// Destructeur

/**********************************************/
GLFWwindow* Window::CreateWindow(const std::string& title)
{
	return glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), NULL, NULL);

}

/*********************************************/

bool Window::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	return true;
}
/***********************************************/
