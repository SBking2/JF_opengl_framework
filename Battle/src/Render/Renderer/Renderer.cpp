#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "stb/stb_image.h"
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
				{ ShaderDataType::Float2 },
				{ ShaderDataType::Float4 }
			});
		m_VertexArray->set_vertex_buffer(m_VertexBuffer.get());

		stbi_set_flip_vertically_on_load(true);

		int img_width, img_height, channels;
		unsigned char* data = stbi_load("assets/texture/te.jpg", &img_width, &img_height, &channels, 0);
		if (!data) {
			std::cerr << "Failed to load texture!" << std::endl;
			assert(true);
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // X轴重复
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // Y轴重复
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 缩小过滤
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 放大过滤

		GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, img_width, img_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);	//释放图片数据
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
		static float rotation = 0.0f;

		rotation += 0.1;
		y = std::sin(rotation);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//设置Clear时使用的颜色
		glClear(GL_COLOR_BUFFER_BIT);	//Clear

		// 绘制三角形
		m_Shader->bind();
		m_Shader->set_uniform_matrix4("projection", m_Camera->get_view_projection_matrix());
		m_Shader->set_uniform_Int("textureID", 0);

		start_batch();

		draw_quad(glm::vec3(0.0f), 0.0f);
		draw_quad(glm::vec3(1.0f, y, 0.0f), rotation);
		draw_quad(glm::vec3(-2.0f, -0.5f, 0.0f), 0.0f);

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

	void Renderer::draw_quad(const glm::vec3& position, float rotation)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[0];
		m_RenderData.vertex_data_ptr->uv = glm::vec2(0.0f, 1.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(0.5f, 1.0f, 1.0f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[1];
		m_RenderData.vertex_data_ptr->uv = glm::vec2(0.0f, 0.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(1.0f, 0.5f, 1.0f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[2];
		m_RenderData.vertex_data_ptr->uv = glm::vec2(1.0f, 0.0f);
		m_RenderData.vertex_data_ptr->color = glm::vec4(1.5f, 1.0f, 0.5f, 1.0f);
		m_RenderData.vertex_data_ptr++;

		m_RenderData.vertex_data_ptr->position = transform * m_RenderData.quad_vertex[3];
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