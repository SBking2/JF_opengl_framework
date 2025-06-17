#pragma once
#include "Render/VertexBuffer/VertexBuffer.h"
#include "Render/IndexBuffer/IndexBuffer.h"
#include<glew/glew.h>
#include <memory>
namespace JF
{
	class VertexArray
	{
	public:
		VertexArray(uint32_t maxIndexSize);
		virtual ~VertexArray();
		void bind();
		void unbind();
		void set_vertex_buffer(VertexBuffer* const& vertexbuffer);
		void set_index_buffer(const void* data, uint32_t size, uint32_t count);
		inline uint32_t get_index_count() const { return m_IndexBuffer->get_count(); }
	private:
		GLuint m_VertexArrayID;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}