#pragma once
#include<glew/glew.h>
#include <cstdint>
#include <iostream>
#include <cassert>
namespace JF
{
	enum class ShaderDataType
	{
		NONE = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	class Utils
	{
	public:
		static uint32_t get_data_size(const ShaderDataType& type) {
			switch (type)
			{
			case ShaderDataType::NONE:
				std::cout << "Unknown Data Type!" << std::endl;
				assert(true);
				return 0;
				break;
			case ShaderDataType::Float:       return 4 * 1;
				break;
			case ShaderDataType::Float2:      return 4 * 2;
				break;
			case ShaderDataType::Float3:      return 4 * 3;
				break;
			case ShaderDataType::Float4:      return 4 * 4;
				break;
			case ShaderDataType::Mat3:        return 4 * 3 * 3;
				break;
			case ShaderDataType::Mat4:        return 4 * 4 * 4;
				break;
			case ShaderDataType::Int:         return 4 * 1;
				break;
			case ShaderDataType::Int2:        return 4 * 2;
				break;
			case ShaderDataType::Int3:        return 4 * 3;
				break;
			case ShaderDataType::Int4:        return 4 * 4;
				break;
			case ShaderDataType::Bool:        return 1 * 1;
				break;
			}
			std::cout << "Unknown Data Type!" << std::endl;
			assert(true);
			return 0;
		}
		static uint32_t get_data_count(const ShaderDataType& type) {
			switch (type)
			{
			case ShaderDataType::NONE:
				std::cout << "Unknown Data Type!" << std::endl;
				assert(true);
				return 0;
				break;
			case ShaderDataType::Float:   return 1;
				break;
			case ShaderDataType::Float2:  return 2;
				break;
			case ShaderDataType::Float3:  return 3;
				break;
			case ShaderDataType::Float4:  return 4;
				break;
			case ShaderDataType::Mat3:    return 3 * 3;
				break;
			case ShaderDataType::Mat4:    return 4 * 4;
				break;
			case ShaderDataType::Int:     return 1;
				break;
			case ShaderDataType::Int2:    return 2;
				break;
			case ShaderDataType::Int3:    return 3;
				break;
			case ShaderDataType::Int4:    return 4;
				break;
			case ShaderDataType::Bool:    return 1;
				break;
			}

			std::cout << "Unknown Data Type!" << std::endl;
			assert(true);
			return 0;
		}
		static GLenum get_opengl_type(const ShaderDataType& type)
		{
			switch (type)
			{
			case ShaderDataType::NONE:
				std::cout << "Unknown Data Type!" << std::endl;
				assert(true);
				return 0;
				break;
			case ShaderDataType::Float:       return GL_FLOAT;
				break;
			case ShaderDataType::Float2:      return GL_FLOAT;
				break;
			case ShaderDataType::Float3:      return GL_FLOAT;
				break;
			case ShaderDataType::Float4:      return GL_FLOAT;
				break;
			case ShaderDataType::Mat3:        return GL_FLOAT;
				break;
			case ShaderDataType::Mat4:        return GL_FLOAT;
				break;
			case ShaderDataType::Int:         return GL_INT;
				break;
			case ShaderDataType::Int2:        return GL_INT;
				break;
			case ShaderDataType::Int3:        return GL_INT;
				break;
			case ShaderDataType::Int4:        return GL_INT;
				break;
			case ShaderDataType::Bool:        return GL_BOOL;
				break;
			}
			std::cout << "Unknown Data Type!" << std::endl;
			assert(true);
			return 0;
		}
	};
}