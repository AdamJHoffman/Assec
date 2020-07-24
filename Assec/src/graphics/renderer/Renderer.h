#pragma once
#include "core/Config.h"
#include "graphics/renderer/Batch.h"
#include <glm/glm.hpp>
#include "graphics/renderer/Renderable.h"
#include "graphics/Window.h"

namespace assec::graphics
{
	class Renderer
	{
	public:
		virtual ~Renderer() { TIME_FUNCTION; }
		virtual void endScene() = 0;
		void beginScene(const glm::mat4& viewProjectionMatrix)
		{
			TIME_FUNCTION;
			this->m_ViewProjectionMatrix = viewProjectionMatrix;
		}
		void submit(ref<Window> target, ref<Renderable> renderable)
		{
			TIME_FUNCTION;
			this->m_BatchManager.pushBack(target, renderable);
		}
	protected:
		Renderer() { TIME_FUNCTION; }
		glm::mat4& m_ViewProjectionMatrix = glm::mat4(1.0f);
		ref<graphics::VertexArray> m_VertexArray = nullptr;
		BatchManager m_BatchManager = BatchManager(BATCH_MAX_SIZE, BATCH_MAX_TEXTURES);
	};

	class Renderer2D : public Renderer
	{
	public:
		Renderer2D();
		~Renderer2D();
		virtual void endScene() override;
	};
}
