#pragma once
#include <GL/glew.h>
#include <string>
#include "OpenGLBuffer.h"

class ComputeShader
{
private:
	unsigned int id_;
	unsigned int createShader(const std::string& sourcePath);
	void createProgram(const unsigned int& shader);

public:
	ComputeShader(const std::string& shader);
	~ComputeShader();
	void dispatch(GLuint x, GLuint y, GLuint z);
	void bindBuffer(const GenericOpenGLBuffer& buffer, const size_t& n);
};

