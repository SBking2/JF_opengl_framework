#pragma once
#include<memory>
#include <sstream>

#include<glm/glm.hpp>
#include "GLEW/glew.h"

#include "Render/Camera/Camera.h"
#include"Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/EventDispatcher.h"
#include "Render/Shader/Shader.h"
#include "Render/VertexArray/VertexArray.h"

namespace JF
{
	class Renderer
	{
	public:
		struct VertexData
		{
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec4 color;
		};

		class RenderData
		{
		public:
			RenderData()
			{
				quad_vertex[0] = {-0.5f, 0.5f, 0.0f, 1.0f};
				quad_vertex[1] = {-0.5f, -0.5f, 0.0f, 1.0f};
				quad_vertex[2] = { 0.5f, -0.5f, 0.0f, 1.0f};
				quad_vertex[3] = { 0.5f, 0.5f, 0.0f, 1.0};
			}
			uint32_t MAX_QUAD_COUNT = 1000;
			VertexData* vertex_data_base;
			VertexData* vertex_data_ptr;
			uint32_t* index_base;
			uint32_t* index_ptr;

			glm::vec4 quad_vertex[4];
		};

	public:
		Renderer(size_t width, size_t height);
		virtual ~Renderer();
		void on_render();
		void on_update();
		void on_event(Event& e);
		void set_camera_bound(size_t width, size_t height);
	private:
		void draw_quad(const glm::vec3& position, float rotation);		//ªÊ÷∆Quad
		void start_batch();
		void draw_command();
	private:
		std::shared_ptr<Camera> m_Camera;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		RenderData m_RenderData;
	};
}