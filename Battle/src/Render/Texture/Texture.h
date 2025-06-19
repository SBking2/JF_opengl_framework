#pragma once
#include<glew/glew.h>
#include <cstdint>
#include <string>
namespace JF
{
	class Texture
	{
	public:
		Texture(const std::string& path, bool isFlip = true);
		virtual ~Texture();
		void bind(uint32_t slot);
	private:
		uint32_t m_Slot;	//记录当前纹理绑定在哪个纹理单元中
		uint32_t m_Width, m_Height, m_Channels;
		GLuint m_TextureID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}