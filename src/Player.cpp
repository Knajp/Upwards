#include "Player.h"
#include <iostream>

Player::Player()
{
	m_Vertices =
	{
		{-0.05f, 0.0f, 0.0f, 0.0f},
		{0.05f, 0.0f, 1.0f, 0.0f},
		{-0.05f, 0.1f, 0.0f, 1.0f},
		{0.05f, 0.1f, 1.0f, 1.0f}
	};
	m_Indices =
	{
		0,1,2,
		2,1,3
	};

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, { m_Position.x, m_Position.y, 0.0f });

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(tVertex), m_Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned short int), m_Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Player::Render(GLint transLoc)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, { m_Position.x, m_Position.y, 0.0f });

	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

void Player::Inputs(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Velocity.x += 0.01f;
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Velocity.x -= 0.01f;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && grounded)
	{
		m_Position.y += 0.001;
		m_Velocity.y += 4.0f;
		grounded = false;
	}
		
	Gravity(deltaTime);

	m_Position.x += m_Velocity.x * deltaTime;
	m_Position.y += m_Velocity.y * deltaTime;

	m_Velocity.x *= 0.995f;
}

void Player::Gravity(float deltaTime)
{
	const float gravity = 9.81f * deltaTime;

	if (!grounded)
	{
		m_Velocity.y -= gravity;
	}
	if (m_Position.y <= -0.5f)
	{
		m_Velocity.y = 0.0f;
		if (!grounded)
			m_Position.y = -0.5f;
		grounded = true;
	}
}

glm::vec2 Player::getPosition()
{
	return m_Position;
}
