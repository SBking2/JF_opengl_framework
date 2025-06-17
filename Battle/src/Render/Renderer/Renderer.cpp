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

		m_RenderData.vertex_data_base = new VertexData[1000 * 4];
		m_RenderData.vertex_data_ptr = m_RenderData.vertex_data_base;

		m_RenderData.index_base = new uint32_t[1000 * 6];
		m_RenderData.index_ptr = m_RenderData.index_base;

		m_VertexArray = std::make_shared<VertexArray>(1000 * 6);
		m_VertexBuffer = std::make_shared<VertexBuffer>(1000 * 4);
		m_VertexBuffer->set_layout(
			{
				{ ShaderDataType::Float3 },
				{ ShaderDataType::Float4 }
			});
		m_VertexArray->set_vertex_buffer(m_VertexBuffer.get());
	}

	Renderer::~Renderer()
	{

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

		start_batch();

		int quad_count = 0;
		draw_quad(glm::vec3(0.0f), 0.0f ,quad_count);
		draw_quad(glm::vec3(1.0f, 0.5f, 0.0f), 25.0f, quad_count);
		draw_quad(glm::vec3(-2.0f, -0.5f, 0.0f), 0.0f ,quad_count);

		draw_command();
	}

	void Renderer::on_event(Event& e)
	{
		m_Camera->on_event(e);
	}

	void Renderer::set_camera_bound(size_t width, size_t height)
	{
		m_Camera->set_camera_aspect(width, height);
	}

	void Renderer::draw_quad(const glm::vec3& position, float rotation, int& count)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[0];
		m_RenderData.vertex_data_ptr->color = glm::vec4(0.5f, 1.0f, 1.0f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[1];
		m_RenderData.vertex_data_ptr->color = glm::vec4(1.0f, 0.5f, 1.0f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[2];
		m_RenderData.vertex_data_ptr->color = glm::vec4(1.5f, 1.0f, 0.5f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[3];
		m_RenderData.vertex_data_ptr->color = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		*m_RenderData.index_ptr = 4 * count;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = 4 * count + 1;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = 4 * count + 2;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = 4 * count;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = 4 * count + 2;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = 4 * count + 3;
		m_RenderData.index_ptr++;

		count++;
	}
	void Renderer::start_batch()
	{
		m_RenderData.vertex_data_ptr = m_RenderData.vertex_data_base;
		m_RenderData.index_ptr = m_RenderData.index_base;
	}
	void Renderer::draw_command()
	{
		uint32_t vertex_data_size = (m_RenderData.vertex_data_ptr - m_RenderData.vertex_data_base) * sizeof(VertexData);
		m_VertexBuffer->set_data(m_RenderData.vertex_data_base, vertex_data_size);

		uint32_t index_data_size = (m_RenderData.index_ptr - m_RenderData.index_base) * sizeof(uint32_t);
		m_VertexArray->set_index_buffer(m_RenderData.index_base, index_data_size, index_data_size / sizeof(uint32_t));

		m_VertexArray->bind();
		glDrawElements(GL_TRIANGLES, m_VertexArray->get_index_count(), GL_UNSIGNED_INT, 0);
	}
}