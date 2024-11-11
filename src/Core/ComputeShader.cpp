#include "ComputeShader.h"
#include <sstream>
#include <fstream>
#include <iostream>
ComputeShader::ComputeShader(const std::string& shader)
{
	const std::string computeShaderSourcePath = "src/Shaders/Compute/" + shader + ".comp";
	unsigned int cShader = createShader(computeShaderSourcePath);
	createProgram(cShader);
}

ComputeShader::~ComputeShader()
{
	glDeleteProgram(id_);
}

unsigned int ComputeShader::createShader(const std::string& sourcePath)
{
    std::ifstream stream(sourcePath);
    std::string source;

    if (stream)
    {
        std::stringstream shaderStream;
        shaderStream << stream.rdbuf();
        stream.close();
        source = shaderStream.str();
    }
    else
    {
        std::cout << "Failed to read shader at: " << sourcePath << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int shader = glCreateShader(GL_COMPUTE_SHADER);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cerr << "Error compiling shader at path: " << sourcePath << " due to: \n" << log << std::endl;
        return -1;
    }

    return shader;
}

void ComputeShader::createProgram(const unsigned int& shader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, shader);

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(program, 512, NULL, log);
        std::cerr << "Error compiling program: " << log << std::endl;
        return;
    }

    // Shaders can be discarded after linking
    glDeleteShader(shader);
    id_ = program;
}

void ComputeShader::dispatch(GLuint x, GLuint y, GLuint z)
{
    glUseProgram(id_);
    glDispatchCompute(x, y, z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);    
}

void ComputeShader::bindBuffer(const GenericOpenGLBuffer& buffer, const size_t& n)
{
    static unsigned int ssboBindingPoint = 0;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssboBindingPoint, buffer.getId());
    ssboBindingPoint++;
}