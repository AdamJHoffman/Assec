#include "include/Assec.h"

namespace client
{
	auto layerStack = assec::layersystem::LayerStack();
	void onEvent(assec::events::Event& event)
	{
		TIME_FUNCTION;
		AC_CLIENT_TRACE(event.toString());
		layerStack.onEvent(event);
	}
	auto windowManager = std::make_shared<assec::graphics::WindowManager>(onEvent);
	void init()
	{
		assec::init();
		TIME_FUNCTION;
		unsigned int width = 1920, height = 1080;

		windowManager->addWindow(width, height, "name", nullptr, nullptr);
	}
	void update()
	{
		TIME_FUNCTION;
		while (!windowManager->empty())
		{
			TIME_FUNCTION;
			windowManager->prepare();
			windowManager->finish();
		}
	}
	void cleanup()
	{
		TIME_FUNCTION;
		assec::cleanup();
	}
}

int main()
{
	client::init();
	client::update();
	client::cleanup();
}
