#include "include/Assec.h"

namespace client
{
	void init()
	{
		ASSEC_CLIENT_TRACE("client launched");
		assec::init();
		auto windowManager = std::make_shared<assec::graphics::WindowManager>();
		unsigned int width = 1920, height = 1080;

		windowManager->m_Windows.push_back(assec::createWindow(width, height, "name", nullptr, nullptr, [windowManager](assec::events::Event& event)
			{
				windowManager->onEvent(event, assec::onEvent);
			}));

		while (windowManager->m_Windows[0]->getWindowData().m_Open)
		{
			for (auto window : windowManager->m_Windows)
			{
				window->makeCurrent();
				window->clear();
				window->swapBuffers();
				window->pollEvents();
			}
		}
		assec::cleanup();
	}
}

int main()
{
	client::init();
}