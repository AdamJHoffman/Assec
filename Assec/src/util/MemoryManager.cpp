#include "acpch.h"
#include "MemoryManager.h"

namespace assec::util
{
	MemoryManager::MemoryManager() {}
	MemoryManager::~MemoryManager() {}
	uint32_t MemoryManager::m_Allocated = 0;
	uint32_t MemoryManager::m_Freed = 0;
}