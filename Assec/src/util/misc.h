#pragma once

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

	template<typename T> std::vector<unsigned char> toVector(T t)
	{
		std::vector<unsigned char> data(sizeof(t));
		std::memcpy(data.data(), &t, sizeof(t));
		return data;
	}

	//float fromVector(const std::vector<unsigned char>& data)
	//{
	//	float f;
	//	if (data.size() != sizeof(f))
	//		throw std::runtime_error{ "Size of data in vector and float do not match" };
	//	std::memcpy(&f, data.data(), sizeof(f));
	//	return f;
	//}
}
