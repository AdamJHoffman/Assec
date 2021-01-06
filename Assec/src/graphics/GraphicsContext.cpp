#include "acpch.h"

#include "GraphicsContext.h"

namespace assec::graphics
{
	Format determineFormat(CONST_REF(InternalFormat) internalFormat)
	{
		switch (internalFormat)
		{
		case InternalFormat::DEPTH_COMPONENT16:
		case InternalFormat::DEPTH_COMPONENT24:
		case InternalFormat::DEPTH_COMPONENT32:
		case InternalFormat::DEPTH_COMPONENT32F:
			return Format::DEPTH_COMPONENT;
			break;
		case InternalFormat::DEPTH24_STENCIL8:
		case InternalFormat::DEPTH32F_STENCIL8:
			return Format::DEPTH_STENCIL;
			break;
		case InternalFormat::R8:
		case InternalFormat::R8_SNORM:
		case InternalFormat::R16:
		case InternalFormat::R16_SNORM:
		case InternalFormat::R16F:
		case InternalFormat::R32F:
			return Format::RED;
			break;
		case InternalFormat::RG8:
		case InternalFormat::RG8_SNORM:
		case InternalFormat::RG16:
		case InternalFormat::RG16_SNORM:
		case InternalFormat::RG16F:
		case InternalFormat::RG32F:
			return Format::RG;
			break;
		case InternalFormat::R3_G3_B2:
		case InternalFormat::RGB4:
		case InternalFormat::RGB5:
		case InternalFormat::RGB8:
		case InternalFormat::RGB8_SNORM:
		case InternalFormat::SRGB8:
		case InternalFormat::RGB10:
		case InternalFormat::RGB12:
		case InternalFormat::RGB16:
		case InternalFormat::RGB16_SNORM:
		case InternalFormat::RGB16F:
		case InternalFormat::RGB32F:
		case InternalFormat::R11F_G11F_B10F:
		case InternalFormat::RGB9_E5:
			return Format::RGB;
			break;
		case InternalFormat::RGBA2:
		case InternalFormat::RGBA4:
		case InternalFormat::RGB5_A1:
		case InternalFormat::RGBA8:
		case InternalFormat::RGBA8_SNORM:
		case InternalFormat::SRGB8_ALPHA8:
		case InternalFormat::RGB10_A2:
		case InternalFormat::RGBA12:
		case InternalFormat::RGBA16:
		case InternalFormat::RGBA16_SNORM:
		case InternalFormat::RGBA16F:
		case InternalFormat::RGBA32F:
			return Format::RGBA;
			break;
		case InternalFormat::R8I:
		case InternalFormat::R16I:
		case InternalFormat::R32I:
		case InternalFormat::R8UI:
		case InternalFormat::R16UI:
		case InternalFormat::R32UI:
			return Format::RED_INTEGER;
			break;
		case InternalFormat::RG8I:
		case InternalFormat::RG8UI:
		case InternalFormat::RG16UI:
		case InternalFormat::RG16I:
		case InternalFormat::RG32I:
		case InternalFormat::RG32UI:
			return Format::RG_INTEGER;
			break;
		case InternalFormat::RGB8I:
		case InternalFormat::RGB8UI:
		case InternalFormat::RGB16I:
		case InternalFormat::RGB32I:
		case InternalFormat::RGB16UI:
		case InternalFormat::RGB32UI:
			return Format::RGB_INTEGER;
			break;
		case InternalFormat::RGBA8I:
		case InternalFormat::RGBA16I:
		case InternalFormat::RGBA32I:
		case InternalFormat::RGBA8UI:
		case InternalFormat::RGBA16UI:
		case InternalFormat::RGBA32UI:
			return Format::RGBA_INTEGER;
			break;
		default:
			AC_CORE_ASSERT(false, "cannot determine format");
			return Format::RED;
			break;
		}
	}

