#include <Neon.h>

#include "imgui.h"


class ExampleLayer : public Neon::Layer
{
public:
	void ExampleLayer::DrawSquare()
	{
		std::shared_ptr<Neon::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Neon::IndexBuffer> m_IndexBuffer;

		m_SquarVertexArray.reset(Neon::VertexArray::Create());

		float vertices[4 * 8] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		};

		// Vertex Buffer Initialization
		m_VertexBuffer.reset(Neon::VertexBuffer::Create(vertices, sizeof(vertices)));
		Neon::BufferLayout layout = {
			{ Neon::ShaderDataType::Float3, "a_Position"},
			{ Neon::ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_SquarVertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		// Index Buffer Initialization
		m_IndexBuffer.reset(Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_SquarVertexArray->SetIndexBuffer(m_IndexBuffer);

		m_IndexBuffers.push_back(m_IndexBuffer);

		// Shader Initialization
		std::shared_ptr<Neon::Shader> m_Shader;
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

		m_Shader.reset(new Neon::Shader(vertexSrc, fragmentSrc));
		m_Shaders.push_back(m_Shader);
	}

	void ExampleLayer::DrawTriangle()
	{
		std::shared_ptr<Neon::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Neon::IndexBuffer> m_IndexBuffer;

		m_TriangleVertexArray.reset(Neon::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		};

		// Vertex Buffer Initialization
		m_VertexBuffer.reset(Neon::VertexBuffer::Create(vertices, sizeof(vertices)));
		Neon::BufferLayout layout = {
			{ Neon::ShaderDataType::Float3, "a_Position"},
			{ Neon::ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);
		m_TriangleVertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		// Index Buffer Initialization
		m_IndexBuffer.reset(Neon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_TriangleVertexArray->SetIndexBuffer(m_IndexBuffer);

		m_IndexBuffers.push_back(m_IndexBuffer);

		// Shader Initialization
		std::shared_ptr<Neon::Shader> m_Shader;
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

		m_Shader.reset(new Neon::Shader(vertexSrc, fragmentSrc));
		m_Shaders.push_back(m_Shader);
	}

	ExampleLayer() : Layer("Example"), 
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), 
		m_CameraPosition(0.0f, 0.0f, 0.0f), 
		m_CameraRotation(0.0f)
	{
		ExampleLayer::DrawSquare();
		ExampleLayer::DrawTriangle();
	}

	void ListenForCameraPositionChange()
	{
		if (Neon::Input::IsKeyPressed(NEON_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (Neon::Input::IsKeyPressed(NEON_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (Neon::Input::IsKeyPressed(NEON_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		}
		else if (Neon::Input::IsKeyPressed(NEON_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}
	}

	void ListenForCameraRoatationChange()
	{
		if (Neon::Input::IsKeyPressed(NEON_KEY_Q))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}
		else if (Neon::Input::IsKeyPressed(NEON_KEY_E))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}
	}

	void RenderScene()
	{
		Neon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Neon::RenderCommand::Clear();

		//m_Camera.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Neon::Renderer::BeginScene(m_Camera);

		Neon::Renderer::Submit(m_SquarVertexArray, m_Shaders[0]);
		Neon::Renderer::Submit(m_TriangleVertexArray, m_Shaders[1]);

		Neon::Renderer::EndScene();
	}

	void OnUpdate() override
	{
		//NeonLogInfo("ExampleLayer::Update");

		/*if (Neon::Input::IsKeyPressed(NEON_KEY_TAB))
		{
			NeonLogInfo("Tab key is pressed ... ");
		}*/

		ListenForCameraPositionChange();

		ListenForCameraRoatationChange();

		RenderScene();
	}

	virtual void OnImGuiRender() override
	{
		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}

	void OnEvent(Neon::Event& event) override
	{
		//NeonLogTrace("{0}", event);

		//if (event.GetEventType() == Neon::EventType::KeyPressed)
		//{
		//	Neon::KeyPressedEvent& e = (Neon::KeyPressedEvent&)event;
		//	//NeonLogDebug("{0}", (char)e.GetKeyCode());

		//	if (e.GetKeyCode() == NEON_KEY_ENTER)
		//	{
		//		NeonLogDebug("You pressed enter!!");
		//	}
		//}

		/*Neon::EventDispatcher dispatcher = Neon::EventDispatcher(event);
		dispatcher.Dispatch<Neon::KeyPressedEvent>(NEON_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEventHandler));*/
	}

	// result indicates whether to lock or not
	/*bool OnKeyPressedEventHandler(Neon::KeyPressedEvent& event)
	{
		

		return false;
	}*/

private:
	std::vector<std::shared_ptr<Neon::Shader>> m_Shaders;
	std::vector<std::shared_ptr<Neon::VertexBuffer>> m_VertexBuffers;
	std::vector<std::shared_ptr<Neon::IndexBuffer>> m_IndexBuffers;

	std::shared_ptr<Neon::VertexArray> m_TriangleVertexArray;
	std::shared_ptr<Neon::VertexArray> m_SquarVertexArray;

	Neon::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Neon::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	};

	~Sandbox() {

	};
};

Neon::Application* Neon::CreateApplication() {
	return new Sandbox();
};

//void main() {
//	/*Sandbox* sandbox = new Sandbox();
//	
//	sandbox->Run();
//
//	delete sandbox;*/
//}