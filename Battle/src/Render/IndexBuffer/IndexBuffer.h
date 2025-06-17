#pragma once
#include<glew/glew.h>
#include <cstdint>
namespace JF
{
	class IndexBuffer
	{
	public:
		IndexBuffer(size_t size);
		~IndexBuffer();
		void bind();
		void unbind();
		void set_data(const void* data, uint32_t size, uint32_t count);
		inline uint32_t get_count() const { return m_Count; }
	private:
		GLuint m_IndexBufferID;
		uint32_t m_Count;
	};
}