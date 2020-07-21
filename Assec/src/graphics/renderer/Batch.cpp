#include "acpch.h"
#include "Batch.h"

namespace assec::graphics
{
	Batch::Batch(ref<Material> material) : m_Size(0), m_Material(material), m_Meshes(std::vector<ref<Mesh>>()) {}
	Batch::~Batch() {}
	const ref<Mesh> Batch::getMesh()
	{
		std::vector<Vertex> vertices = std::vector<Vertex>();
		std::vector<int> indices = std::vector<int>();
		if (!this->m_Meshes.empty())
		{
			int indicesOffset = 0;
			for (ref<Mesh> m : m_Meshes)
			{
				for (Vertex v : m->m_Vertices)
				{
					vertices.push_back(v);
				}
				for (unsigned int i : m->m_Indices)
				{
					indices.push_back(i + indicesOffset);
				}
				indicesOffset += ((int)m->m_Indices.size());
			}
			return std::make_shared<Mesh>(vertices, indices);
		}
		return nullptr;
	}
	void Batch::pushBack(ref<Mesh> mesh)
	{
		this->m_Meshes.push_back(mesh);
	}
	const size_t* Batch::calulateSize()
	{
		size_t verticesCount = 0;
		for (ref<Mesh> m : this->m_Meshes)
		{
			verticesCount += m->m_Vertices.size();
		}
		this->m_Size = verticesCount * Vertex::getLayout().calculateVertexSize();
		return &this->m_Size;
	}

	BatchManager::BatchManager(size_t batchSize) : m_BatchSize(batchSize), m_Batches(std::unordered_map<ref<Window>, std::vector<ref<Batch>>>()) {}
	BatchManager::~BatchManager() {}
	void BatchManager::pushBack(ref<Window> target, ref<Renderable> renderable)
	{
		if (!this->m_Batches.empty())
		{
			for (ref<Batch> b : this->m_Batches[target])
			{
				if (b->m_Material == renderable->m_Material)
				{
					if (*b->calulateSize() + *renderable->m_Mesh->calculateSize() < this->m_BatchSize)
					{
						b->pushBack(renderable->m_Mesh);
						return;
					}
				}
			}
		}
		ref<Batch> b = std::make_shared<Batch>(renderable->m_Material);
		b->pushBack(renderable->m_Mesh);
		this->m_Batches[target].push_back(b);
	}

}
