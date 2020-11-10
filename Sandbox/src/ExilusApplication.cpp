#include "include/Assec.h"
//#include "EditorLayer.h"
//#include "EditorGuiLayer.h"

namespace assec::editor
{
	class ExilusApplication : public assec::Application
	{
	public:
		ExilusApplication() {}
		~ExilusApplication() {}
		virtual void init() override
		{
			this->m_FrameBuffer = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createFrameBuffer({ {}, 1920, 1080, 1, false, });
			this->m_FrameBuffer->addTextureAttachment(Type::COLOR_ATTACHMENT0, Type::RGBA8, Type::RGBA, Type::UNSIGNED_BYTE);
			this->m_FrameBuffer->addTextureAttachment(Type::DEPTH_STENCIL_ATTACHMENT, Type::DEPTH24_STENCIL8, Type::DEPTH_STENCIL, Type::UNSIGNED_INT_24_8);
			this->m_FrameBuffer->validate();
			//this->AC_LAYER_STACK->addLayer(std::make_shared<EditorLayer>(*this, this->m_FrameBuffer));
			//this->AC_LAYER_STACK->addOverlay(std::make_shared<EditorGuiLayer>(*this, this->m_FrameBuffer));
			graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->setClearColor(glm::vec4(0.09803921568, 0.09803921568, 0.11764705882, 1.0f));
			graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->enable(Type::DEPTH_TEST);
			graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->setDepthFunction(Type::LESS);
		}
	private:
		ref<graphics::FrameBuffer> m_FrameBuffer = nullptr;
	};
} // namespace assec::editor

int main()
{
	assec::editor::ExilusApplication().run();
}
