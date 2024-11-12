#include "ComputeShader.h"
#include <sstream>
#include <fstream>
#include <iostream>
ComputeShader::ComputeShader(const std::string& shader)
    : Shader(shader, true) {}

void ComputeShader::dispatch(GLuint x, GLuint y, GLuint z)
{
    glUseProgram(id_);
    glDispatchCompute(x, y, z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);    
}
