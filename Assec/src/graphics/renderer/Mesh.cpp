﻿#include "acpch.h"

#include "Mesh.h"

namespace assec::graphics
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices) : m_Vertices(vertices), m_Indices(indices) { TIME_FUNCTION; }
	const std::vector<float> Mesh::createVerticesData()
	{
		TIME_FUNCTION;
		std::vector<float> result = std::vector<float>();
		result.reserve(this->m_Vertices.size() * Vertex::getLayout().calculateVertexSize());
		for (auto& v : this->m_Vertices)
		{
			result.push_back(v.position.x);
			result.push_back(v.position.y);
			result.push_back(v.position.z);
		}
		for (auto& v : this->m_Vertices)
		{
			result.push_back(v.normal.x);
			result.push_back(v.normal.y);
			result.push_back(v.normal.z);
		}
		for (auto& v : this->m_Vertices)
		{
			result.push_back(v.textureCoordinate.x);
			result.push_back(v.textureCoordinate.y);
		}
		for (auto& v : this->m_Vertices)
		{
			result.push_back(v.color.x);
			result.push_back(v.color.y);
			result.push_back(v.color.z);
		}
		for (int i = 0; i < 4; i++)
		{
			for (Vertex v : this->m_Vertices)
			{
				for (int j = 0; j < v.transformationMatrix.length(); j++)
				{
					result.push_back(v.transformationMatrix[i][j]);
				}
			}
		}
		for (auto& v : this->m_Vertices)
		{
			result.push_back(v.texID);
		}
		return result;
	}
	const size_t Mesh::calculateSize()
	{
		TIME_FUNCTION;
		return this->m_Vertices.size() * Vertex::getLayout().calculateVertexSize();
	}
	void Mesh::setTransformationMatrix(const glm::mat4& transform)
	{
		for (auto& v : this->m_Vertices)
		{
			v.transformationMatrix = transform;
		}
	}
	void Mesh::setTextureIndex(const float& index)
	{
		for (auto& v : this->m_Vertices)
		{
			v.texID = index;
		}
	}
}
