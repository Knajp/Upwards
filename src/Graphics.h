#pragma once

extern const char* basicVertexShaderSource;
extern const char* basicFragmentShaderSource;
extern const char* textureVertexShaderSource;
extern const char* textureFragmentShaderSource;

class Shader
{
public:
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
	~Shader() = default;

	unsigned int getID();
private:
	unsigned int ID;
};