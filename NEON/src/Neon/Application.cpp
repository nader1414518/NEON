#include "Application.h";

#include "Neon/Events/ApplicationEvent.h";
#include "Neon/Log.h";

namespace Neon {
	Application::Application() {

	};

	Application::~Application() {

	};

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		NeonLogTrace(e);

		while (true);
	};
}