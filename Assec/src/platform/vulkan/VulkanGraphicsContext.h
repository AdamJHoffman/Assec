#pragma once

#include <vulkan/vulkan.h>

#include "graphics/GraphicsContext.h"

namespace assec::graphics
{
	class VulkanGraphicsContext : public GraphicsContext
	{
	public:
		virtual void init() override;
		virtual void cleanup() override;

		virtual void clear(CONST_REF(std::vector<BufferBitMask>)) const override {}
		virtual void clearColor(CONST_REF(glm::vec4)) const override {}
		virtual void clearDepth(CONST_REF(float)) const override {}
		virtual void clearStencil(CONST_REF(int)) const override {}
		virtual void finish(void) const override {}
		virtual void flush(void) const override {}
		virtual void readBuffer(CONST_REF(DrawBuffer)) const override {}
		virtual std::vector<unsigned char> readPixels(const glm::vec<2, int>&,
			const glm::vec<2, int>&, CONST_REF(InternalFormat)) const override {
			return std::vector<unsigned char>();
		}


		virtual void setActiveTexture(CONST_REF(uint32_t) texture) const override {}
		virtual void enable(CONST_REF(Type) type) const override {}
		virtual void setDepthFunction(CONST_REF(Type) type) const override {}
		virtual void setBlendFunction(const Type& sfactor, const Type& dfactor) const override {}

		virtual ref<VertexBuffer> createVertexBuffer(const void* vertices, CONST_REF(size_t) size, CONST_REF(int) usage) const override { return nullptr; }
		virtual ref<IndexBuffer> createIndexBuffer(CONST_REF(std::vector<uint32_t>) data, CONST_REF(int) usage) const override { return nullptr; }
		virtual ref<VertexArray> createVertexArray(CONST_REF(VertexArray::VertexArrayProps) vertexArrayData) const override { return nullptr; }
		virtual ref<VertexArray> createVertexArray(CONST_REF(Usage), CONST_REF(size_t) size = 0) const override { return nullptr; }
		virtual ref<Shader> createShader(CONST_REF(std::string) source, CONST_REF(Type) type) const override { return nullptr; }
		virtual ref<ShaderProgram> createShaderProgram(CONST_REF(std::string) vertexSource, CONST_REF(std::string) fragmentSource) const override { return nullptr; }
		virtual ref<ShaderProgram> createShaderProgram(CONST_REF(std::string) source) const override { return nullptr; }
		virtual ref<Texture2D> createTexture2D(CONST_REF(uint32_t) width, CONST_REF(uint32_t) height, CONST_REF(Texture::TextureProps) props) const override { return nullptr; }
		virtual ref<Texture2D> createTexture2D(CONST_REF(std::string) path, CONST_REF(Texture::TextureProps) props) const override { return nullptr; }
		virtual ref<Framebuffer> createFrameBuffer(CONST_REF(FramebufferProps) frameBufferProps) const override { return nullptr; }

	private:
		VkInstance m_Instance;
	};
}