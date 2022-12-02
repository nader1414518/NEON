#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "Neon/ImGui/ImGuiLayer.h"
#include "Neon/Renderer/Shader.h"
#include "Neon/Renderer/Buffer.h"
#include "Neon/Renderer/VertexArray.h"
#include "Neon/Renderer/OrthographicCamera.h"

namespace Neon {

	class NEON_API Application
	{

	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		//void InitCamera();
		void InitWindow();
		void DrawTriangle();
		void DrawSquare();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::vector<std::shared_ptr<Shader>> m_Shaders;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::vector<std::shared_ptr<IndexBuffer>> m_IndexBuffers;

		std::shared_ptr<VertexArray> m_TriangleVertexArray;
		std::shared_ptr<VertexArray> m_SquarVertexArray;

		OrthographicCamera m_Camera;

		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}

