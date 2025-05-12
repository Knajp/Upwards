#include "Game.h"
#include "Graphics.h"
#include "Platform.h"
#include "Texture.h"
#include <iostream>

Game::Game()
{
	if (!glfwInit())
		std::cerr << "Failed to initialize GLFW!" << std::endl;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	window = glfwCreateWindow(mode->width, mode->height, "Upwards", NULL, NULL);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Failed to load OpenGL!" << std::endl;

	glViewport(0, 0, mode->width, mode->height);
}
void Game::Loop()
{
	Platform ground({ -1.0f, -1.0f }, { 2.0f, 0.5f }, { 0.106f, 0.89f, 0.267f });
	Shader basicShader(basicVertexShaderSource, basicFragmentShaderSource);
	Shader textureShader(textureVertexShaderSource, textureFragmentShaderSource);
	Texture groundTexture("src/texture/ground.png");

	glClearColor(0.137f, 0.761f, 0.941f, 1.0f);
	glDisable(GL_CULL_FACE);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(textureShader.getID());

		ground.Render();


		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window, true);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
