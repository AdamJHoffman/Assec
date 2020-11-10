#include "acpch.h"

#include "Batch.h"

namespace assec::graphics
{
	Batch::Batch(const Material& material) : m_Material(material) { TIME_FUNCTION; }
	Batch::~Batch() { TIME_FUNCTION; }
	const ref<Mesh> Batch::createMesh()
	{
		TIME_FUNCTION;
		return std::make_shared<Mesh>(this->m_Vertices, this->m_Indices);
	}
	void Batch::submit(const Renderable& renderable)
	{
		TIME_FUNCTION;
		int indexOffset = static_cast<int>(this->m_Vertices.size());
		auto& texture = std::find(this->m_Textures.begin(), this->m_Textures.end(), renderable.m_Material.m_Texture);
		if (texture == this->m_Textures.end())
		{
			this->m_Textures.push_back(renderable.m_Material.m_Texture);
			texture = this->m_Textures.end() - 1;
		}
		renderable.m_Mesh.setTextureIndex(static_cast<float>(std::distance(this->m_Textures.begin(), texture)));
		this->m_Vertices.insert(this->m_Vertices.end(), renderable.m_Mesh.getVertices().begin(), renderable.m_Mesh.getVertices().end());
		for (int i : renderable.m_Mesh.getIndices()) { this->m_Indices.push_back(indexOffset + i); }
	}
	void Batch::prepare(const glm::mat4& viewProjectionMatrix, const GraphicsContext* graphicscontext)
	{
		TIME_FUNCTION;
		this->m_Material.m_ShaderProgram->bind();
		this->m_Material.m_ShaderProgram->loadMat4(AC_SHADER_VIEWPROJECTIONMATRIX_NAME, viewProjectionMatrix);
		for (int i = 0; i < this->m_Textures.size(); i++)
		{
			this->m_Material.m_ShaderProgram->loadInt("u_images[" + std::to_string(i) + "]", i);
			graphicscontext->setActiveTexture(i);
			this->m_Textures[i]->bind();
		}
	}
	const size_t Batch::calulateSize()
	{
		TIME_FUNCTION;
		return this->m_Vertices.size() * Vertex::getLayout().calculateVertexSize();
	}

	BatchManager::BatchManager(const size_t& batchSize, const size_t& maxTextures) : m_BatchSize(batchSize), m_MaxTextures(maxTextures) { TIME_FUNCTION; }
	BatchManager::~BatchManager() { TIME_FUNCTION; }
	void BatchManager::submit(const Window& target, const Renderable& renderable)
	{
		TIME_FUNCTION;
		if (!this->m_Batches.empty())
		{
			for (auto& b : this->m_Batches[&target])
			{
				if (b.m_Material.m_ShaderProgram == renderable.m_Material.m_ShaderProgram)
				{
					if ((b.calulateSize() + renderable.m_Mesh.calculateSize()) < this->m_BatchSize)
					{
						if (std::count(b.m_Textures.begin(), b.m_Textures.end(), renderable.m_Material.m_Texture) ||
							b.m_Textures.size() + 1 < this->m_MaxTextures)
						{
							b.submit(renderable);
							return;
						}
					}
				}
			}
		}
		Batch b = Batch(renderable.m_Material);
		b.submit(renderable);
		this->m_Batches[&target].push_back(b);
	}

}
