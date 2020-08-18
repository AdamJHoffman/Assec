#include "include/Assec.h"
#include "EditorLayer.h"
#include "EditorGuiLayer.h"

namespace assec::editor
{
	class EditorApplication : public assec::Application
	{
	public:
		EditorApplication()
		{}
		~EditorApplication() {}
		virtual void init() override
		{
			this->m_FrameBuffer = this->AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createFrameBuffer({ {}, 1920, 1080, 1, false, });
			this->m_FrameBuffer->addTextureAttachment(Type::COLOR_ATTACHMENT_0, Type::RGBA8, Type::RGBA, Type::UNSIGNED_BYTE);
			this->m_FrameBuffer->addTextureAttachment(Type::DEPTH_STENCIL_ATTACHMENT, Type::DEPTH24_STENCIL8, Type::DEPTH_STENCIL, Type::UNSIGNED_INT_24_8);
			this->m_FrameBuffer->validate();
			this->AC_LAYER_STACK->addLayer(std::make_shared<EditorLayer>(*this, this->m_FrameBuffer.get()));
			this->AC_LAYER_STACK->addOverlay(std::make_shared<EditorGuiLayer>(*this, this->m_FrameBuffer.get()));
		}
	private:
		ref<graphics::FrameBuffer> m_FrameBuffer = nullptr;
	};
} // namespace assec::editor

int main()
{
	assec::editor::EditorApplication().run();
}