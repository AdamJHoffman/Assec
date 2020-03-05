#pragma once
#include <graphics/Window.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "core/Config.h"

namespace assec
{
	class OpenGLWindow : public Window
	{
	public:
	 OpenGLWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share);
		virtual ~OpenGLWindow();
		virtual const void makeCurrent() const override;
		virtual const void swapBuffers() const override;
		virtual const void pollEvents() const override;
	protected:
		virtual void* createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const override;
	};
}