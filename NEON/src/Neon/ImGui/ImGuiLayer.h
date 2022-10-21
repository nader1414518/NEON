#pragma once

#include "Neon/Layer.h"
#include "Neon/Events/ApplicationEvent.h"
#include "Neon/Events/KeyEvent.h"
#include "Neon/Events/MouseEvent.h"

namespace Neon {

	class NEON_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		//void OnUpdate();
		//void OnEvent(Event& event);
	/*private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);*/

	private:
		float m_Time = 0.0f;
	};
}

