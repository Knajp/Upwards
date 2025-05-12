#include <glm/glm.hpp>
#include "Structs.h"
#include <vector>

class Platform
{
public:
	Platform(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
	~Platform() = default;
	
	void Render();

	glm::vec2 getPosition();
	glm::vec2 getSize();

private:
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	std::vector<bVertex> m_Vertices;
	std::vector<unsigned short int> m_Indices;
	unsigned int VAO, VBO, EBO;
};