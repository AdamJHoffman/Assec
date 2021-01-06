#pragma once

#include <glm/glm.hpp>

#include "graphics/Buffer.h"

namespace assec::graphics
{
	struct Vertex
	{
		static const VertexBufferLayout& getLayout()
		{
			static const VertexBufferLayout s_Layout = VertexBufferLayout{ {
			VertexBufferAttribute{assec::DataType::FLOAT, false, 3},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 3},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 2},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 3},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 4},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 4},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 4},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 4},
			VertexBufferAttribute{assec::DataType::FLOAT, false, 1},
			VertexBufferAttribute{assec::DataType::UNSIGNED_INT, false, 1} } };
			return s_Layout;
		}
		glm::vec3 position = glm::vec3(1.0f);
		glm::vec3 normal = glm::vec3(1.0f);
		glm::vec2 textureCoordinate = glm::vec2(1.0f);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::mat4 transformationMatrix = glm::mat4(1.0f);
		float texID = 0;
		uint32_t ID = 0;
	};
	class Mesh
	{
	public:
		Mesh(CONST_REF(std::vector<Vertex>) vertices, CONST_REF(std::vector<uint32_t>) indices);
		Mesh() { TIME_FUNCTION; }
		~Mesh() { TIME_FUNCTION; }
		const std::vector<unsigned char> createVerticesData();
		const size_t calculateSize();
		const inline std::vector<Vertex>& getVertices() const { TIME_FUNCTION;  return this->m_Vertices; }
		const inline std::vector<uint32_t>& getIndices() const { TIME_FUNCTION; return this->m_Indices; }
		inline std::vector<Vertex>& getVertices() { TIME_FUNCTION; return this->m_Vertices; }
		inline std::vector<uint32_t>& getIndices() { TIME_FUNCTION; return this->m_Indices; }
		void setTransformationMatrix(const glm::mat4&);
		void setTextureIndex(const float&);
		void setID(const uint32_t&);
	private:
		std::vector<uint32_t> m_Indices = std::vector<uint32_t>();
		std::vector<Vertex> m_Vertices = std::vector<Vertex>();
	};
} // namespace assec::graphics
