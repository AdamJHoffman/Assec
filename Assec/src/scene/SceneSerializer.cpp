#include "acpch.h"

#include <yaml-cpp/yaml.h>

#include "SceneSerializer.h"
#include "Entity.h"

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}
namespace assec::scene
{

	SceneSerializer::SceneSerializer(const ref<Scene>& scene) : m_Scene(scene) {}

	SceneSerializer::~SceneSerializer() {}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << "12837192831273"; // TODO: Entity ID goes here

		if (entity.hasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = entity.getComponent<TagComponent>().m_Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent
		}

		if (entity.hasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = entity.getComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << tc.translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.scale;

			out << YAML::EndMap; // TransformComponent
		}

		if (entity.hasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = entity.getComponent<CameraComponent>();
			auto& camera = cameraComponent.m_Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)cameraComponent.m_Type;
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << cameraComponent.m_PerspectiveFov;
			out << YAML::Key << "PerspectiveNear" << YAML::Value << cameraComponent.m_PerspectiveNear;
			out << YAML::Key << "PerspectiveFar" << YAML::Value << cameraComponent.m_PerspectiveFar;
			out << YAML::Key << "OrthographicSize" << YAML::Value << cameraComponent.m_OrthographicSize;
			out << YAML::Key << "OrthographicNear" << YAML::Value << cameraComponent.m_OrthographicNear;
			out << YAML::Key << "OrthographicFar" << YAML::Value << cameraComponent.m_OrthographicFar;
			out << YAML::EndMap; // Camera

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.m_Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.m_FixedAspectRatio;

			out << YAML::EndMap; // CameraComponent
		}

		if (entity.hasComponent<MeshComponent>())
		{
			out << YAML::Key << "MeshComponent";
			out << YAML::BeginMap; // MeshComponent

			auto& meshComponent = entity.getComponent<MeshComponent>();
			//out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			out << YAML::EndMap; // MeshComponent
		}

		if (entity.hasComponent<MaterialComponent>())
		{
			out << YAML::Key << "MaterialComponent";
			out << YAML::BeginMap; // MaterialComponent

			auto& materialComponent = entity.getComponent<MaterialComponent>();
			//out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			out << YAML::EndMap; // MaterialComponent
		}

		out << YAML::EndMap; // Entity
	}

	void SceneSerializer::serialize(const std::string& path)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
			{
				Entity entity = { entityID, m_Scene.get() };
				if (!entity)
					return;

				SerializeEntity(out, entity);
			});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(path);
		fout << out.c_str();
	}

	void SceneSerializer::serializeRuntime(const std::string& path)
	{
		AC_CORE_ASSERT_(false, "not implemeneted");
	}

	bool SceneSerializer::deserialize(const std::string& path)
	{
		std::ifstream stream(path);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		AC_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				uint64_t uuid = entity["Entity"].as<uint64_t>(); // TODO

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				AC_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->createEntity(name);

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					// Entities always have transforms
					auto& tc = deserializedEntity.getComponent<TransformComponent>();
					tc.translation = transformComponent["Translation"].as<glm::vec3>();
					tc.rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.scale = transformComponent["Scale"].as<glm::vec3>();
				}

				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.addComponent<CameraComponent>();

					auto& cameraProps = cameraComponent["Camera"];
					cc.m_Type = static_cast<Camera::projectionType>(cameraProps["ProjectionType"].as<int>());

					cc.m_PerspectiveFov = cameraProps["PerspectiveFOV"].as<float>();
					cc.m_PerspectiveNear = cameraProps["PerspectiveNear"].as<float>();
					cc.m_PerspectiveFar = cameraProps["PerspectiveFar"].as<float>();

					cc.m_OrthographicSize = cameraProps["OrthographicSize"].as<float>();
					cc.m_OrthographicNear = cameraProps["OrthographicNear"].as<float>();
					cc.m_OrthographicFar = cameraProps["OrthographicFar"].as<float>();

					cc.m_Primary = cameraComponent["Primary"].as<bool>();
					cc.m_AspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
				}

				//auto spriteRendererComponent = entity["SpriteRendererComponent"];
				//if (spriteRendererComponent)
				//{
				//	auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
				//	src.Color = spriteRendererComponent["Color"].as<glm::vec4>();
				//}
			}
		}

		return true;
	}
	bool SceneSerializer::deserializeRuntime(const std::string& path)
	{
		AC_CORE_ASSERT_(false, "not implemeneted");
		return false;
	}
}
