#pragma once

#include <fstream>
#include <sstream>

#include "core/Base.h"

#include "graphics/renderer/Mesh.h"

#include "scene/Scene.h"

#include "log/Logger.h"

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
		static std::string loadFile(const char*);
		static std::vector<graphics::Mesh> loadgltfMesh(const char*);
		~Loader() { TIME_FUNCTION; }
	private:
		Loader() { TIME_FUNCTION; }
		static std::ifstream m_InputStream;
	};
}
