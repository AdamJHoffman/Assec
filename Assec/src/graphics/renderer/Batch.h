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
		const ref<Mesh> createMesh();
		void submit(const Renderable& renderable);
		void clear() { TIME_FUNCTION; this->m_Vertices.clear(); this->m_Indices.clear(); this->m_Textures.clear(); }
		void prepare(const glm::mat4& viewProjectionMatrix, const GraphicsContext* graphicscontext);
		const size_t calulateSize();
	private:
		Material m_Material = Material();
		std::vector<ref<Texture>> m_Textures = std::vector<ref<Texture>>();
		std::vector<Vertex> m_Vertices = std::vector<Vertex>();
		std::vector<int> m_Indices = std::vector<int>();
		friend class BatchManager;
	};

	class BatchManager
	{
	public:
		BatchManager(const size_t& batchSize, const size_t& maxTexture);
		~BatchManager();
		const inline std::unordered_map<const Window*, std::vector<Batch>>& getBatches() const { TIME_FUNCTION; return this->m_Batches; }
		void submit(const Window& target, const Renderable& renderable);
		void clear() { TIME_FUNCTION; this->m_Batches.clear(); }
	private:
		std::unordered_map<const Window*, std::vector<Batch>> m_Batches = std::unordered_map<const Window*, std::vector<Batch>>();
		size_t m_BatchSize = 0;
		size_t m_MaxTextures = 0;
	};
}
