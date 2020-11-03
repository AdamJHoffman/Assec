#pragma once

#include <string>

namespace assec::util {

	class FileDialogs
	{
	public:
		struct FileDialogData
		{
			const char* m_Filter;
			std::function<void(const char*)> m_FileFoundCallback;
		};
		static void OpenFile(const FileDialogData&);
		static void SaveFile(const FileDialogData&);
		static void processDialogRequests();
	private:
		static std::vector<FileDialogData> m_OpenFileDialogRequests;
		static std::vector<FileDialogData> m_SaveFileDialogRequests;
	};

}
