#pragma once
#include "acpch.h"

#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include "util/Profiler.h"

namespace assec::graphics
{
	class GraphicsContext
	{
	public:
		struct ContextData
		{
			std::string m_Vendor = "", m_Renderer = "", m_Version = "";
			int m_MaxTextures = 0;
		};
		GraphicsContext() { TIME_FUNCTION; }
		virtual ~GraphicsContext() { TIME_FUNCTION; }
		virtual const void init() const = 0;
		virtual void setActiveTexture(const uint32_t& texture) const = 0;
		virtual void setClearColor(const glm::vec4& color) const = 0;
		virtual void enable(const Type& type) const = 0;
		virtual void setDepthFunction(const Type& type) const = 0;
		inline const ContextData& getContextData() const { return this->m_ContextData; }
		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const = 0;
		virtual ref<IndexBuffer> createIndexBuffer(const void* indices, const size_t& size, const int& usage) const = 0;
		virtual ref<VertexArray> createVertexArray(const VertexArray::VertexArrayProps& vertexArrayData) const = 0;
		virtual ref<VertexArray> createVertexArray(const Type& usage, const size_t& size = 0) const = 0;
		virtual ref<Shader> createShader(const std::string& source, const Type& type) const = 0;
		virtual ref<ShaderProgram> createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) const = 0;
		virtual ref<ShaderProgram> createShaderProgram(const std::string& source) const = 0;
		virtual ref<Texture2D> createTexture2D(const void* data, const Texture::TextureProps& props) const = 0;
		virtual ref<FrameBuffer> createFrameBuffer(const FrameBuffer::FrameBufferProps& frameBufferProps) const = 0;
	protected:
		mutable ContextData m_ContextData;
	};
}
