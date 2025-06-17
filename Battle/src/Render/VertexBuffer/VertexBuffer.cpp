#include "VertexBuffer.h"

namespace JF
{
	VertexBuffer::VertexBuffer(size_t size)
	{
		glGenBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_VertexBufferID);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::set_layout(const BufferLayout& layout)
	{
		m_BufferLayout = layout;
	}

	const BufferLayout VertexBuffer::get_layout()
	{
		return m_BufferLayout;
	}

	void VertexBuffer::set_data(const void* data, uint32_t size)
	{
		bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);	//在调用glBufferSubData之前需要先分配内存
	}
}