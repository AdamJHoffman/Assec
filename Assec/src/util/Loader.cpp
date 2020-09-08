#include "acpch.h"
#include "Loader.h"

namespace assec::util
{
	std::ifstream Loader::m_InputStream;
	std::string Loader::loadFile(const char* file)
	{
		TIME_FUNCTION;
		m_InputStream.open(file);
		if (!m_InputStream)
		{
			AC_CORE_WARNING("Assertion failed: {0}: {1}", "unable to open file", file);
		}
		std::stringstream text;
		text << m_InputStream.rdbuf();
		m_InputStream.close();
		return text.str();
	}
	Loader::TextureData Loader::loadImage(const char* file)
	{
		TIME_FUNCTION;
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb);
		if (stbi_failure_reason())
			std::cout << stbi_failure_reason();
		TextureData result = { static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(nrChannels), data };
		return result;
	}
}
