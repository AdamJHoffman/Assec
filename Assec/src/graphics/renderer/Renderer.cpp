#include "acpch.h"
#include "Renderer.h"
#include "Batch.h"
#include "util/misc.h"
#include "core/OpenGLConfig.h"
#include "glm/gtc/type_ptr.hpp"

namespace assec::graphics
{
	glm::mat4& Renderer::m_ViewProjectionMatrix = glm::mat4(1.0f);
	graphics::VertexArray* Renderer::m_VertexArray = nullptr;
	BatchManager Renderer::m_BatchManager = BatchManager(BATCH_MAX_SIZE, BATCH_MAX_TEXTURES);
	void Renderer::beginScene(const glm::mat4& viewProjectionMatrix)
	{
		TIME_FUNCTION;
		m_ViewProjectionMatrix = viewProjectionMatrix;
	}
	void Renderer::endScene()
	{
		TIME_FUNCTION;
		for (auto key : util::Keys(*m_BatchManager.getBatches()))
		{
			key->makeCurrent();
			if (m_VertexArray == nullptr)
			{
				m_VertexArray = &key->getWindowData().m_GraphicsContext->createVertexArray(Type::DYNAMIC_DRAW, sizeof(Vertex) * 1000);
			}
			for (auto b : (*m_BatchManager.getBatches()).at(key))
			{
				b->prepare(m_ViewProjectionMatrix, key->getWindowData().m_GraphicsContext);
				m_VertexArray->m_VertexBuffer->addSubData(&b->getMesh()->getVerticesData()[0], sizeof(float) * b->getMesh()->getVerticesData().size(), 0);
				m_VertexArray->m_IndexBuffer->addSubData(&b->getMesh()->m_Indices[0], sizeof(uint32_t) * b->getMesh()->m_Indices.size(), 0);
				m_VertexArray->mapVertexAttributes(*b->getMesh()->calculateSize(), Vertex::getLayout());
				m_VertexArray->render();
			}
		}
		m_BatchManager.clear();
	}
	void Renderer::submit(const Window& target, const Renderable& renderable)
	{
		TIME_FUNCTION;
		m_BatchManager.pushBack(target, renderable);
	}
}
