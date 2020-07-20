#pragma once
#include <glm/glm.hpp>
#include "graphics/renderer/Renderable.h"
#include "graphics/Window.h"

namespace assec::graphics
{
	class Renderer
	{
	public:
		virtual ~Renderer() {}
		virtual void endScene() = 0;
		void beginScene(const glm::mat4& viewProjectionMatrix)
		{
			this->m_ViewProjectionMatrix = viewProjectionMatrix;
		}
		void submit(ref<Window> target, ref<Renderable> renderable)
		{
			this->m_Renderables[target].push_back(renderable);
		}
	protected:
		Renderer() {}
		glm::mat4& m_ViewProjectionMatrix = glm::mat4(1.0f);
		std::unordered_map<ref<Window>, std::vector<ref<Renderable>>> m_Renderables = std::unordered_map<ref<Window>, std::vector<ref<Renderable>>>();
		ref<graphics::VertexArray> m_VertexArray = nullptr;
	};

	class Renderer2D : public Renderer
	{
	public:
		Renderer2D();
		~Renderer2D();
		virtual void endScene() override;
	};
}