#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
namespace JF
{
	Renderer::Renderer(size_t width, size_t height)
	{
		m_Camera = std::make_shared<Camera>(width, height);
		m_Shader = std::make_shared<Shader>("assets/shader/normal_shader");

		float vertices[] = {
			 0.0f,  0.5f, 0.0f, // 上顶点
			-0.5f, -0.5f, 0.0f, // 左下
			 0.5f, -0.5f, 0.0f  // 右下
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		// 绑定VAO
		glBindVertexArray(VAO);

		// 绑定并设置VBO数据
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	Renderer::~Renderer()
	{
		// 清理资源
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Renderer::on_update()
	{

	}

	void Renderer::on_render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//设置Clear时使用的颜色
		glClear(GL_COLOR_BUFFER_BIT);	//Clear

		// 绘制三角形
		m_Shader->bind();
		m_Shader->set_unifrom_matrix4("projection", m_Camera->get_view_projection_matrix());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Renderer::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Renderer::on_key_pressed, this, std::placeholders::_1));

		m_Camera->on_event(e);
	}

	void Renderer::on_key_pressed(KeyPressedEvent& e)
	{
	}

	std::string Renderer::read_file(const std::string& path)
	{
		std::string content;
		std::ifstream fileStream(path, std::ios::in);
		
		//判断文件是否打开
		if (!fileStream.is_open())
		{
			std::cout << "File Open Failed!" << std::endl;
			assert(true);
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
		return content;
	}

	void Renderer::set_camera_bound(size_t width, size_t height)
	{
		m_Camera->set_camera_aspect(width, height);
	}
}