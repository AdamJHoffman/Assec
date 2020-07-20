#pragma once
#include "acpch.h"

namespace assec::util
{
	template<typename map>
	std::vector<typename map::key_type> Keys(const map& m)
	{
		std::vector<typename map::key_type> r;
		r.reserve(m.size());
		for (const auto& kvp : m)
		{
			r.push_back(kvp.first);
		}
		return r;
	}

	template<typename map>
	std::vector<typename map::mapped_type> Values(const map& m)
	{
		std::vector<typename map::mapped_type> r;
		r.reserve(m.size());
		for (const auto& kvp : m)
		{
			r.push_back(kvp.second);
		}
		return r;
	}
}