#include "acpch.h"

#include <glm/gtc/type_ptr.hpp>

#include "graphics/renderer/Renderer.h"
#include "graphics/renderer/Batch.h"

#include "util/misc.h"

namespace assec::graphics
{
	glm::mat4& Renderer::m_ViewProjectionMatrix = glm::mat4(1.0f);
	ref<VertexArray> Renderer::m_VertexArray = nullptr;
	BatchManager Renderer::m_BatchManager = BatchManager(0, 0);
	void Renderer::init(CONST_REF(int) maxSize, CONST_REF(int) maxTextures)
	{
		m_BatchManager = BatchManager(maxSize, maxTextures);
	}
	void Renderer::beginScene(CONST_REF(glm::mat4) viewProjectionMatrix)
	{
		TIME_FUNCTION;
		m_ViewProjectionMatrix = viewProjectionMatrix;
	}
	void Renderer::endScene()
	{
		TIME_FUNCTION;
		for (auto& key : util::Keys(m_BatchManager.getBatches()))
		{
			key->makeContextCurrent();
			if (m_VertexArray == nullptr)
			{
				m_VertexArray = key->getWindowData().graphicsContext->createVertexArray(Type::DYNAMIC_DRAW, sizeof(Vertex) * 1000);
			}
			for (auto& b : (m_BatchManager.getBatches())[key])
			{
				b.prepare(m_ViewProjectionMatrix, *key->getWindowData().graphicsContext);
				m_VertexArray->getVertexBuffer().addSubData(&b.createMesh()->createVerticesData()[0], sizeof(float) * b.createMesh()->createVerticesData().size(), 0);
				m_VertexArray->getIndexBuffer().addSubData(&b.createMesh()->getIndices()[0], sizeof(uint32_t) * b.createMesh()->getIndices().size(), 0);
				m_VertexArray->mapVertexAttributes(b.createMesh()->calculateSize(), Vertex::getLayout());
				m_VertexArray->render();
			}
		}
		m_BatchManager.clear();
	}
	void Renderer::submit(CONST_REF(Window) target, REF(Renderable) renderable)
	{
		TIME_FUNCTION;
		m_BatchManager.submit(target, renderable);
	}
} // namespace assec::graphics
