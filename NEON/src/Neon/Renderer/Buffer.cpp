#include "NEON_PCH.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Neon {



	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	NeonCoreAssert(false, "RendererAPI None is currently not supported!!") return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		NeonCoreAssert(false, "Unknown Renderer API ... ");

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	NeonCoreAssert(false, "RendererAPI None is currently not supported!!") return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		NeonCoreAssert(false, "Unknown Renderer API ... ");

		return nullptr;
	}

}