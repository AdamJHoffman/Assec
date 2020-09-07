#pragma once
#include "graphics/renderer/Material.h"
#include "graphics/renderer/Mesh.h"
#include "graphics/renderer/Renderable.h"
#include "graphics/GraphicsContext.h"
#include "graphics/Window.h"

namespace assec::graphics
{
	class Batch
	{
	public:
		Batch(const Material& material);
		~Batch();
		const ref<Mesh> getMesh();
		void submit(const Renderable& renderable);
		void clear() { TIME_FUNCTION; this->vertices.clear(); this->indices.clear(); this->m_Textures.clear(); }
		void prepare(glm::mat4 viewProjectionMatrix, GraphicsContext* graphicscontext);
		const size_t* calulateSize();
		const Material m_Material;
		std::vector<Texture*> m_Textures = std::vector<Texture*>();
	private:
		size_t m_Size = 0;
		std::vector<Vertex> vertices = std::vector<Vertex>();
		std::vector<int> indices = std::vector<int>();
	};

	class BatchManager
	{
	public:
		BatchManager(size_t batchSize, size_t maxTexture);
		~BatchManager();
		const inline std::unordered_map<const Window*, std::vector<ref<Batch>>>* getBatches() const { TIME_FUNCTION; return &this->m_Batches; }
		void submit(const Window& target, const Renderable& renderable);
		void clear() { TIME_FUNCTION; this->m_Batches.clear(); }
	private:
		std::unordered_map<const Window*, std::vector<ref<Batch>>> m_Batches = std::unordered_map<const Window*, std::vector<ref<Batch>>>();
		size_t m_BatchSize;
		size_t m_MaxTextures;
	};
}
