#include "NEON_PCH.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Neon
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		NeonCoreAssert(windowHandle, "Window handle is null ... ");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NeonCoreAssert(status, "Failed to initialize Glad!");

		std::string Vendor(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		std::string Renderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		std::string Version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		NeonCoreLogInfo("Vendor: {0}", Vendor);
		NeonCoreLogInfo("Renderer: {0}", Renderer);
		NeonCoreLogInfo("Version: {0}", Version);
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}