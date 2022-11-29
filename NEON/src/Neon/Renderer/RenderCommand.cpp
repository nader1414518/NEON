
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Neon {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}