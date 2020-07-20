#include "acpch.h"
#include "Renderer.h"
#include "util/misc.h"
#include "core/OpenGLConfig.h"
#include "glm/gtc/type_ptr.hpp"

namespace assec::graphics
{
	Renderer2D::Renderer2D() {}
	Renderer2D::~Renderer2D() {}
	void Renderer2D::endScene()
	{
		for (auto key : util::Keys(this->m_Renderables))
		{
			key->makeCurrent();
			key->getWindowData().m_GraphicsContext->setActiveTexture(0);
			//if (this->m_VertexArray == nullptr)
			//{
			//	Type usage = Type::DYNAMIC_DRAW;
			//	this->m_VertexArray = key->getWindowData().m_GraphicsContext->createVertexArray(toOpenGLType(usage), 1000000);
			//}
			for (auto renderable : this->m_Renderables.at(key))
			{
				renderable->m_Material->prepare(this->m_ViewProjectionMatrix);

				Type usage = Type::DYNAMIC_DRAW;
				this->m_VertexArray = key->getWindowData().m_GraphicsContext->createVertexArray({ &renderable->m_Mesh->m_VerticesData[0], (const void*)&renderable->m_Mesh->m_Indices[0], sizeof(float) * renderable->m_Mesh->m_VerticesData.size(), sizeof(unsigned int) * renderable->m_Mesh->m_Indices.size(), toOpenGLType(usage), Vertex::getLayout() });
				//this->m_VertexArray->m_VertexBuffer->addData(&renderable->m_Mesh->m_VerticesData[0], sizeof(float) * renderable->m_Mesh->m_VerticesData.size(), toOpenGLType(usage));
				//this->m_VertexArray->m_IndexBuffer->addData(&renderable->m_Mesh->m_Indices[0], sizeof(unsigned int) * renderable->m_Mesh->m_Indices.size(), toOpenGLType(usage));
			}
			this->m_VertexArray->render();
			this->m_VertexArray->cleanup();

		}
		this->m_Renderables.clear();
	}
}
