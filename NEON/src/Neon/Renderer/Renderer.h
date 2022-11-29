#pragma once

#include "RenderCommand.h"

namespace Neon {

	class Renderer
	{
	public:
		static void BeginScene(); // TODO: Add scene parameters 
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}