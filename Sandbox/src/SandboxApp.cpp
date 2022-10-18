#include <Neon.h>


class ExampleLayer : public Neon::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		NeonLogInfo("ExampleLayer::Update");
	}

	void OnEvent(Neon::Event& event) override
	{
		NeonLogTrace("{0}", event);
	}
};

class Sandbox : public Neon::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Neon::ImGuiLayer());
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