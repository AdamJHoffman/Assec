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