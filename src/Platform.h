#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Structs.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

class Platform
{
public:
	Platform(glm::vec2 pos, glm::vec2 size);
	~Platform() = default;
	
	void Render(GLint transLoc);

	glm::vec2 getPosition();
	glm::vec2 getSize();

private:
	glm::mat4 modelMatrix;
	glm::vec2 m_Position;
	glm::vec2 m_Size;
	std::vector<tVertex> m_Vertices;
	std::vector<unsigned short int> m_Indices;
	unsigned int VAO, VBO, EBO;
};