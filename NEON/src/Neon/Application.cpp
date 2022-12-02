#include "Application.h"
#include "NEON_PCH.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Input.h"

#include "Renderer/Renderer.h"

//#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
//#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
//#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
//#include <glm/ext/scalar_constants.hpp> // glm::pi
//
//glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
//{
//	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
//	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//	return Projection * View * Model;
//}


namespace Neon {
	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	void Application::InitWindow()
	{
		WindowProps props = WindowProps("NEON - Windows", 1280, 720);

		m_Window = std::unique_ptr<Window>(Window::Create(props));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::DrawSquare()
	{
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		m_SquarVertexArray.reset(VertexArray::Create());

		float vertices[4 * 8] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		};

		// Vertex Buffer Initialization
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_SquarVertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		// Index Buffer Initialization
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_SquarVertexArray->SetIndexBuffer(m_IndexBuffer);

		m_IndexBuffers.push_back(m_IndexBuffer);

		// Shader Initialization
		std::shared_ptr<Shader> m_Shader;
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_Shaders.push_back(m_Shader);
	}

	void Application::DrawTriangle()
	{
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		m_TriangleVertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		// Vertex Buffer Initialization
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_TriangleVertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		// Index Buffer Initialization
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_TriangleVertexArray->SetIndexBuffer(m_IndexBuffer);

		m_IndexBuffers.push_back(m_IndexBuffer);

		// Shader Initialization
		std::shared_ptr<Shader> m_Shader;
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_Shaders.push_back(m_Shader);
	}

	Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		NeonCoreAssert(!s_Instance, "Application already exists!");
		s_Instance = this;

		Application::InitWindow();

		//Application::InitCamera();

		Application::DrawSquare();

		Application::DrawTriangle();
	};

	Application::~Application() { 

	};

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//NeonCoreLogTrace("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
			{
				break;
			}
		}
	}

	void Application::Run() {
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			//m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
			m_Camera.SetRotation(0.0f);

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_SquarVertexArray, m_Shaders[0]);
			Renderer::Submit(m_TriangleVertexArray, m_Shaders[1]);
			
			Renderer::EndScene();

			//Renderer::Flush();

			//// Draw GFX 
			//m_Shaders[0]->Bind();
			//m_SquarVertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_IndexBuffers[0]->GetCount(), GL_UNSIGNED_INT, nullptr);

			//m_Shaders[1]->Bind();
			//m_TriangleVertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_IndexBuffers[1]->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		} 
	};

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}