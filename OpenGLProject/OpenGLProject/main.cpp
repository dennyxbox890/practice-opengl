#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <shader.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
using namespace glm;
using namespace std;
int main() {
	if (!glfwInit()) {
		cout << "failed glewinit" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4xAA
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window;
	// open a window and create contest
	window = glfwCreateWindow(
		1024, 768, "GLtest", NULL, NULL); // resolution, titlebar and GLFWwindow

	if (window == NULL) // check window
	{
		cout << "window failed" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		cout << "glew failed" << endl;
		return -1;
	}

	glfwSetInputMode(
		window, GLFW_STICKY_KEYS, GL_TRUE); // using glfw to capture key event
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);   // screen background color(r,g,b,a)
	// create VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	// compile our GLSL shaders
	GLuint programID = LoadShaders(
		"SimpleVertexShader.vertexshader",
		"SimpleFragmentShader.fragmentshader");
	// create 3d vertex data
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f,
		-0.5f,
		0.0f,
		0.5f,
		-0.5f,
		0.0f,
		0.0f,
		0.5f,
		0.0f,
	};
	//³»ÂI½w½Ä¹ï¶HVBO
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(g_vertex_buffer_data),
		g_vertex_buffer_data,
		GL_STATIC_DRAW);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0, // attribute 0. No particular reason for 0, but must match the
			   // layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void*)0 // array buffer offset
		);
		glDrawArrays(
			GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glfwTerminate();
	return 0;
}