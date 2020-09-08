#pragma once
#include <glm/glm.hpp>
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
		const char* m_Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const char* tag)
			: m_Tag(tag) {}

		operator const char* () const { return this->m_Tag; }
	};

	struct TransformComponent
	{
		glm::mat4 m_Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : m_Transform(transform) {}

		operator glm::mat4& () { return m_Transform; }
		operator const glm::mat4& () const { return m_Transform; }
	};

	struct OrthoCameraComponent
	{
		Camera m_Camera;

		OrthoCameraComponent() = default;
		OrthoCameraComponent(const OrthoCameraComponent&) = default;
		OrthoCameraComponent(const Camera& camera) : m_Camera(camera) {}

		void onEvent(const events::Event& event)
		{
			events::Dispatcher dispatcher = events::Dispatcher(event);
			dispatcher.dispatch<events::WindowResizeEvent>([this](const events::WindowResizeEvent& event)
				{
					this->setViewportSize(event.m_Width, event.m_Height);
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

		void setViewportSize(uint32_t width, uint32_t height)
		{
			m_AspectRatio = (float)width / (float)height;
			recalculateProjection();
		}

		void recalculateProjection()
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;

			this->m_Camera.m_Projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar) * glm::inverse(this->viewMatrix);
		}

		void setViewMatrix(const glm::mat4& viewmatrix)
		{
			this->viewMatrix = viewmatrix;
			this->recalculateProjection();
		}

		operator Camera& () { return m_Camera; }
		operator const Camera& () const { return m_Camera; }

	private:
		float m_OrthographicSize = 10.0f, m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f, m_AspectRatio = 1.0f;
		glm::mat4 viewMatrix = glm::mat4(1.0f);
	};

	struct MeshComponent
	{
		graphics::Mesh* m_Mesh = nullptr;

		~MeshComponent() { delete this->m_Mesh; }
		MeshComponent(const std::vector<graphics::Vertex>& vertices, const std::vector<int>& indices)
			: m_Mesh(new graphics::Mesh(vertices, indices)) {}
		MeshComponent(const MeshComponent& other)
			: m_Mesh(new graphics::Mesh(other.m_Mesh->m_Vertices, other.m_Mesh->m_Indices)) {}

		operator graphics::Mesh& () { return *this->m_Mesh; }
		operator const graphics::Mesh& () const { return *this->m_Mesh; }
	};

	struct MaterialComponent
	{
		graphics::Material* m_Material = nullptr;

		~MaterialComponent() { delete this->m_Material; }
		MaterialComponent(graphics::ShaderProgram& shaderProgram, graphics::Texture& texture)
			: m_Material(new graphics::Material(shaderProgram, texture)) {}
		MaterialComponent(const MaterialComponent& other)
			: m_Material(new graphics::Material(other.m_Material->m_ShaderProgram, other.m_Material->m_Texture)) {}

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
