#pragma once

#include <glm/glm.hpp>

#include "core/Base.h"

#include "graphics/renderer/Batch.h"
#include "graphics/renderer/Renderable.h"
#include "graphics/Window.h"

namespace assec::graphics
{
	class Renderer
	{
	public:
		virtual ~Renderer() { TIME_FUNCTION; }
		static void init(CONST_REF(int) maxSize, CONST_REF(int) maxTextures);
		static void beginScene(CONST_REF(glm::mat4) viewProjectionMatrix);
		static void endScene();
		static void submit(CONST_REF(Window) target, REF(Renderable) renderable);
	protected:
		Renderer() { TIME_FUNCTION; }
		static glm::mat4& m_ViewProjectionMatrix;
		static ref<graphics::VertexArray> m_VertexArray;
		static BatchManager m_BatchManager;
	};
} // namespace assec::graphics
