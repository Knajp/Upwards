#pragma once
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Structs.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Player
{
public:
	Player();
	~Player() = default;

	void Render(GLint transLoc);

	void Inputs(GLFWwindow* window, float deltaTime);
	void Gravity(float deltaTime);

	glm::vec2 getPosition();
private:
	glm::mat4 modelMatrix;
	std::vector<tVertex> m_Vertices;
	std::vector<unsigned short int> m_Indices;
	unsigned int VAO, VBO, EBO;
	glm::vec2 m_Position;
	glm::vec2 m_Velocity;
	bool grounded = false;
};