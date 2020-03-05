#include <iostream>
#include <include/Assec.h>
namespace client
{
	static assec::Logger CLIENT_LOGGER = assec::Logger("CLIENT");
	
	void init()
	{
		assec::init();
		assec::cleanup();
	}
}

int main()
{
	client::init();
}