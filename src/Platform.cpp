#include "Platform.h"
#include <glad/glad.h>
#include <iostream>
Platform::Platform(glm::vec2 pos, glm::vec2 size, glm::vec3 color)
	:m_Position(pos), m_Size(size)
{
	m_Vertices =
	{
		{pos.x, pos.y, color.r, color.g, color.b},
		{pos.x + size.x, pos.y, color.r, color.g, color.b},
		{pos.x, pos.y + size.y, color.r, color.g, color.b},
		{pos.x + size.x , pos.y + size.y, color.r, color.g, color.b}
	};
	m_Indices =
	{
		0,1,2,
		2,3,1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(bVertex), m_Vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned short), m_Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Platform::Render()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << std::hex << err << std::dec << std::endl;
	}
}
