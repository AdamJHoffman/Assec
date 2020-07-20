#include "acpch.h"
#include "Mesh.h"

namespace assec::graphics
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices) : m_Vertices(vertices), m_Indices(indices)
	{
		std::vector<float>* ptr = (std::vector<float>*) & this->m_VerticesData;
		ptr->reserve(this->m_Vertices.size() * ((size_t)3) + this->m_Indices.size() * ((size_t)2) +
			((size_t)this->m_Vertices[0].transformationMatrix.length()) * ((size_t)this->m_Vertices[0].transformationMatrix.length())
			* this->m_Vertices.size());

		for (Vertex v : this->m_Vertices)
		{
			ptr->push_back(v.position.x);
			ptr->push_back(v.position.y);
			ptr->push_back(v.position.z);
		}

		for (Vertex v : this->m_Vertices)
		{
			ptr->push_back(v.textureCoordinate.x);
			ptr->push_back(v.textureCoordinate.y);
		}

		for (int i = 0; i < this->m_Vertices[0].transformationMatrix.length(); i++)
		{
			for (Vertex v : this->m_Vertices)
			{
				for (int j = 0; j < v.transformationMatrix.length(); j++)
				{
					ptr->push_back(v.transformationMatrix[i][j]);
				}
			}
		}

	}
}
