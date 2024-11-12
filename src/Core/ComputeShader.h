#pragma once
#include <GL/glew.h>
#include <string>
#include "OpenGLBuffer.h"
#include "Shader.h"

class ComputeShader : public Shader
{

public:
	ComputeShader(const std::string& shader);
	void dispatch(GLuint x, GLuint y, GLuint z);
};

