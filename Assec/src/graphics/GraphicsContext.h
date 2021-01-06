#pragma once

#include "graphics/Buffer.h"
#include "graphics/Framebuffer.h"
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
		virtual void init() = 0;
		virtual void cleanup() = 0;

		virtual void clear(CONST_REF(std::vector<BufferBitMask>)) const = 0;
		virtual void clearColor(CONST_REF(glm::vec4)) const = 0;
		virtual void clearDepth(CONST_REF(float)) const = 0;
		virtual void clearStencil(CONST_REF(int)) const = 0;
		virtual void finish(void) const = 0;
		virtual void flush(void) const = 0;
		virtual void readBuffer(CONST_REF(DrawBuffer)) const = 0;
		virtual std::vector<unsigned char> readPixels(const glm::vec<2, int>&, 
			const glm::vec<2, int>&, CONST_REF(InternalFormat)) const = 0;


		virtual void setActiveTexture(CONST_REF(uint32_t) texture) const = 0;
		virtual void enable(CONST_REF(Type) type) const = 0;
		virtual void setDepthFunction(CONST_REF(Type) type) const = 0;
		virtual void setBlendFunction(const Type& sfactor, const Type& dfactor) const = 0;

		inline const ContextData& getContextData() const { return this->m_ContextData; }

		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, CONST_REF(size_t) size, CONST_REF(int) usage) const = 0;
		virtual ref<IndexBuffer> createIndexBuffer(CONST_REF(std::vector<uint32_t>) data, CONST_REF(int) usage) const = 0;
		virtual ref<VertexArray> createVertexArray(CONST_REF(VertexArray::VertexArrayProps) vertexArrayData) const = 0;
		virtual ref<VertexArray> createVertexArray(CONST_REF(Usage), CONST_REF(size_t) size = 0) const = 0;
		virtual ref<Shader> createShader(CONST_REF(std::string) source, CONST_REF(Type) type) const = 0;
		virtual ref<ShaderProgram> createShaderProgram(CONST_REF(std::string) vertexSource, CONST_REF(std::string) fragmentSource) const = 0;
		virtual ref<ShaderProgram> createShaderProgram(CONST_REF(std::string) source) const = 0;
		virtual ref<Texture2D> createTexture2D(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(Texture::TextureProps) props) const = 0;
		virtual ref<Texture2D> createTexture2D(CONST_REF(std::string) path, CONST_REF(Texture::TextureProps) props) const = 0;
		virtual ref<Framebuffer> createFrameBuffer(CONST_REF(FramebufferProps) frameBufferProps) const = 0;
	protected:
		mutable ContextData m_ContextData;
	};

	Format determineFormat(CONST_REF(InternalFormat) internalFormat);
	DataType determineDataType(CONST_REF(InternalFormat) internalFormat);
	size_t determineWidth(CONST_REF(InternalFormat) internalFormat);
	size_t determineTotalSize(CONST_REF(InternalFormat) internalFormat);


	size_t determineSize(CONST_REF(DataType) type);

} // namespace assec::graphics
