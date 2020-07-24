#pragma once

namespace assec::graphics
{
	class Batch
	{
	public:
		Batch(ref<Material> material);
		~Batch();
		const ref<Mesh> getMesh();
		void pushBack(ref<Renderable> renderable);
		void clear() { TIME_FUNCTION; this->vertices.clear(); this->indices.clear(); this->m_Textures.clear(); }
		void prepare(glm::mat4 viewProjectionMatrix, GraphicsContext* graphicscontext);
		const size_t* calulateSize();
		ref<Material> m_Material;
		std::vector<ref<Texture>> m_Textures = std::vector<ref<Texture>>();
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
		const inline std::unordered_map<ref<Window>, std::vector<ref<Batch>>>* getBatches() const { TIME_FUNCTION; return &this->m_Batches; }
		void pushBack(ref<Window> target, ref<Renderable> renderable);
		void clear() { TIME_FUNCTION; this->m_Batches.clear(); }
		size_t m_MaxTextures;
	private:
		std::unordered_map<ref<Window>, std::vector<ref<Batch>>> m_Batches;
		size_t m_BatchSize;
	};
}
