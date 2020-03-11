#pragma once

namespace assec::util
{
	class MemoryManager
	{
	public:
		static MemoryManager& getMemoryManager() { static MemoryManager s_Instance; return s_Instance; }
		MemoryManager::~MemoryManager() {}
		inline const uint32_t* getUsed() const { return &this->m_Allocated - this->m_Freed; }
		uint32_t m_Allocated;
		uint32_t m_Freed;
		MemoryManager(MemoryManager const&) = delete;
		void operator=(MemoryManager const&) = delete;
	private:
		MemoryManager() : m_Allocated(0), m_Freed(0) {}
	};
}