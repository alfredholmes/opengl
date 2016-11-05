#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "simpleshader.h"
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OPENGL!!!!", 0, 0);
	if(window == 0)
	{
		//handle error
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		//hande error
		return -1;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	SimpleShader shader("res/vert.glsl", "res/frag.glsl");


	if(shader.getError() != 0)
	{
		return -1;
	}

	GLfloat vertices[] = {
		 0.5f,  0.5f,  0.0f,
		 0.5f,  -0.5f, 0.0f,
		-0.5f,  -0.5f, 0.0f,
		-0.5f,  0.8f,  0.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3

	};


	GLuint EBO;
	glGenBuffers(1, &EBO);
	
	GLuint VBO;
	glGenBuffers(1, &VBO);



	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	while(!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		shader.bind();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}