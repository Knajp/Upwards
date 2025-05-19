#include "Game.h"
#include "Graphics.h"
#include "Platform.h"
#include "Texture.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Player.h"
#include "TextRenderer.h"

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

	aspectRatio = (float)mode->width / (float)mode->height;
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Failed to load OpenGL!" << std::endl;

	glViewport(0, 0, mode->width, mode->height);
}
void Game::Loop()
{
	Platform ground({ -2.0f, -1.5f }, { 4.0f, 1.0f });
	Player player;

	Shader basicShader(basicVertexShaderSource, basicFragmentShaderSource);
	Shader textureShader(textureVertexShaderSource, textureFragmentShaderSource);
	Shader textShader(textureVertexShaderSource, textureFragmentShaderSource);

	Texture groundTexture("src/texture/ground.png");
	Texture playerTexture("src/texture/knight.png");


	TextRenderer tRend(aspectRatio);
	glClearColor(0.137f, 0.761f, 0.941f, 1.0f);
	glDisable(GL_CULL_FACE);
	glUseProgram(textureShader.getID());

	GLint transLoc = glGetUniformLocation(textureShader.getID(), "modelMatrix");
	
	GLint projLoc = glGetUniformLocation(textureShader.getID(), "projMatrix");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float prevTime = glfwGetTime();
	float currentTime;
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		float deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);

		glUseProgram(textureShader.getID());

		player.Inputs(window, deltaTime);
		glm::mat4 projection = glm::ortho(player.getPosition().x - aspectRatio, player.getPosition().x + aspectRatio, player.getPosition().y - 0.8f, player.getPosition().y +1.2f, -1.0f, 1.0f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindTexture(GL_TEXTURE_2D, groundTexture.ID);
		ground.Render(transLoc);

		glBindTexture(GL_TEXTURE_2D, playerTexture.ID);
		player.Render(transLoc);

		tRend.RenderText(textShader.getID(), "Hello", 0.0f, 0.0f, 0.01f, {1.0f, 0.0f, 0.0f});

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window, true);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
