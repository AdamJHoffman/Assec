#pragma once
#include "core/Config.h"
#include "log/Logger.h"
#include "scene/Scene.h"
#include "graphics/renderer/Mesh.h"
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
		struct FileDialogData
		{
			const char* m_FileTypes;
			std::function<void(const char*)> m_FileFoundCallback;
		};
		static std::string loadFile(const char*);
		static TextureData loadImage(const char*);
		static std::vector<graphics::Mesh> loadgltfMesh(const char*);
		~Loader() { TIME_FUNCTION; }
	private:
		Loader() { TIME_FUNCTION; }
		static std::ifstream m_InputStream;
	};
}
