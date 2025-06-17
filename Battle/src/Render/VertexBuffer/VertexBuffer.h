#pragma once
#include "BufferLayout.h"
#include<glew/glew.h>
namespace JF
{
	class VertexBuffer
	{
	public:
		VertexBuffer(size_t size);
		virtual ~VertexBuffer();
		void bind();
		void unbind();
		void set_layout(const BufferLayout& layout);
		const BufferLayout get_layout();
		void set_data(const void* data, uint32_t size);
	private:
		GLuint m_VertexBufferID;
		BufferLayout m_BufferLayout;
	};
}