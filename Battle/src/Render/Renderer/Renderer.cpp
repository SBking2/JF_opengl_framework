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
				{ ShaderDataType::Float },
				{ ShaderDataType::Float2 },
				{ ShaderDataType::Float4 }
			});
		m_VertexArray->set_vertex_buffer(m_VertexBuffer.get());

		m_RenderData.texture1 = std::make_shared<Texture>("assets/texture/xia.jpg");
		m_RenderData.texture1->bind(0);

		m_RenderData.texture2 = std::make_shared<Texture>("assets/texture/te2.jpg");
		m_RenderData.texture2->bind(1);

		m_RenderData.texture3 = std::make_shared<Texture>("assets/texture/te.jpg");
		m_RenderData.texture3->bind(2);

		m_RenderData.texture4 = std::make_shared<Texture>("assets/texture/xiang.jpg");
		m_RenderData.texture4->bind(3);

		m_Shader->bind();

		int sampler2D[32];
		for (int i = 0; i < 32; i++)
		{
			sampler2D[i] = i;
		}

		m_Shader->set_uniform_IntArray("textureIDs", sampler2D, 32);	//修改Shader值，只有在绑定Shader之后才有用

		/*m_RenderData.texture5 = std::make_shared<Texture>("assets/texture/bk.jpg");
		m_RenderData.texture1->bind(4);*/
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::on_update()
	{

	}

	void Renderer::on_render()
	{
		static float y = 0.0f;
		static float x = 0.0f;
		static float rotation = 0.0f;

		rotation += 0.1;
		y = std::sin(rotation);
		x = std::cos(rotation);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//设置Clear时使用的颜色
		glClear(GL_COLOR_BUFFER_BIT);	//Clear
		
		m_Shader->set_uniform_matrix4("projection", m_Camera->get_view_projection_matrix());

		start_batch();

		draw_quad(glm::vec3(0.0f), x, 0);
		draw_quad(glm::vec3(x, y, 0.0f), rotation, 1);
		draw_quad(glm::vec3(x, -0.5f, 0.0f), 0.0f, 2);

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

	void Renderer::draw_quad(const glm::vec3& position, float rotation, int texindex)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[0];
		m_RenderData.vertex_data_ptr->texIndex = texindex;
		m_RenderData.vertex_data_ptr->uv = glm::vec2(0.0f, 1.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(0.5f, 1.0f, 1.0f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[1];
		m_RenderData.vertex_data_ptr->texIndex = texindex;
		m_RenderData.vertex_data_ptr->uv = glm::vec2(0.0f, 0.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(1.0f, 0.5f, 1.0f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[2];
		m_RenderData.vertex_data_ptr->texIndex = texindex;
		m_RenderData.vertex_data_ptr->uv = glm::vec2(1.0f, 0.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(1.5f, 1.0f, 0.5f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[3];
		m_RenderData.vertex_data_ptr->texIndex = texindex;
		m_RenderData.vertex_data_ptr->uv = glm::vec2(1.0f, 1.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		int lastIndex = m_RenderData.index_ptr == m_RenderData.index_base ? -1 : *(m_RenderData.index_ptr - 1);

		*m_RenderData.index_ptr = lastIndex + 1;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = lastIndex + 2;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = lastIndex + 3;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = lastIndex + 1;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = lastIndex + 3;
		m_RenderData.index_ptr++;

		*m_RenderData.index_ptr = lastIndex + 4;
		m_RenderData.index_ptr++;

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