#pragma once
#include "Config.h"
#include <glad/glad.h>

#ifdef AC_DEBUG
#define GLClearError() while(glGetError() != GL_NO_ERROR)
#define GLCall(x)   GLClearError();\
                    x;\
                    {\
                    uint32_t error = glGetError();\
					AC_CORE_ASSERT(!error, "Assertion failed: [OPENGL ERROR {0}] in function \"{1}\" on line {2} in file \"{3}\"", error, #x, __LINE__, __FILE__)\
					}
#else
#define GLCall(x) x
#endif

namespace assec
{
	static uint32_t toOpenGLType(Type& type)
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
		case Type::UNSIGNED_BYTE:
			return GL_UNSIGNED_BYTE;
			break;
		case Type::UNSIGNED_INT_24_8:
			return GL_UNSIGNED_INT_24_8;
			break;
		case Type::VERTEX_SHADER:
			return GL_VERTEX_SHADER;
			break;
		case Type::FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;
			break;
		case Type::STATIC_DRAW:
			return GL_STATIC_DRAW;
			break;
		case Type::DYNAMIC_DRAW:
			return GL_DYNAMIC_DRAW;
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
		case Type::RGB:
			return GL_RGB;
			break;
		case Type::RGBA:
			return GL_RGBA;
			break;
		case Type::RGBA8:
			return GL_RGBA8;
			break;
		case Type::DEPTH24_STENCIL8:
			return GL_DEPTH24_STENCIL8;
			break;
		case Type::DEPTH_STENCIL:
			return GL_DEPTH_STENCIL;
			break;
		default:
			return NULL;
			break;
		}
	}
}
