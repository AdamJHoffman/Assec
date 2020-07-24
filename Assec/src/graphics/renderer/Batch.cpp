#include "acpch.h"
#include "Batch.h"

namespace assec::graphics
{
	Batch::Batch(ref<Material> material) : m_Material(material) { TIME_FUNCTION; }
	Batch::~Batch() { TIME_FUNCTION; }
	const ref<Mesh> Batch::getMesh()
	{
		TIME_FUNCTION;
		return std::make_shared<Mesh>(this->vertices, this->indices);
	}
	void Batch::pushBack(ref<Renderable> renderable)
	{
		TIME_FUNCTION;
		int indicesOffset = this->vertices.size();
		for (Vertex v : renderable->m_Mesh->m_Vertices)
		{
			this->vertices.push_back(v);
		}
		for (int i : renderable->m_Mesh->m_Indices)
		{
			this->indices.push_back(indicesOffset + i);
		}
		this->m_Textures.push_back(renderable->m_Material->m_Texture);
	}
	void Batch::prepare(glm::mat4 viewProjectionMatrix, GraphicsContext* graphicscontext)
	{
		TIME_FUNCTION;
		this->m_Material->m_ShaderProgram->bind();
		this->m_Material->m_ShaderProgram->loadMat4(AC_SHADER_VIEWPROJECTIONMATRIX_NAME, viewProjectionMatrix);
		for (int i = 0; i < this->m_Textures.size(); i++)
		{
			this->m_Material->m_ShaderProgram->loadInt("u_images[" + std::to_string(i) + "]", i);
			graphicscontext->setActiveTexture(i);
			this->m_Textures[i]->bind();
		}
	}
	const size_t* Batch::calulateSize()
	{
		TIME_FUNCTION;
		this->m_Size = this->vertices.size() * Vertex::getLayout().calculateVertexSize();
		return &this->m_Size;
	}

	BatchManager::BatchManager(size_t batchSize, size_t maxTextures) : m_BatchSize(batchSize), m_MaxTextures(maxTextures), m_Batches(std::unordered_map<ref<Window>, std::vector<ref<Batch>>>()) { TIME_FUNCTION; }
	BatchManager::~BatchManager() { TIME_FUNCTION; }
	void BatchManager::pushBack(ref<Window> target, ref<Renderable> renderable)
	{
		TIME_FUNCTION;
		if (!this->m_Batches.empty())
		{
			for (ref<Batch> b : this->m_Batches[target])
			{
				if (b->m_Material->m_ShaderProgram == renderable->m_Material->m_ShaderProgram)
				{
					if (*b->calulateSize() + *renderable->m_Mesh->calculateSize() < this->m_BatchSize)
					{
						if (std::count(b->m_Textures.begin(), b->m_Textures.end(), renderable->m_Material->m_Texture) ||
							b->m_Textures.size() + 1 < this->m_MaxTextures)
						{
							b->pushBack(renderable);
							return;
						}
					}
				}
			}
		}
		ref<Batch> b = std::make_shared<Batch>(renderable->m_Material);
		b->pushBack(renderable);
		this->m_Batches[target].push_back(b);
	}

}
