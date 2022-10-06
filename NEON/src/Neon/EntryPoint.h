#pragma once

#ifdef NEON_PLATFORM_WINDOWS

extern Neon::Application* Neon::CreateApplication();

void main(int argc, char** argv)
{
	Neon::Log::Init();
	
	NeonCoreLogWarning("Neon Engine Initialized ... ");
	NeonLogInfo("Sanbox Initialized ... ");

	auto app = Neon::CreateApplication();
	app->Run();
	delete app;
}

#endif
