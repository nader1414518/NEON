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

#ifdef NEON_ENABLE_ASSERTS
	#define NeonAssert(x. ...) { if(!(x)) { NeonLogError("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NeonCoreAssert(x, ...) { if(!(x)) { NeonCoreLogError("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();  } }
#else
	#define NeonAssert(x, ...)
	#define NeonCoreAssert(x, ...)
#endif // NEON_ENABLE_ASSERTS


#define BIT(x) (1 << x)
