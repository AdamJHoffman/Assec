#pragma once
#include "acpch.h"

#include <glm/glm.hpp>

#include "graphics/Buffer.h"

namespace assec::graphics
{
	struct Vertex
	{
		static const VertexBuffer::VertexBufferLayout& getLayout()
		{
			static const VertexBuffer::VertexBufferLayout s_Layout = VertexBuffer::VertexBufferLayout({
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 3, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 3, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 2, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 3, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 1, false) });
			return s_Layout;
		}
		glm::vec3 position = glm::vec3(1.0f);
		glm::vec3 normal = glm::vec3(1.0f);
		glm::vec2 textureCoordinate = glm::vec2(1.0f);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::mat4 transformationMatrix = glm::mat4(1.0f);
		float texID = 0;
	};
	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices);
		Mesh() {}
		~Mesh() { TIME_FUNCTION; }
		const std::vector<float> createVerticesData();
		const size_t calculateSize();
		const inline std::vector<Vertex>& getVertices() const { return this->m_Vertices; }
		const inline std::vector<int>& getIndices() const { return this->m_Indices; }
		inline std::vector<Vertex>& getVertices() { return this->m_Vertices; }
		inline std::vector<int>& getIndices() { return this->m_Indices; }
		void setTransformationMatrix(const glm::mat4&);
		void setTextureIndex(const float&);
	private:
		std::vector<int> m_Indices = std::vector<int>();
		std::vector<Vertex> m_Vertices = std::vector<Vertex>();
	};
}
