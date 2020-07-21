#include "acpch.h"
#include "Renderer.h"
#include "Batch.h"
#include "util/misc.h"
#include "core/OpenGLConfig.h"
#include "glm/gtc/type_ptr.hpp"

namespace assec::graphics
{
	Renderer2D::Renderer2D() {}
	Renderer2D::~Renderer2D() {}
	void Renderer2D::endScene()
	{
		for (auto key : util::Keys(*this->m_BatchManager.getBatches()))
		{
			key->makeCurrent();
			key->getWindowData().m_GraphicsContext->setActiveTexture(0);
			if (this->m_VertexArray == nullptr)
			{
				this->m_VertexArray = key->getWindowData().m_GraphicsContext->createVertexArray(Type::DYNAMIC_DRAW, sizeof(Vertex) * 1000);
			}
			for (auto b : (*this->m_BatchManager.getBatches()).at(key))
			{
				b->m_Material->prepare(this->m_ViewProjectionMatrix);
				this->m_VertexArray->m_VertexBuffer->addSubData(&b->getMesh()->m_VerticesData[0], sizeof(float) * b->getMesh()->m_VerticesData.size(), 0);
				this->m_VertexArray->m_IndexBuffer->addSubData(&b->getMesh()->m_Indices[0], sizeof(unsigned int) * b->getMesh()->m_Indices.size(), 0);
				this->m_VertexArray->mapVertexAttributes(*b->getMesh()->calculateSize(), Vertex::getLayout());
				this->m_VertexArray->render();
			}
		}
		this->m_BatchManager.clear();
	}
}
