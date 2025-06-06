#include "Graphics.h"
#include <glad/glad.h>
#include <iostream>
const char* basicVertexShaderSource =
R"(
#version 430 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out vec3 outColor;
void main()
{
	gl_Position = vec4(aPos, 0.0, 1.0);
	outColor = aColor;
}
)";

const char* basicFragmentShaderSource =
R"(
#version 430 core

in vec3 outColor;
out vec4 FragColor;
void main()
{
	FragColor = vec4(outColor, 1.0);
}
)";

const char* textureVertexShaderSource = 
R"(
#version 430 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
out vec2 tCoord;
void main()
{
	gl_Position = projMatrix * modelMatrix * vec4(aPos, 0.0, 1.0);
	tCoord = texCoord;
}
)";

const char* textureFragmentShaderSource =
R"(
#version 430 core
out vec4 FragColor;
in vec2 tCoord;
uniform sampler2D txt;
void main()
{
	vec4 texColor = texture(txt, tCoord);
	if(texColor.a == 0) discard;
	FragColor = texColor; 
}
)";

const char* textVertexShaderSource =
R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec tCoord; 
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = tCoord;
} 
)";

const char* textFragmentShaderSource =
R"(
#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
} 
)";
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::getID()
{
	return ID;
}
