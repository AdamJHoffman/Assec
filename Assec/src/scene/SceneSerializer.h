#pragma once

#include "Scene.h"

namespace assec::scene
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const ref<Scene>& scene);
		~SceneSerializer();

		void serialize(const std::string& path);
		void serializeRuntime(const std::string& path);

		bool deserialize(const std::string& path);
		bool deserializeRuntime(const std::string& path);
	private:
		ref<Scene> m_Scene;
	};
} // assec::scene
