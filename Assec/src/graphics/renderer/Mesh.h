#pragma once

#include <glm/glm.hpp>
#include "acpch.h"

namespace assec::graphics
{
	struct Vertex
	{
		static VertexBuffer::VertexBufferLayout& getLayout()
		{

			static VertexBuffer::VertexBufferLayout s_Layout = VertexBuffer::VertexBufferLayout({
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 3, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 2, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false),
			VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 4, false) });
			return s_Layout;
		}
		glm::vec3 position = glm::vec3(1.0f);
		//glm::vec3 normal;
		glm::vec2 textureCoordinate = glm::vec2(1.0f);
		//glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::mat4 transformationMatrix = glm::mat4(1.0f);
		//float texID = 0;
	};
	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		~Mesh() {}
		const std::vector<int> m_Indices;
		const std::vector<Vertex> m_Vertices;
		const std::vector<float> m_VerticesData;
	};
}