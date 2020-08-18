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
		std::string loadFile(const char* file)
		{
			TIME_FUNCTION;
			this->m_InputStream.open(file);
			if (!this->m_InputStream)
			{
				AC_CORE_WARNING("Assertion failed: {0}: {1}", "unable to open file", file);
			}
			std::stringstream text;
			text << this->m_InputStream.rdbuf();
			this->m_InputStream.close();
			return text.str();
		}
		TextureData loadImage(const char* file)
		{
			TIME_FUNCTION;
			int width, height, nrChannels;
			unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
			return { static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(nrChannels), data };
		}
		~Loader() { TIME_FUNCTION; }
	private:
		Loader() { TIME_FUNCTION; }
		std::ifstream m_InputStream;
	};
}
