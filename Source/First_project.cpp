#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//versiones que uso
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//si uso openGL "core" que tiene funciones modernas, o compatibilidad, que tiene modernas y antiguas
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//crear la ventana
	//cada grupo de 3 valores es una coordenada
	//las coordenadas van entre -1 y 1, el origen esta en el medio de la ventana
	// la parte mas a la izquierda de la ventana es -1 en x, la mas a la derecha 1
	// la parte mas de arriba de la ventana es 1, la mas abajo -1
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f 
	};
	//creo los vertices, y con los indices doy el orden con el cual se van a unir para formar la figura
	GLuint indices[] =
	{
		0,3,5,
		3,2,4,
		5,4,1
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "primerOpengl", NULL, NULL);
		
	if (window == NULL)
	{	
		std::cout << "No se pudo crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//para configurar glad
	gladLoadGL();

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//existen 2 tipos de buffers, el "front" el cual es el que veo en el momento, y el "back" que es el que se esta creando y no se ve.
	glClear(GL_COLOR_BUFFER_BIT);
	
	glfwSwapBuffers(window);

	glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//hay que "compilar" ya a machine code el codigo fuente del shader
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(fragmentShader);

	//para usarlos, tenemos que "unirlos" en un shader program

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	//eliminamos los shaders que creamos porque ya estan en el programa

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//enviar de la cpu a la gpu es lento, por eso mandamos como "buffers", un gran grupo de informacion (no confundir con los otros buffers)
	//vbo = buffer object
	//vao = array object
	//ebo = element array buffer
	GLuint VAO,VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//"bind" objects, esto es como que el objeto que esta "bind", es el principal. Si tenemos una funcion que lo modifique, va a afectar a ese en particular
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	



	//bucle para mantener abierta la ventana
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);

	glDeleteBuffers(1, &VBO);
	
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}