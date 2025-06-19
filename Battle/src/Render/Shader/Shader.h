#pragma once
#include<glew/glew.h>
#include<string>
#include<glm/glm.hpp>
namespace JF
{
	class Shader
	{
	public:
		Shader(const std::string& path);
		virtual ~Shader();
		void bind();
		void unbind();
	public:
		void set_uniform_matrix4(const std::string& name, const glm::mat4& matrix);
		void set_uniform_Int(const std::string& name, const int& value);
		void set_uniform_IntArray(const std::string& name, int* values, uint32_t count);
	private:
		void read_file(const std::string& path, std::string& vertexSrc, std::string& fragmentSrc);
	private:
		GLuint m_ShaderProgram;
	};
}