#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>



class Game
{
public:
	Game();
	Game(const Game& game) = delete;
	~Game();

	void Loop();
private:
	GLFWwindow* window;
};
