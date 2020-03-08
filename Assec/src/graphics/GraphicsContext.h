#pragma once
#include "acpch.h"

namespace assec::graphics
{
	class GraphicsContext
	{
	public:
		GraphicsContext() {}
		virtual ~GraphicsContext() {}
		virtual const void init() const = 0;
	};
}