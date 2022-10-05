#pragma once

#include "Core.h";

namespace Neon {
	class NEON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}

