#include "acpch.h"
#include "Mesh.h"

namespace assec::graphics
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices) : m_Vertices(vertices), m_Indices(indices), m_Size(0) { TIME_FUNCTION; }
	const std::vector<float>& Mesh::getVerticesData()
	{
		TIME_FUNCTION;
		this->m_VerticesData.reserve(this->m_Vertices.size() * ((size_t)3) + this->m_Indices.size() * ((size_t)2) +
			((size_t)this->m_Vertices[0].transformationMatrix.length()) * ((size_t)this->m_Vertices[0].transformationMatrix.length())
			* this->m_Vertices.size());

		for (Vertex v : this->m_Vertices)
		{
			this->m_VerticesData.push_back(v.position.x);
			this->m_VerticesData.push_back(v.position.y);
			this->m_VerticesData.push_back(v.position.z);
		}

		for (Vertex v : this->m_Vertices)
		{
			this->m_VerticesData.push_back(v.normal.x);
			this->m_VerticesData.push_back(v.normal.y);
			this->m_VerticesData.push_back(v.normal.z);
		}

		for (Vertex v : this->m_Vertices)
		{
			this->m_VerticesData.push_back(v.textureCoordinate.x);
			this->m_VerticesData.push_back(v.textureCoordinate.y);
		}

		for (Vertex v : this->m_Vertices)
		{
			this->m_VerticesData.push_back(v.color.x);
			this->m_VerticesData.push_back(v.color.y);
			this->m_VerticesData.push_back(v.color.z);
		}

		for (int i = 0; i < this->m_Vertices[0].transformationMatrix.length(); i++)
		{
			for (Vertex v : this->m_Vertices)
			{
				for (int j = 0; j < v.transformationMatrix.length(); j++)
				{
					this->m_VerticesData.push_back(v.transformationMatrix[i][j]);
				}
			}
		}

		for (Vertex v : this->m_Vertices)
		{
			this->m_VerticesData.push_back(v.texID);
		}
		return this->m_VerticesData;
	}
	const size_t* Mesh::calculateSize() const
	{
		TIME_FUNCTION;
		this->m_Size = this->m_Vertices.size() * Vertex::getLayout().calculateVertexSize();
		return &this->m_Size;
	}
	void Mesh::setTransformationMatrix(const glm::mat4& transform)
	{
		for (Vertex v : this->m_Vertices)
		{
			v.transformationMatrix = transform;
		}
	}

}
