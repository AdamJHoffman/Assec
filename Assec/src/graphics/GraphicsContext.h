#pragma once
#include "acpch.h"
#include "graphics/Buffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "util/Profiler.h"

namespace assec::graphics
{
	class GraphicsContext
	{
	public:
		GraphicsContext() {}
		virtual ~GraphicsContext()
		{
			this->cleanup();
		}
		virtual const void init() const = 0;
		const ref<VertexBuffer> genVertexBuffer(const void* vertices, const size_t& size, const int& usage)
		{
			TIME_FUNCTION;
			auto result = this->createVertexBuffer(vertices, size, usage);
			this->m_VertexBuffers.push_back(result);
			return result;
		}
		const ref<IndexBuffer> genIndexBuffer(const void* indices, const size_t& size, const int& usage)
		{
			TIME_FUNCTION;
			auto result = this->createIndexBuffer(indices, size, usage);
			this->m_IndexBuffers.push_back(result);
			return result;
		}
		const ref<VertexArray> genVertexArray(const void* vertices, const size_t& verticesSize, const void* indices, const size_t& indicesSize, const int& usage, graphics::VertexBuffer::VertexBufferLayout& layout)
		{
			TIME_FUNCTION;
			auto result = this->createVertexArray(vertices, verticesSize, indices, indicesSize, usage, layout);
			this->m_VertexArrays.push_back(result);
			return result;
		}
		const ref<Shader> genShader(const char* source, DataType type)
		{
			TIME_FUNCTION;
			auto result = this->createShader(source, type);
			this->m_Shaders.push_back(result);
			return result;
		}
		const ref<ShaderProgram> genShaderProgram(const char* vertexSource, const char* fragmentSource)
		{
			TIME_FUNCTION;
			auto result = this->createShaderProgram(vertexSource, fragmentSource);
			this->m_ShaderPrograms.push_back(result);
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
		}
	protected:
		virtual const ref<VertexBuffer> createVertexBuffer(const void* vertices, const size_t& size, const int& usage) const = 0;
		virtual const ref<IndexBuffer> createIndexBuffer(const void* indices, const size_t& size, const int& usage) const = 0;
		virtual const ref<VertexArray> createVertexArray(const void* vertices, const size_t& verticesSize, const void* indices, const size_t& indicesSize, const int& usage, graphics::VertexBuffer::VertexBufferLayout& layout) const = 0;
		virtual const ref<Shader> createShader(const char* source, DataType& type) const = 0;
		virtual const ref<ShaderProgram> createShaderProgram(const char* vertexSource, const char* fragmentSource) const = 0;
	private:
		std::vector<ref<VertexBuffer>> m_VertexBuffers = std::vector<ref<VertexBuffer>>();
		std::vector<ref<IndexBuffer>> m_IndexBuffers = std::vector<ref<IndexBuffer>>();
		std::vector<ref<VertexArray>> m_VertexArrays = std::vector<ref<VertexArray>>();
		std::vector<ref<Shader>> m_Shaders = std::vector<ref<Shader>>();
		std::vector<ref<ShaderProgram>> m_ShaderPrograms = std::vector<ref<ShaderProgram>>();
	};
}
