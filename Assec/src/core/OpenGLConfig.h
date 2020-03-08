#pragma once
#include "Config.h"
#include "glad/glad.h"

#ifdef AC_DEBUG
#define GLClearError() while(glGetError() != GL_NO_ERROR)
#define GLCall(x)   GLClearError();\
                    x;\
                    unsigned int error = glGetError();\
                    AC_CORE_ASSERT(!error, "Assertion failed: [OPENGL ERROR {0}] in function \"{1}\" on line {2} in file \"{3}\"", error, #x, __LINE__, __FILE__)
#else
#define GLCall(x) x
#endif
