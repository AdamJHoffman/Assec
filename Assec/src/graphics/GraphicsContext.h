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
			const char* m_Vendor = "", * m_Renderer = "", * m_Version = "";
			int m_MaxTextures = 0;
		};
		GraphicsContext() { TIME_FUNCTION; }
		virtual ~GraphicsContext()
		{
			TIME_FUNCTION;
			this->cleanup();
		}
		virtual const void init() const = 0;
		virtual void setActiveTexture(uint32_t texture) const = 0;
		inline const ContextData& getContextData() const
		{
			return this->m_ContextData;
		}
		VertexBuffer& createVertexBuffer(const void* vertices, const size_t& size, const int& usage)
		{
			TIME_FUNCTION;
			auto result = this->createVertexBuffer0(vertices, size, usage);
			this->m_VertexBuffers.push_back(result);
			return *result;
		}
		IndexBuffer& createIndexBuffer(const void* indices, const size_t& size, const int& usage)
		{
			TIME_FUNCTION;
			auto result = this->createIndexBuffer0(indices, size, usage);
			this->m_IndexBuffers.push_back(result);
			return *result;
		}
		VertexArray& createVertexArray(VertexArray::VertexArrayData vertexArrayData)
		{
			TIME_FUNCTION;
			auto result = this->createVertexArray0(vertexArrayData);
			this->m_VertexArrays.push_back(result);
			return *result;
		}
		VertexArray& createVertexArray(Type usage, const size_t& size = 0)
		{
			TIME_FUNCTION;
			auto result = this->createVertexArray0(usage, size);
			this->m_VertexArrays.push_back(result);
			return *result;
		}
		Shader& createShader(const char* source, Type type)
		{
			TIME_FUNCTION;
			auto result = this->createShader0(source, type);
			this->m_Shaders.push_back(result);
			return *result;
		}
		ShaderProgram& createShaderProgram(const char* vertexSource, const char* fragmentSource)
		{
			TIME_FUNCTION;
			auto result = this->createShaderProgram0(vertexSource, fragmentSource);
			this->m_ShaderPrograms.push_back(result);
			return *result;
		}
		Texture2D& createTexture2D(const void* data, Texture::TextureProps props)
		{
			TIME_FUNCTION;
			auto result = this->createTexture2D0(data, props);
			this->m_Textures.push_back(result);
			return *result;
		}
		FrameBuffer& createFrameBuffer(const FrameBuffer::FrameBufferProps& frameBufferProps)
		{
			TIME_FUNCTION;
			auto result = this->createFrameBuffer0(frameBufferProps);
			this->m_FrameBuffers.push_back(result);
			return *result;
		}
		const void cleanup()
		{
			TIME_FUNCTION;
			for (auto vertexBuffer : this->m_VertexBuffers)
			{
				vertexBuffer->cleanup();
				delete vertexBuffer;
			}
			for (auto indexBuffer : this->m_IndexBuffers)
			{
				indexBuffer->cleanup();
				delete indexBuffer;
			}
			for (auto vertexArray : this->m_VertexArrays)
			{
				vertexArray->cleanup();
				delete vertexArray;
			}
			for (auto shader : this->m_Shaders)
			{
				shader->cleanup();
				delete shader;
			}
			for (auto program : this->m_ShaderPrograms)
			{
				program->cleanup();
				delete program;
			}
			for (auto texture : this->m_Textures)
			{
				texture->cleanup();
				delete texture;
			}
			for (auto framebuffer : this->m_FrameBuffers)
			{
				framebuffer->cleanup();
				delete framebuffer;
			}
		}
	protected:
		virtual VertexBuffer* createVertexBuffer0(const void* vertices, const size_t& size, const int& usage) const = 0;
		virtual IndexBuffer* createIndexBuffer0(const void* indices, const size_t& size, const int& usage) const = 0;
		virtual VertexArray* createVertexArray0(VertexArray::VertexArrayData vertexArrayData) const = 0;
		virtual VertexArray* createVertexArray0(Type& usage, const size_t& size = 0) const = 0;
		virtual Shader* createShader0(const char* source, Type& type) const = 0;
		virtual ShaderProgram* createShaderProgram0(const char* vertexSource, const char* fragmentSource) const = 0;
		virtual Texture2D* createTexture2D0(const void* data, Texture::TextureProps props) const = 0;
		virtual FrameBuffer* createFrameBuffer0(const FrameBuffer::FrameBufferProps& frameBufferProps) const = 0;
		mutable ContextData m_ContextData;
	private:
		std::vector<VertexBuffer*> m_VertexBuffers = std::vector<VertexBuffer*>();
		std::vector<IndexBuffer*> m_IndexBuffers = std::vector<IndexBuffer*>();
		std::vector<VertexArray*> m_VertexArrays = std::vector<VertexArray*>();
		std::vector<Shader*> m_Shaders = std::vector<Shader*>();
		std::vector<ShaderProgram*> m_ShaderPrograms = std::vector<ShaderProgram*>();
		std::vector<Texture*> m_Textures = std::vector<Texture*>();
		std::vector<FrameBuffer*> m_FrameBuffers = std::vector<FrameBuffer*>();
	};
}
