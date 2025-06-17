#include "VertexArray.h"

namespace JF
{
	VertexArray::VertexArray(uint32_t maxIndexSize)
	{
		glGenVertexArrays(1, &m_VertexArrayID);

		bind();
		m_IndexBuffer = std::make_shared<IndexBuffer>(maxIndexSize);
		unbind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::set_vertex_buffer(VertexBuffer* const& vertexbuffer)
	{
		glBindVertexArray(m_VertexArrayID);		//绑定了VertexArray之后再设置VertexArray Layout
		vertexbuffer->bind();

		int index = 0;
		const auto& layout = vertexbuffer->get_layout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			if (element.dataType == ShaderDataType::Int)
				glVertexAttribIPointer(index, element.dataCount, Utils::get_opengl_type(element.dataType), layout.get_stride()
					, (const void*)element.offset);
			else
				glVertexAttribPointer(index, element.dataCount, Utils::get_opengl_type(element.dataType)
					, element.isNormalized ? GL_TRUE : GL_FALSE, layout.get_stride(), (const void*)element.offset);

			index++;
		}

		glBindVertexArray(0);
	}

	void VertexArray::set_index_buffer(const void* data, uint32_t size, uint32_t count)
	{
		bind();
		m_IndexBuffer->set_data(data, size, count);
		unbind();
	}
}