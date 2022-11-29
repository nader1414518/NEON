#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Neon {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Neon::ShaderDataType::Float:		return GL_FLOAT;
			case Neon::ShaderDataType::Float2:		return GL_FLOAT;
			case Neon::ShaderDataType::Float3:		return GL_FLOAT;
			case Neon::ShaderDataType::Float4:		return GL_FLOAT;
			case Neon::ShaderDataType::Mat3:		return GL_FLOAT;
			case Neon::ShaderDataType::Mat4:		return GL_FLOAT;
			case Neon::ShaderDataType::Int:			return GL_INT;
			case Neon::ShaderDataType::Int2:		return GL_INT;
			case Neon::ShaderDataType::Int3:		return GL_INT;
			case Neon::ShaderDataType::Int4:		return GL_INT;
			case Neon::ShaderDataType::Bool:		return GL_BOOL;
		}

		NeonCoreAssert(false, "Unknown Shader Data Type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		NeonCoreAssert(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		OpenGLVertexArray::Bind();
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		OpenGLVertexArray::Bind();

		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}