	DataType determineDataType(CONST_REF(InternalFormat) internalFormat)
	{
		switch (internalFormat)
		{
		case InternalFormat::DEPTH_COMPONENT16:
		case InternalFormat::DEPTH_COMPONENT24:
		case InternalFormat::DEPTH_COMPONENT32:
		case InternalFormat::R32UI:
		case InternalFormat::RG32UI:
		case InternalFormat::RGB32UI:
		case InternalFormat::RGBA32UI:
			return DataType::UNSIGNED_INT;
			break;
		case InternalFormat::DEPTH_COMPONENT32F:
		case InternalFormat::R16F:
		case InternalFormat::R32F:
		case InternalFormat::RG16F:
		case InternalFormat::RG32F:
		case InternalFormat::RGB16F:
		case InternalFormat::RGB32F:
		case InternalFormat::RGBA16F:
		case InternalFormat::RGBA32F:
			return DataType::FLOAT;
			break;
		case InternalFormat::DEPTH24_STENCIL8:
			return DataType::UNSIGNED_INT_24_8;
			break;
		case InternalFormat::DEPTH32F_STENCIL8:
			return DataType::FLOAT_32_UNSIGNED_INT_24_8_REV;
			break;
		case InternalFormat::R8:
		case InternalFormat::RG8:
		case InternalFormat::RGB4:
		case InternalFormat::RGB5:
		case InternalFormat::RGB8:
		case InternalFormat::SRGB8:
		case InternalFormat::RGBA2:
		case InternalFormat::RGBA4:
		case InternalFormat::RGBA8:
		case InternalFormat::SRGB8_ALPHA8:
		case InternalFormat::R8UI:
		case InternalFormat::RG8UI:
		case InternalFormat::RGB8UI:
		case InternalFormat::RGBA8UI:
			return DataType::UNSIGNED_BYTE;
			break;
		case InternalFormat::R8_SNORM:
		case InternalFormat::RG8_SNORM:
		case InternalFormat::RGB8_SNORM:
		case InternalFormat::RGBA8_SNORM:
		case InternalFormat::R8I:
		case InternalFormat::RG8I:
		case InternalFormat::RGB8I:
		case InternalFormat::RGBA8I:
			return DataType::BYTE;
			break;
		case InternalFormat::R3_G3_B2:
			return DataType::UNSIGNED_BYTE_3_3_2;
			break;
		case InternalFormat::R11F_G11F_B10F:
			return DataType::UNSIGNED_INT_10F_11F_11F_REV;
			break;
		case InternalFormat::RGB9_E5:
			return DataType::UNSIGNED_INT_5_9_9_9_REV;
			break;
		case InternalFormat::RGB5_A1:
			return DataType::UNSIGNED_SHORT_5_5_5_1;
			break;
		case InternalFormat::RGB10_A2:
			return DataType::UNSIGNED_INT_10_10_10_2;
			break;
		case InternalFormat::R16_SNORM:
		case InternalFormat::RG16_SNORM:
		case InternalFormat::RGB16_SNORM:
		case InternalFormat::RGBA16_SNORM:
		case InternalFormat::R16I:
		case InternalFormat::RG16I:
		case InternalFormat::RGB16I:
		case InternalFormat::RGBA16I:
			return DataType::SHORT;
			break;
		case InternalFormat::R16:
		case InternalFormat::RG16:
		case InternalFormat::RGB10:
		case InternalFormat::RGB12:
		case InternalFormat::RGB16:
		case InternalFormat::RGBA12:
		case InternalFormat::RGBA16:
		case InternalFormat::R16UI:
		case InternalFormat::RG16UI:
		case InternalFormat::RGB16UI:
		case InternalFormat::RGBA16UI:
			return DataType::UNSIGNED_SHORT;
			break;
		case InternalFormat::R32I:
		case InternalFormat::RG32I:
		case InternalFormat::RGB32I:
		case InternalFormat::RGBA32I:
			return DataType::INT;
			break;
		default:
			AC_CORE_ASSERT(false, "cannot determine datatype");
			return DataType::UNSIGNED_BYTE;
			break;
		}
	}

