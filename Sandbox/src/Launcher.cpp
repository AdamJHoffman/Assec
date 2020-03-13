#include "include/Assec.h"
namespace client
{
	auto layerStack = assec::layersystem::LayerStack();
	void onEvent(assec::events::Event& event)
	{
		TIME_FUNCTION;
		AC_CLIENT_TRACE(event.toString());
		layerStack.onEvent(event);
	}
	auto windowManager = std::make_shared<assec::graphics::WindowManager>(onEvent);
	void init()
	{
		assec::init();
		TIME_FUNCTION;
		unsigned int width = 1920, height = 1080;

		windowManager->addWindow(width, height, "Assec", nullptr, nullptr);
	}
	void update()
	{
		TIME_FUNCTION;
		const char* vertex = R"(
			#version 460
			
			layout (location = 0) in vec3 a_position;

			out vec4 p_color; 
		
			void main()
			{
				p_color = vec4(a_position, 1.0);
				gl_Position = vec4(a_position, 1.0);
			}	

		)";
		const char* fragment = R"(
			#version 460
			
			in vec4 p_color;
			out vec4 o_color;
		
			void main()
			{
				o_color = p_color + 0.5;
			}	

		)";
		float vertices[3 * 3] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
		};

		unsigned int indices[3] = {
			0, 1, 2
		};
		auto attrib1 = assec::graphics::VertexBuffer::VertexBufferAttribute(assec::DataType::FLOAT, 3, false);
		auto layout = assec::graphics::VertexBuffer::VertexBufferLayout();
		layout.m_Attributes.push_back(attrib1);

		assec::ref<assec::graphics::VertexArray> vertexArray = windowManager->getWindows()[0]->getWindowData().m_GraphicsContext->genVertexArray(vertices, sizeof(vertices), indices, sizeof(indices), 0x88E4, layout);
		assec::ref<assec::graphics::ShaderProgram> shader = windowManager->getWindows()[0]->getWindowData().m_GraphicsContext->genShaderProgram(vertex, fragment);
		while (!windowManager->empty())
		{
			TIME_FUNCTION;
			windowManager->prepare();

			shader->bind();

			vertexArray->render();

			windowManager->finish();
		}
	}
	void cleanup()
	{
		TIME_FUNCTION;
		assec::cleanup();
	}
}

int main()
{
	client::init();
	client::update();
	client::cleanup();
}
