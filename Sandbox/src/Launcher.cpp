#include "include/Assec.h"

namespace client
{
	auto windowManager = std::make_shared<assec::graphics::WindowManager>();
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