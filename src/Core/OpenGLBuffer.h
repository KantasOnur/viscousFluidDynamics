#pragma once
#include <cassert>

class GenericOpenGLBuffer
{
public:
	GenericOpenGLBuffer() = default;
	~GenericOpenGLBuffer() = default;
	virtual unsigned int getId() const = 0;
};


template <typename T>
class OpenGLBuffer : public GenericOpenGLBuffer
{
private:
	unsigned int m_id;
	GLenum m_type;
public:
	OpenGLBuffer(GLenum type, T* data, const size_t& n, GLenum usage)
		: m_type(type)
	{
		//assert(type == GL_TRANSFORM_FEEDBACK_BUFFER || type == GL_TRANSFORM_FEEDBACK_BUFFER || type = GL_UNIFORM_BUFFER || type = GL_SHADER_STORAGE_BUFFER);
		glGenBuffers(1, &m_id); // generate buffer
		glBindBuffer(type, m_id); // bind buffer to modify
		glBufferData(type, sizeof(T) * n, data, usage); // write to buffer 
	}
	~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}
	unsigned int getId() const override { return m_id; };
	void sendToGpu(const size_t& index)
	{
		glBindBufferBase(m_type, index, m_id);
	}
	void retrieveBuffer(const size_t& offset, const size_t& n, T* data) const
	{
		glGetNamedBufferSubData(m_id, offset, n, data);
	}
};
