#pragma once

namespace assec::graphics
{
	class Batch
	{
	public:
		Batch(ref<Material> material);
		~Batch();
		const ref<Mesh> getMesh();
		void pushBack(ref<Mesh> mesh);
		void clear() { this->m_Meshes.clear(); }
		const size_t* calulateSize();
		ref<Material> m_Material;
	private:
		size_t m_Size;
		std::vector<ref<Mesh>> m_Meshes;
	};

	class BatchManager
	{
	public:
		BatchManager(size_t batchSize);
		~BatchManager();
		const inline std::unordered_map<ref<Window>, std::vector<ref<Batch>>>* getBatches() const { return &this->m_Batches; }
		void pushBack(ref<Window> target, ref<Renderable> renderable);
		void clear() { this->m_Batches.clear(); }
	private:
		std::unordered_map<ref<Window>, std::vector<ref<Batch>>> m_Batches;
		size_t m_BatchSize;
	};
}
