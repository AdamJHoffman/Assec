﻿#pragma once
#include "core/Config.h"
#include "log/Logger.h"
#include <fstream>
#include <sstream>
#include <stb_image.h>

namespace assec::util
{
	class Loader
	{
	public:
		struct TextureData
		{
			uint32_t m_Width, m_Height, m_NrChannels;
			unsigned char* m_Data;
		};
		static Loader& getLoader()
		{
			TIME_FUNCTION;
			static Loader loader;
			return loader;
		}
		static std::string loadFile(const char* file)
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
		static TextureData loadImage(const char* file)
		{
			TIME_FUNCTION;
			int width, height, nrChannels;
			unsigned char* data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb);
			if (stbi_failure_reason())
				std::cout << stbi_failure_reason();
			TextureData result = { static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(nrChannels), data };
			return result;
		}
		~Loader() { TIME_FUNCTION; }
	private:
		Loader() { TIME_FUNCTION; }
		static std::ifstream m_InputStream;
	};
}
