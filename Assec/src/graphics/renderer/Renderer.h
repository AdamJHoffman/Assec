#pragma once
#include <glm/glm.hpp>

namespace assec::graphics
{
	class Renderer
	{
	public:
		virtual ~Renderer();
		void beginScene(glm::mat4& viewProjectionMatrix)
		{
			this->m_ViewProjectionMatrix = viewProjectionMatrix;
		}
		virtual void endScene() = 0;
	protected:
		Renderer();
		glm::mat4& m_ViewProjectionMatrix = glm::mat4(1.0f);
	};
}