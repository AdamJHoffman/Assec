#include "acpch.h"

#include "util/PlatformUtils.h"

#include "graphics/WindowManager.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace assec::util {

	std::vector<FileDialogs::FileDialogData> FileDialogs::m_OpenFileDialogRequests;
	std::vector<FileDialogs::FileDialogData> FileDialogs::m_SaveFileDialogRequests;
	void FileDialogs::OpenFile(const FileDialogData& data)
	{
		m_OpenFileDialogRequests.push_back(data);
	}

	void FileDialogs::SaveFile(const FileDialogData& data)
	{
		m_SaveFileDialogRequests.push_back(data);
	}

	void FileDialogs::processDialogRequests()
	{
		for (auto& data : m_OpenFileDialogRequests)
		{
			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)graphics::WindowManager::getWindows()[0]->getWindowData().nativeWindow);
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = data.m_Filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				data.m_FileFoundCallback(ofn.lpstrFile);
			}
		}
		m_OpenFileDialogRequests.clear();
		for (auto& data : m_SaveFileDialogRequests)
		{
			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)graphics::WindowManager::getWindows()[0]->getWindowData().nativeWindow);
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = data.m_Filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
			ofn.lpstrDefExt = strchr(data.m_Filter, '\0') + 1;
			if (GetSaveFileNameA(&ofn) == TRUE)
			{
				data.m_FileFoundCallback(ofn.lpstrFile);
			}
		}
		m_SaveFileDialogRequests.clear();
	}

}