	size_t determineWidth(CONST_REF(InternalFormat) internalFormat)
	{
		switch (internalFormat)
		{
		case InternalFormat::DEPTH_COMPONENT16:
		case InternalFormat::DEPTH_COMPONENT24:
		case InternalFormat::DEPTH_COMPONENT32:
		case InternalFormat::DEPTH_COMPONENT32F:
		case InternalFormat::R8:
		case InternalFormat::R16:
		case InternalFormat::R16_SNORM:
		case InternalFormat::R8_SNORM:
		case InternalFormat::R8I:
		case InternalFormat::R16I:
		case InternalFormat::R8UI:
		case InternalFormat::R16UI:
		case InternalFormat::R16F:
		case InternalFormat::R32F:
		case InternalFormat::R32I:
		case InternalFormat::R32UI:
			return 1;
			break;
		case InternalFormat::DEPTH24_STENCIL8:
		case InternalFormat::DEPTH32F_STENCIL8:
		case InternalFormat::RG8:
		case InternalFormat::RG8_SNORM:
		case InternalFormat::RG16:
		case InternalFormat::RG16_SNORM:
		case InternalFormat::RG16F:
		case InternalFormat::RG32F:
		case InternalFormat::RG8I:
		case InternalFormat::RG8UI:
		case InternalFormat::RG16I:
		case InternalFormat::RG16UI:
		case InternalFormat::RG32I:
		case InternalFormat::RG32UI:
			return 2;
			break;
		case InternalFormat::R3_G3_B2:
		case InternalFormat::RGB4:
		case InternalFormat::RGB5:
		case InternalFormat::RGB8:
		case InternalFormat::RGB8_SNORM:
		case InternalFormat::SRGB8:
		case InternalFormat::RGB10:
		case InternalFormat::RGB12:
		case InternalFormat::RGB16:
		case InternalFormat::RGB16_SNORM:
		case InternalFormat::RGB16F:
		case InternalFormat::RGB32F:
		case InternalFormat::R11F_G11F_B10F:
		case InternalFormat::RGB8I:
		case InternalFormat::RGB8UI:
		case InternalFormat::RGB16I:
		case InternalFormat::RGB16UI:
		case InternalFormat::RGB32I:
		case InternalFormat::RGB32UI:
			return 3;
			break;
		case InternalFormat::RGBA2:
		case InternalFormat::RGBA4:
		case InternalFormat::RGB5_A1:
		case InternalFormat::RGBA8:
		case InternalFormat::RGBA8_SNORM:
		case InternalFormat::RGB10_A2:
		case InternalFormat::RGBA12:
		case InternalFormat::RGBA16:
		case InternalFormat::RGBA16_SNORM:
		case InternalFormat::SRGB8_ALPHA8:
		case InternalFormat::RGBA16F:
		case InternalFormat::RGBA32F:
		case InternalFormat::RGB9_E5:
		case InternalFormat::RGBA8I:
		case InternalFormat::RGBA8UI:
		case InternalFormat::RGBA16I:
		case InternalFormat::RGBA16UI:
		case InternalFormat::RGBA32I:
		case InternalFormat::RGBA32UI:
			return 4;
			break;
		default:
			AC_CORE_ASSERT(false, "cannot determine datatype");
			return 0;
			break;
		}
	}

