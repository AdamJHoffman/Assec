#pragma once

namespace assec::util
{
	class MemoryManager
	{
	public:
		static inline const uint32_t getUsed() { return m_Allocated - m_Freed; }
		static uint32_t m_Allocated;
		static uint32_t m_Freed;
		MemoryManager(MemoryManager const&) = delete;
		void operator=(MemoryManager const&) = delete;
	private:
		MemoryManager();
		~MemoryManager();
	};
}
