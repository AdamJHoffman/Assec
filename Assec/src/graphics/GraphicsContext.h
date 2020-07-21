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
		GraphicsContext() { TIME_FUNCTION; }
		virtual ~GraphicsContext()
		{
			TIME_FUNCTION;
			this->cleanup();
		}
		virtual const void init() const = 0;
		virtual void setActiveTexture(unsigned int texture) const = 0;
		const ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage)
		{
			TIME_FUNCTION;
			auto result = this->createVertexBuffer0(vertices, size, usage);
			this->m_VertexBuffers.push_back(result);
			return result;
		}
		const ref<IndexBuffer> createIndexBuffer(const void* indices, const size_t& size, const int& usage)
		{
			TIME_FUNCTION;
			auto result = this->createIndexBuffer0(indices, size, usage);
			this->m_IndexBuffers.push_back(result);
			return result;
		}
		const ref<VertexArray> createVertexArray(VertexArray::VertexArrayData vertexArrayData)
		{
			TIME_FUNCTION;
			auto result = this->createVertexArray0(vertexArrayData);
			this->m_VertexArrays.push_back(result);
			return result;
		}
		const ref<VertexArray> createVertexArray(Type usage, const size_t& size = 0)
		{
			TIME_FUNCTION;
			auto result = this->createVertexArray0(usage, size);
			this->m_VertexArrays.push_back(result);
			return result;
		}
		const ref<Shader> createShader(const char* source, Type type)
		{
			TIME_FUNCTION;
			auto result = this->createShader0(source, type);
			this->m_Shaders.push_back(result);
			return result;
		}
		const ref<ShaderProgram> createShaderProgram(const char* vertexSource, const char* fragmentSource)
		{
			TIME_FUNCTION;
			auto result = this->createShaderProgram0(vertexSource, fragmentSource);
			this->m_ShaderPrograms.push_back(result);
			return result;
		}
		const ref<Texture2D> createTexture2D(unsigned int width, unsigned int height, const void* data, Texture::TextureProps props)
		{
			TIME_FUNCTION;
			auto result = this->createTexture2D0(width, height, data, props);
			this->m_Textures.push_back(result);
			return result;
		}
		const void cleanup()
		{
			TIME_FUNCTION;
			for (auto vertexBuffer : this->m_VertexBuffers)
			{
				vertexBuffer->cleanup();
			}
			for (auto indexBuffer : this->m_IndexBuffers)
			{
				indexBuffer->cleanup();
			}
			for (auto vertexArray : this->m_VertexArrays)
			{
				vertexArray->cleanup();
			}
			for (auto shader : this->m_Shaders)
			{
				shader->cleanup();
			}
			for (auto program : this->m_ShaderPrograms)
			{
				program->cleanup();
			}
			for (auto texture : this->m_Textures)
			{
				texture->cleanup();
			}
		}
	protected:
		virtual const ref<VertexBuffer> createVertexBuffer0(const void* vertices, const size_t& size, const int& usage) const = 0;
		virtual const ref<IndexBuffer> createIndexBuffer0(const void* indices, const size_t& size, const int& usage) const = 0;
		virtual const ref<VertexArray> createVertexArray0(VertexArray::VertexArrayData vertexArrayData) const = 0;
		virtual const ref<VertexArray> createVertexArray0(Type& usage, const size_t& size = 0) const = 0;
		virtual const ref<Shader> createShader0(const char* source, Type& type) const = 0;
		virtual const ref<ShaderProgram> createShaderProgram0(const char* vertexSource, const char* fragmentSource) const = 0;
		virtual const ref<Texture2D> createTexture2D0(unsigned int width, unsigned int height, const void* data, Texture::TextureProps props) const = 0;
	private:
		std::vector<ref<VertexBuffer>> m_VertexBuffers = std::vector<ref<VertexBuffer>>();
		std::vector<ref<IndexBuffer>> m_IndexBuffers = std::vector<ref<IndexBuffer>>();
		std::vector<ref<VertexArray>> m_VertexArrays = std::vector<ref<VertexArray>>();
		std::vector<ref<Shader>> m_Shaders = std::vector<ref<Shader>>();
		std::vector<ref<ShaderProgram>> m_ShaderPrograms = std::vector<ref<ShaderProgram>>();
		std::vector<ref<Texture>> m_Textures = std::vector<ref<Texture>>();
	};
}
