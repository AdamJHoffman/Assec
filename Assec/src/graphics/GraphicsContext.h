#pragma once

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
		virtual void setActiveTexture(CONST_REF(uint32_t) texture) const = 0;
		virtual void setClearColor(CONST_REF(glm::vec4) color) const = 0;
		virtual void enable(CONST_REF(Type) type) const = 0;
		virtual void setDepthFunction(CONST_REF(Type) type) const = 0;
		inline const ContextData& getContextData() const { return this->m_ContextData; }
		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, CONST_REF(size_t) size, CONST_REF(int) usage) const = 0;
		virtual ref<IndexBuffer> createIndexBuffer(const void* indices, CONST_REF(size_t) size, CONST_REF(int) usage) const = 0;
		virtual ref<VertexArray> createVertexArray(CONST_REF(VertexArray::VertexArrayProps) vertexArrayData) const = 0;
		virtual ref<VertexArray> createVertexArray(CONST_REF(Type), CONST_REF(size_t) size = 0) const = 0;
		virtual ref<Shader> createShader(CONST_REF(std::string) source, CONST_REF(Type) type) const = 0;
		virtual ref<ShaderProgram> createShaderProgram(CONST_REF(std::string) vertexSource, CONST_REF(std::string) fragmentSource) const = 0;
		virtual ref<ShaderProgram> createShaderProgram(CONST_REF(std::string) source) const = 0;
		virtual ref<Texture2D> createTexture2D(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(Texture::TextureProps) props) const = 0;
		virtual ref<Texture2D> createTexture2D(CONST_REF(std::string) path, CONST_REF(Texture::TextureProps) props) const = 0;
		virtual ref<FrameBuffer> createFrameBuffer(CONST_REF(FrameBuffer::FrameBufferProps) frameBufferProps) const = 0;
	protected:
		mutable ContextData m_ContextData;
	};
} // namespace assec::graphics
