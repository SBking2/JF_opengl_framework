#include "Shader.h"

#include<glm/gtc/type_ptr.hpp>

#include<iostream>
#include<fstream>
#include<vector>
#include <cassert>
namespace JF
{
	Shader::Shader(const std::string& path)
	{
		std::string vertex_src_string;
		std::string fragment_src_string;
		read_file(path, vertex_src_string, fragment_src_string);	//读取Shader文件

		const char* vertex_shader_src = vertex_src_string.c_str();
		const char* fragment_shader_src = fragment_src_string.c_str();

		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
		glCompileShader(vertex_shader);

		//顶点着色器Error日志
		GLint success;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			// 获取错误日志长度
			GLint logLength;
			glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logLength);

			// 读取错误日志
			std::vector<GLchar> errorLog(logLength);
			glGetShaderInfoLog(vertex_shader, logLength, NULL, errorLog.data());

			// 输出错误信息
			std::cerr << "顶点着色器编译失败:\n" << errorLog.data() << std::endl;
		}

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_src, nullptr);
		glCompileShader(fragment_shader);

		//片元着色器Error日志
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			// 获取错误日志长度
			GLint logLength;
			glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &logLength);

			// 读取错误日志
			std::vector<GLchar> errorLog(logLength);
			glGetShaderInfoLog(fragment_shader, logLength, NULL, errorLog.data());

			// 输出错误信息
			std::cerr << "片元着色器编译失败:\n" << errorLog.data() << std::endl;
		}

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertex_shader);
		glAttachShader(m_ShaderProgram, fragment_shader);
		glLinkProgram(m_ShaderProgram);

		GLint validate_success;
		glGetProgramiv(m_ShaderProgram, GL_VALIDATE_STATUS, &validate_success);
		if (!validate_success) {
			GLint logLength;
			glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &logLength);

			std::vector<GLchar> errorLog(logLength);
			glGetProgramInfoLog(m_ShaderProgram, logLength, NULL, errorLog.data());

			std::cerr << "着色器程序验证失败:\n" << errorLog.data() << std::endl;
		}

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void Shader::bind()
	{
		glUseProgram(m_ShaderProgram);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	void Shader::set_unifrom_matrix4(const std::string& name, const glm::mat4& matrix)
	{
		GLuint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::read_file(const std::string& path, std::string& vertexSrc, std::string& fragmentSrc)
	{
		std::ifstream fileStream(path, std::ios::in);

		if (!fileStream.is_open())
		{
			std::cout << "Shader 文件打开失败!" << std::endl;
			assert(true);
		}

		int count = 0;

		std::string line = "";
		while (!fileStream.eof())
		{
			getline(fileStream, line);
			if (line.find("#version") != std::string::npos)
				count++;
			
			//说明读取到了fragmentShader
			if (count > 1)
			{
				fragmentSrc.append(line + "\n");
				break;
			}
			vertexSrc.append(line + "\n");
		}

		while (!fileStream.eof())
		{
			getline(fileStream, line);
			fragmentSrc.append(line + "\n");
		}

		fileStream.close();
	}
}