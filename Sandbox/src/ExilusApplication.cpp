#include "include/Assec.h"

#include "ExilusBaseLayer.h"

#include "scene/SceneSerializer.h"

namespace exilus
{
	class ExilusApplication : public assec::Application
	{
	public:
		ExilusApplication() : assec::Application("Exilus") {}
		~ExilusApplication() {}
		virtual void init0() override
		{
			this->m_LayerStack->addLayer(std::make_shared<ExilusBaseLayer>(*this));
			assec::graphics::WindowManager::getWindows()[0]->getWindowData().graphicsContext->setClearColor(glm::vec4(0.09803921568, 0.09803921568, 0.11764705882, 1.0f));
			assec::graphics::WindowManager::getWindows()[0]->getWindowData().graphicsContext->enable(assec::Type::DEPTH_TEST);
			assec::graphics::WindowManager::getWindows()[0]->getWindowData().graphicsContext->setDepthFunction(assec::Type::LESS);
			assec::scene::SceneSerializer(this->m_ActiveScene).deserialize("res/test.assec");
			this->m_ActiveScene->reg().view<assec::scene::NativeScriptComponent>().each([&](auto entity, auto& nsc)
				{
					if (!nsc.m_Instance)
					{
						nsc.m_Instance = nsc.InstantiateScript(entity, &*this->m_ActiveScene);
					}
				});
		}
	};
} // namespace assec::editor

int main()
{
	exilus::ExilusApplication().run();
}
