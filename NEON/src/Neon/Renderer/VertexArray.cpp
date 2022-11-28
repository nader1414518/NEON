#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Neon {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:			NeonCoreAssert(false, "RendererAPI::None is currently not supported!!"); return nullptr;
			case RendererAPI::OpenGL:		return new OpenGLVertexArray();
		}

		NeonCoreAssert(false, "Unknown Renderer API !!");
		return nullptr;
	}

}