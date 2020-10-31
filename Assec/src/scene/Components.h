#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>
#include <imgui.h>

#include "Camera.h"

#include "graphics/renderer/Renderable.h"

#include "event/Event.h"
#include "event/WindowEvents.h"

#include "Entity.h"


namespace assec::scene
{

	struct TagComponent
	{
		std::string m_Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: m_Tag(std::string(tag)) {}

		operator const char* () const { return this->m_Tag.c_str(); }
	};

	struct TransformComponent
	{
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
		{
			glm::quat rotation;
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(transform, this->scale, rotation, this->translation, skew, perspective);
			this->rotation = glm::degrees(glm::eulerAngles(rotation));
		}

		glm::mat4 toMatrix()
		{
			return glm::translate(glm::mat4(1.0f), this->translation)
				* glm::toMat4(glm::quat(glm::radians(this->rotation)))
				* glm::scale(glm::mat4(1.0f), this->scale);
		}
	};

	struct CameraComponent
	{
		Camera m_Camera;
		Camera::projectionType m_Type;
		bool m_Primary = false, m_FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const Camera& camera, const Camera::projectionType& type) : m_Camera(camera), m_Type(type) {}

		void onEvent(const events::Event& event)
		{
			events::Dispatcher dispatcher = events::Dispatcher(event);
			dispatcher.dispatch<events::WindowResizeEvent>([this](const events::WindowResizeEvent& event)
				{
					if (!this->m_FixedAspectRatio)
					{
						this->setViewportSize(event.m_Width, event.m_Height);
					}
					return false;
				});
		}

		void orthographic(float size, float nearClip, float farClip)
		{
			m_OrthographicSize = size;
			m_OrthographicNear = nearClip;
			m_OrthographicFar = farClip;
			recalculateProjection();
		}

		void perspective(float fov, float nearClip, float farClip)
		{
			this->m_PerspectiveFov = fov;
			this->m_PerspectiveNear = nearClip;
			this->m_PerspectiveFar = farClip;
			recalculateProjection();
		}

		void setViewportSize(uint32_t width, uint32_t height)
		{
			m_AspectRatio = (float)width / (float)height;
			recalculateProjection();
		}

		void recalculateProjection()
		{
			switch (this->m_Type)
			{
			case Camera::projectionType::ORTHOGRAPHIC:
				float orthoLeft, orthoRight, orthoBottom, orthoTop;
				orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
				orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
				orthoBottom = -m_OrthographicSize * 0.5f;
				orthoTop = m_OrthographicSize * 0.5f;

				this->m_Camera.m_Projection = glm::ortho(orthoLeft, orthoRight,
					orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar) * glm::inverse(this->viewMatrix);
				break;
			case Camera::projectionType::PERSPECTIVE:
				this->m_Camera.m_Projection = glm::perspective(this->m_PerspectiveFov,
					this->m_AspectRatio, this->m_PerspectiveNear, this->m_PerspectiveFar) * glm::inverse(this->viewMatrix);
			}
		}

		void setViewMatrix(const glm::mat4& viewmatrix)
		{
			this->viewMatrix = viewmatrix;
			this->recalculateProjection();
		}

		operator Camera& () { return m_Camera; }
		operator const Camera& () const { return m_Camera; }

		float m_OrthographicSize = 10.0f, m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f, m_AspectRatio = 1.0f;
		float m_PerspectiveFov = 90.0f, m_PerspectiveNear = 0.1f, m_PerspectiveFar = 100.0f;
	private:
		glm::mat4 viewMatrix = glm::mat4(1.0f);
	};

	struct MeshComponent
	{
		ref<graphics::Mesh> m_Mesh = nullptr;
		std::string m_Path = "";

		~MeshComponent() {}
		MeshComponent(const std::vector<graphics::Vertex>& vertices, const std::vector<int>& indices)
			: m_Mesh(std::make_shared<graphics::Mesh>(vertices, indices)) {}
		MeshComponent()
			: m_Mesh(std::make_shared<graphics::Mesh>()) {}
		MeshComponent(const MeshComponent& other)
			: m_Mesh(std::make_shared<graphics::Mesh>(other.m_Mesh->getVertices(), other.m_Mesh->getIndices())) {}

		operator graphics::Mesh& () { return *this->m_Mesh; }
		operator const graphics::Mesh& () const { return *this->m_Mesh; }
	};

	struct MaterialComponent
	{
		ref<graphics::Material> m_Material = nullptr;
		std::string m_TexturePath = "", m_ShaderPath = "";

		~MaterialComponent() { }
		MaterialComponent(ref<graphics::ShaderProgram> shaderProgram, ref<graphics::Texture> texture)
			: m_Material(std::make_shared<graphics::Material>(shaderProgram, texture)) {}
		MaterialComponent()
			: m_Material(std::make_shared<graphics::Material>()) {}
		MaterialComponent(const MaterialComponent& other)
			: m_Material(std::make_shared<graphics::Material>(other.m_Material->m_ShaderProgram, other.m_Material->m_Texture)) {}

		operator graphics::Material& () { return *this->m_Material; }
		operator const graphics::Material& () const { return *this->m_Material; }
	};

	struct NativeScriptComponent
	{
		Entity* m_Instance = nullptr;

		std::function<void(entt::entity, Scene*)> m_InstantiateFunction;
		std::function<void()> m_DestroyInstanceFunction;

		template<typename T> void bind()
		{
			this->m_OnCreateFunction = [&]() { ((T*)this->m_Instance)->onCreate(); };
			this->m_OnDestroyFunction = [&]() { ((T*)this->m_Instance)->onDestroy(); };
			this->m_OnEventFunction = [&](const events::Event& event) { ((T*)this->m_Instance)->onEvent(event); };

			this->m_InstantiateFunction = [&](entt::entity handle, Scene* scene) { this->m_Instance = new T(handle, scene); this->m_OnCreateFunction(); };
			this->m_DestroyInstanceFunction = [&]() { this->m_OnDestroyFunction(); delete (T*)this->m_Instance; this->m_Instance = nullptr; };
		}

		void onEvent(const events::Event& event)
		{
			this->m_OnEventFunction(event);
		}

	private:
		std::function<void()> m_OnCreateFunction;
		std::function<void()> m_OnDestroyFunction;
		std::function<void(const events::Event&)> m_OnEventFunction;
	};
}
