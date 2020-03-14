#pragma once
#include "Config.h"
#include <glad/glad.h>

#ifdef AC_DEBUG
#define GLClearError() while(glGetError() != GL_NO_ERROR)
#define GLCall(x)   GLClearError();\
                    x;\
                    {\
                    unsigned int error = glGetError();\
                    AC_CORE_ASSERT(!error, "Assertion failed: [OPENGL ERROR {0}] in function \"{1}\" on line {2} in file \"{3}\"", error, #x, __LINE__, __FILE__)\
                    }
#else
#define GLCall(x) x
#endif

namespace assec
{
	static unsigned int toOpenGLType(Type& type)
	{
		TIME_FUNCTION;
		switch (type)
		{
		case Type::FLOAT:
			return GL_FLOAT;
			break;
		case Type::UNSIGNED_INT:
			return GL_UNSIGNED_INT;
			break;
		case Type::VERTEX_SHADER:
			return GL_VERTEX_SHADER;
			break;
		case Type::FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;
			break;
		case Type::REPEAT:
			return GL_REPEAT;
			break;
		case Type::MIRRORED_REPEAT:
			return GL_MIRRORED_REPEAT;
			break;
		case Type::CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;
			break;
		case Type::CLAMP_TO_BORDER:
			return GL_CLAMP_TO_BORDER;
			break;
		case Type::LINEAR:
			return GL_LINEAR;
			break;
		case Type::NEAREST:
			return GL_NEAREST;
			break;
		case Type::NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;
			break;
		case Type::LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;
			break;
		case Type::NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;
			break;
		case Type::LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
			break;
		default:
			return NULL;
			break;
		}
	}
}
