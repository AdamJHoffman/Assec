#include "include/Assec.h"

#include "ExilusBaseLayer.h"

#include "scene/SceneSerializer.h"

namespace exilus
{
	class ExilusApplication : public assec::Application
	{
	public:
		ExilusApplication() {}
		~ExilusApplication() {}
		virtual void init() override
		{
			this->AC_LAYER_STACK->addLayer(std::make_shared<ExilusBaseLayer>(*this));
			assec::graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->setClearColor(glm::vec4(0.09803921568, 0.09803921568, 0.11764705882, 1.0f));
			assec::graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->enable(assec::Type::DEPTH_TEST);
			assec::graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->setDepthFunction(assec::Type::LESS);
			assec::scene::SceneSerializer(this->m_ActiveScene).deserialize("C:/OneDrive/OneDrive - Kantonsschule Wettingen/Personal/Workspace/Visual Studio/Assec/Sandbox/res/test.assec");
		}
	};
} // namespace assec::editor

int main()
{
	exilus::ExilusApplication().run();
}
