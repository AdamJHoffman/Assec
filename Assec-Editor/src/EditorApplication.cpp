#include "include/Assec.h"
#include "EditorLayer.h"
#include "EditorGuiLayer.h"

namespace assec::editor
{
	class EditorApplication : public assec::Application
	{
	public:
		EditorApplication() {}
		~EditorApplication() {}
		virtual void init() override
		{
			this->AC_LAYER_STACK->addLayer(std::make_shared<EditorLayer>(*this));
			this->AC_LAYER_STACK->addOverlay(std::make_shared<EditorGuiLayer>(*this));
		}
	};
} // namespace assec::editor

int main()
{
	assec::editor::EditorApplication().run();
}