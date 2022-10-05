#pragma once

#ifdef NEON_PLATFORM_WINDOWS

extern Neon::Application* Neon::CreateApplication();

void main(int argc, char** argv)
{
	printf("NEON Started ... ");
	auto app = Neon::CreateApplication();
	app->Run();
	delete app;
}

#endif
