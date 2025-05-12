#include "Platform.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
Platform::Platform(glm::vec2 pos, glm::vec2 size)
	:m_Position(pos), m_Size(size)
{
	m_Vertices =
	{
		{0.0f, 0.0f, 0.0f, 0.0f},
		{0.0f + size.x, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f + size.y, 0.0f, 1.0f},
		{0.0f + size.x , 0.0f + size.y, 1.0f, 1.0f}
	};
	m_Indices =
	{
		0,1,2,
		2,3,1
	};

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, {pos.x, pos.y, 0.0f});

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(tVertex), m_Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned short), m_Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
}

void Platform::Render(GLint transLoc)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << std::hex << err << std::dec << std::endl;
	}
}