	size_t determineTotalSize(CONST_REF(InternalFormat) internalFormat)
	{
		switch (internalFormat)
		{
		case InternalFormat::DEPTH_COMPONENT16:
		case InternalFormat::DEPTH_COMPONENT24:
		case InternalFormat::DEPTH_COMPONENT32:
		case InternalFormat::DEPTH_COMPONENT32F:
		case InternalFormat::R8:
		case InternalFormat::R16:
		case InternalFormat::R16_SNORM:
		case InternalFormat::R8_SNORM:
		case InternalFormat::R8I:
		case InternalFormat::R16I:
		case InternalFormat::R8UI:
		case InternalFormat::R16UI:
		case InternalFormat::R16F:
		case InternalFormat::R32F:
		case InternalFormat::R32I:
		case InternalFormat::R32UI:
		case InternalFormat::RG8:
		case InternalFormat::RG8_SNORM:
		case InternalFormat::RG16:
		case InternalFormat::RG16_SNORM:
		case InternalFormat::RG16F:
		case InternalFormat::RG32F:
		case InternalFormat::RG8I:
		case InternalFormat::RG8UI:
		case InternalFormat::RG16I:
		case InternalFormat::RG16UI:
		case InternalFormat::RG32I:
		case InternalFormat::RG32UI:
		case InternalFormat::RGB4:
		case InternalFormat::RGB5:
		case InternalFormat::RGB8:
		case InternalFormat::RGB8_SNORM:
		case InternalFormat::SRGB8:
		case InternalFormat::RGB10:
		case InternalFormat::RGB12:
		case InternalFormat::RGB16:
		case InternalFormat::RGB16_SNORM:
		case InternalFormat::RGB16F:
		case InternalFormat::RGB32F:
		case InternalFormat::RGB8I:
		case InternalFormat::RGB8UI:
		case InternalFormat::RGB16I:
		case InternalFormat::RGB16UI:
		case InternalFormat::RGB32I:
		case InternalFormat::RGB32UI:
		case InternalFormat::RGBA2:
		case InternalFormat::RGBA4:
		case InternalFormat::RGBA8:
		case InternalFormat::RGBA8_SNORM:
		case InternalFormat::RGBA12:
		case InternalFormat::RGBA16:
		case InternalFormat::RGBA16_SNORM:
		case InternalFormat::SRGB8_ALPHA8:
		case InternalFormat::RGBA16F:
		case InternalFormat::RGBA32F:
		case InternalFormat::RGBA8I:
		case InternalFormat::RGBA8UI:
		case InternalFormat::RGBA16I:
		case InternalFormat::RGBA16UI:
		case InternalFormat::RGBA32I:
		case InternalFormat::RGBA32UI:
			return determineWidth(internalFormat) * determineSize(determineDataType(internalFormat));
			break;
		case InternalFormat::DEPTH24_STENCIL8:
			return 4; // 4 bytes
			break;
		case InternalFormat::DEPTH32F_STENCIL8:
			return 5; // 5 bytes
			break;
		case InternalFormat::R3_G3_B2:
			return 1; // 1 bytes
			break;
		case InternalFormat::R11F_G11F_B10F:
			return 4; // 4 bytes
			break;
		case InternalFormat::RGB5_A1:
			return 2; // 2 bytes
			break;
		case InternalFormat::RGB10_A2:
			return 4; // 4 bytes
			break;
		case InternalFormat::RGB9_E5:
			return 4; // 4 bytes
			break;
		default:
			AC_CORE_ASSERT(false, "cannot determine datatype");
			return 0;
			break;
		}
	}

	size_t determineSize(CONST_REF(DataType) type)
	{
		TIME_FUNCTION;
		size_t result = 0;
		switch (type)
		{
		case DataType::BYTE:
			result = sizeof(char);
			break;
		case DataType::UNSIGNED_BYTE:
			result = sizeof(unsigned char);
			break;
		case DataType::SHORT:
			result = sizeof(short);
			break;
		case DataType::UNSIGNED_SHORT:
			result = sizeof(unsigned short);
			break;
		case DataType::INT:
			result = sizeof(int);
			break;
		case DataType::UNSIGNED_INT:
			result = sizeof(unsigned int);
			break;
		case DataType::FLOAT:
			result = sizeof(float);
			break;
		default:
			result = 0;
			break;
		}
		return result;
	}
}