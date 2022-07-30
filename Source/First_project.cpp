#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//versiones que uso
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//si uso openGL "core" que tiene funciones modernas, o compatibilidad, que tiene modernas y antiguas
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "primerOpengl", NULL, NULL);
		
	if (window == NULL)
	{	
		std::cout << "No se pudo crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}