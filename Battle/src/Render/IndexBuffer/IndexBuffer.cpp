#include "IndexBuffer.h"

namespace JF
{
	IndexBuffer::IndexBuffer(size_t size)
	{
		glGenBuffers(1, &m_IndexBufferID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::set_data(const void* data, uint32_t size, uint32_t count)
	{
		m_Count = count;
		bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);	//在调用glBufferSubData之前需要先分配内存
	}
}