#pragma once

namespace assec
{
	class Window
	{
	public:
		Window(unsigned int& width, unsigned int& height, const char* title, void* window) 
			: m_Width(width), m_Height(height), m_Title(title), m_Window(window) {}
		virtual ~Window() {}
		inline const void* getWindow() const { return this->m_Window; }
		virtual const void makeCurrent() const = 0;
		virtual const void swapBuffers() const = 0;
		virtual const void pollEvents() const = 0;
		unsigned int m_Width, m_Height;
		std::string m_Title;
	protected:
		virtual void* createWindow(unsigned int& width, unsigned int& height, const char* title, void* monitor, void* share) const = 0;
	private:
		void* m_Window;
	};
}
