#include "include/Assec.h"

namespace client
{
	void init()
	{
		ASSEC_CLIENT_TRACE("client launched");
		assec::init();
		auto windowManager = std::make_shared<assec::graphics::WindowManager>();
		unsigned int width = 1920, height = 1080;

		windowManager->addWindow(width, height, "name", nullptr, nullptr);

		while (!windowManager->empty())
		{
			windowManager->prepare();
			windowManager->finish();
		}
		assec::cleanup();
	}
}

int main()
{
	client::init();
}