#include "Game.h"

int main(int argc, char** argv)
{
	Game* game = new Game;
	game->Loop();
	glfwTerminate();
	return 0;
}