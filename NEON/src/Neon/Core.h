#pragma once

#ifdef NEON_PLATFORM_WINDOWS
	#ifdef NEON_BUILD_DLL
		#define NEON_API __declspec(dllexport)
	#else
		#define NEON_API __declspec(dllimport)
	#endif
#else
	#error NEON Only Support Windows For Now!!
#endif
