#include "acpch.h"

#include "Mesh.h"

namespace assec::graphics
{
	Mesh::Mesh(CONST_REF(std::vector<Vertex>) vertices, CONST_REF(std::vector<uint32_t>) indices) : m_Vertices(vertices), m_Indices(indices) { TIME_FUNCTION; }
	const std::vector<unsigned char> Mesh::createVerticesData()
	{
		TIME_FUNCTION;
		//std::vector<float> result = std::vector<float>();
		//result.reserve(this->m_Vertices.size() * Vertex::getLayout().calculateVertexSize());
		//for (auto& v : this->m_Vertices)
		//{
		//	result.push_back(v.position.x);
		//	result.push_back(v.position.y);
		//	result.push_back(v.position.z);
		//}
		//for (auto& v : this->m_Vertices)
		//{
		//	result.push_back(v.normal.x);
		//	result.push_back(v.normal.y);
		//	result.push_back(v.normal.z);
		//}
		//for (auto& v : this->m_Vertices)
		//{
		//	result.push_back(v.textureCoordinate.x);
		//	result.push_back(v.textureCoordinate.y);
		//}
		//for (auto& v : this->m_Vertices)
		//{
		//	result.push_back(v.color.x);
		//	result.push_back(v.color.y);
		//	result.push_back(v.color.z);
		//}
		//for (int i = 0; i < 4; i++)
		//{
		//	for (Vertex v : this->m_Vertices)
		//	{
		//		for (int j = 0; j < v.transformationMatrix.length(); j++)
		//		{
		//			result.push_back(v.transformationMatrix[i][j]);
		//		}
		//	}
		//}
		//for (auto& v : this->m_Vertices)
		//{
		//	result.push_back(v.texID);
		//}
		//for (auto& v : this->m_Vertices)
		//{
		//	result.push_back(v.ID);
		//}
		//return result;
		std::vector<unsigned char> result = std::vector<unsigned char>();
		result.reserve(this->m_Vertices.size() * Vertex::getLayout().calculateVertexSize());
		
		for (auto& v : this->m_Vertices)
		{
			auto bytes = util::toVector(v.position.x);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.position.y);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.position.z);
			result.insert(result.end(), bytes.begin(), bytes.end());
		}
		
		for (auto& v : this->m_Vertices)
		{
			auto bytes = util::toVector(v.normal.x);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.normal.y);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.normal.z);
			result.insert(result.end(), bytes.begin(), bytes.end());
		}
		for (auto& v : this->m_Vertices)
		{
			auto bytes = util::toVector(v.textureCoordinate.x);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.textureCoordinate.y);
			result.insert(result.end(), bytes.begin(), bytes.end());
		}
		for (auto& v : this->m_Vertices)
		{
			auto bytes = util::toVector(v.color.x);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.color.y);
			result.insert(result.end(), bytes.begin(), bytes.end());
			bytes = util::toVector(v.color.z);
			result.insert(result.end(), bytes.begin(), bytes.end());
		}
		for (int i = 0; i < 4; i++)
		{
			for (Vertex v : this->m_Vertices)
			{
				for (int j = 0; j < v.transformationMatrix.length(); j++)
				{
					auto bytes = util::toVector(v.transformationMatrix[i][j]);
					result.insert(result.end(), bytes.begin(), bytes.end());
				}
			}
		}
		for (auto& v : this->m_Vertices)
		{
			auto bytes = util::toVector(v.texID);
			result.insert(result.end(), bytes.begin(), bytes.end());
		}
		for (auto& v : this->m_Vertices)
		{
			auto bytes = util::toVector(v.ID);
			result.insert(result.end(), bytes.begin(), bytes.end());
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
		TIME_FUNCTION;
		for (auto& v : this->m_Vertices)
		{
			v.transformationMatrix = transform;
		}
	}
	void Mesh::setTextureIndex(const float& index)
	{
		TIME_FUNCTION;
		for (auto& v : this->m_Vertices)
		{
			v.texID = index;
		}
	}
	void Mesh::setID(const uint32_t& id)
	{
		TIME_FUNCTION;
		for (auto& v : this->m_Vertices)
		{
			v.ID = id;
		}
	}
} // namespace assec::graphics
