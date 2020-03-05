#pragma once

#define AC_RENDRING_API OpenGL
#define AC_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace assec
{
	void init();
	void cleanup();
}