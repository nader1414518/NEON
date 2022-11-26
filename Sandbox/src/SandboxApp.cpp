#include <Neon.h>

#include "imgui.h"


class ExampleLayer : public Neon::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//NeonLogInfo("ExampleLayer::Update");

		/*if (Neon::Input::IsKeyPressed(NEON_KEY_TAB))
		{
			NeonLogInfo("Tab key is pressed ... ");
		}*/
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

		if (event.GetEventType() == Neon::EventType::KeyPressed)
		{
			Neon::KeyPressedEvent& e = (Neon::KeyPressedEvent&)event;
			//NeonLogDebug("{0}", (char)e.GetKeyCode());

			if (e.GetKeyCode() == NEON_KEY_ENTER)
			{
				NeonLogDebug("You pressed enter!!");
			}
		}
	}
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