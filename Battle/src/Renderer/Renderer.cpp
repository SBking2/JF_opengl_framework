#include "Renderer.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
namespace JF
{
	Renderer::Renderer(size_t width, size_t height)
	{
		m_Camera = std::make_shared<Camera>(width, height);

		const char* vertexShaderSource = R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * vec4(aPos, 1.0);
			}
		)";

		// ƬԪ��ɫ��Դ��
		const char* fragmentShaderSource = R"(
			#version 330 core
			out vec4 FragColor;

			void main() {
				FragColor = vec4(1.0, 0.5, 0.2, 1.0); // ��ɫ
			}
		)";

		float vertices[] = {
			 0.0f,  0.5f, 0.0f, // �϶���
			-0.5f, -0.5f, 0.0f, // ����
			 0.5f, -0.5f, 0.0f  // ����
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		// ��VAO
		glBindVertexArray(VAO);

		// �󶨲�����VBO����
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// ���붥����ɫ��
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		// ����ƬԪ��ɫ��
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

		// ������ɫ������
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// ɾ����ɫ��
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Renderer::~Renderer()
	{
		// ������Դ
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
	}

	void Renderer::on_update()
	{

	}

	void Renderer::on_render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	//����Clearʱʹ�õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);	//Clear

		// ����������
		glUseProgram(shaderProgram);

		GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_Camera->get_view_projection_matrix()));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Renderer::on_event(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Renderer::on_key_pressed, this, std::placeholders::_1));
	}

	void Renderer::on_key_pressed(KeyPressedEvent& e)
	{
		float speed = 0.05f;
		m_Camera->get_position().x += speed;
		m_Camera->update_camera_matrix();
	}

	void Renderer::set_camera_bound(size_t width, size_t height)
	{
		m_Camera->set_camera_aspect(width, height);
	}
}