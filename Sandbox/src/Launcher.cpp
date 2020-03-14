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
		std::string vertex = assec::util::Loader::getLoader().loadFile("res/shaders/texture_shader/texture.vertex");
		std::string fragment = assec::util::Loader::getLoader().loadFile("res/shaders/texture_shader/texture.fragment");

		float vertices[4 * 3 + 4 * 2] = {
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.5f,  0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f,

				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f
		};

		unsigned int indices[6] = {
			0, 1, 2,
			0, 2, 3
		};
		auto attrib1 = assec::graphics::VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 3, false);
		auto attrib2 = assec::graphics::VertexBuffer::VertexBufferAttribute(assec::Type::FLOAT, 2, false);
		auto layout = assec::graphics::VertexBuffer::VertexBufferLayout();
		layout.m_Attributes.push_back(attrib1);
		layout.m_Attributes.push_back(attrib2);

		assec::util::Loader::TextureData data = assec::util::Loader::getLoader().loadImage("res/textures/rock_cliff/normal.jpg");

		assec::graphics::Texture::TextureProps props = { assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true };

		assec::ref<assec::graphics::Texture> texture = windowManager->getWindows()[0]->getWindowData().m_GraphicsContext->genTexture2D(data.m_Width, data.m_Height, data.m_Data, props);
		assec::ref<assec::graphics::VertexArray> vertexArray = windowManager->getWindows()[0]->getWindowData().m_GraphicsContext->genVertexArray(vertices, sizeof(vertices), indices, sizeof(indices), 0x88E4, layout);
		assec::ref<assec::graphics::ShaderProgram> shader = windowManager->getWindows()[0]->getWindowData().m_GraphicsContext->genShaderProgram(vertex.c_str(), fragment.c_str());
		while (!windowManager->empty())
		{
			TIME_FUNCTION;
			windowManager->prepare();

			shader->bind();
			windowManager->getWindows()[0]->getWindowData().m_GraphicsContext->setActiveTexture(0);
			texture->bind();

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
