#include "include/Assec.h"
namespace client
{
	void init()
	{
		assec::Assec::getInstance();
		TIME_FUNCTION;
		assec::Assec::getInstance().AC_WINDOW_MANAGER->addWindow(1920, 1080, "Assec", nullptr, nullptr);
	}
	void update()
	{
		TIME_FUNCTION;

		// TEMP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		std::string vertex = assec::util::Loader::getLoader().loadFile("res/shaders/matrix_shader/matrix.vertex");
		std::string fragment = assec::util::Loader::getLoader().loadFile("res/shaders/matrix_shader/matrix.fragment");

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

		assec::ref<assec::graphics::Texture> texture = assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(data.m_Width, data.m_Height, data.m_Data, props);
		assec::ref<assec::graphics::VertexArray> vertexArray = assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createVertexArray(vertices, sizeof(vertices), indices, sizeof(indices), 0x88E4, layout);
		assec::ref<assec::graphics::ShaderProgram> shader = assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createShaderProgram(vertex.c_str(), fragment.c_str());
		assec::ref<assec::graphics::Camera> camera = std::make_shared<assec::graphics::OrthographicCamera>(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f);

		shader->loadMat4("u_viewProjection", camera->getViewProjectionMatrix());

		// TEMP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		while (!assec::Assec::getInstance().AC_WINDOW_MANAGER->empty())
		{
			TIME_FUNCTION;
			assec::Assec::getInstance().AC_WINDOW_MANAGER->prepare();

			shader->bind();
			assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->setActiveTexture(0);
			texture->bind();
			vertexArray->render();

			assec::Assec::getInstance().AC_WINDOW_MANAGER->finish();
			assec::Assec::getInstance().handleEvents();
		}
	}
	void cleanup()
	{
		TIME_FUNCTION;
	}
}

int main()
{
	client::init();
	client::update();
	client::cleanup();
}
