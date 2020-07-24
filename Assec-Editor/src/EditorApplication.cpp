#include "include/Assec.h"
#include "core/Application.h"

namespace assec::editor
{
	class EditorApplication : public assec::Application
	{
	public:
		EditorApplication() {}
		~EditorApplication() {}
	};
} // namespace assec::editor

int main()
{
	assec::editor::EditorApplication().run();
}