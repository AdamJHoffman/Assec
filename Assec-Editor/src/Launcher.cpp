//#include "include/Assec.h"
//namespace client
//{
//	void init()
//	{
//		assec::Assec::getInstance();
//		TIME_FUNCTION;
//		assec::Assec::getInstance().AC_WINDOW_MANAGER->addWindow(1920, 1080, "Assec", nullptr, nullptr);
//	}
//	void update()
//	{
//		TIME_FUNCTION;
//
//		// TEMP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		//std::string fragment = assec::util::Loader::getLoader().loadFile("res/renderer2D/shaders/color/color.fragment");
//		//std::string vertex = assec::util::Loader::getLoader().loadFile("res/renderer2D/shaders/color/color.vertex");
//		std::string vertex = assec::util::Loader::getLoader().loadFile("res/renderer2D/shaders/texture/texture.vertex");
//		std::string fragment = assec::util::Loader::getLoader().loadFile("res/renderer2D/shaders/texture/texture.fragment");
//
//		assec::util::Loader::TextureData data = assec::util::Loader::getLoader().loadImage("res/textures/rock_cliff/albedo.jpg");
//		assec::graphics::Texture::TextureProps props = { assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true };
//		assec::ref<assec::graphics::Texture> texture = assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(data.m_Width, data.m_Height, data.m_Data, props);
//
//		assec::ref<assec::graphics::ShaderProgram> shader = assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createShaderProgram(vertex.c_str(), fragment.c_str());
//		assec::ref<assec::graphics::Camera> camera = std::make_shared<assec::graphics::OrthographicCamera>(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f);
//
//		assec::ref<assec::graphics::Renderer2D> renderer2D = std::make_shared<assec::graphics::Renderer2D>();
//
//		//assec::ref<assec::graphics::ColoredMaterial> material = std::make_shared<assec::graphics::ColoredMaterial>(shader, glm::vec4(0.001f, 0.9f, 1.0f, 1.0f));
//		assec::ref<assec::graphics::Material> material = std::make_shared<assec::graphics::Material>(shader, texture);
//
//
//		assec::graphics::Vertex v0;
//		v0.position = glm::vec3(-0.5f, -0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v0.textureCoordinate = glm::vec2(0.0f, 0.0f);
//		v0.transformationMatrix = glm::mat4(1.0f);
//
//		assec::graphics::Vertex v1;
//		v1.position = glm::vec3(0.5f, -0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v1.textureCoordinate = glm::vec2(1.0f, 0.0f);
//		v1.transformationMatrix = glm::mat4(1.0f);
//
//		assec::graphics::Vertex v2;
//		v2.position = glm::vec3(0.5f, 0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v2.textureCoordinate = glm::vec2(1.0f, 1.0f);
//		v2.transformationMatrix = glm::mat4(1.0f);
//
//		assec::graphics::Vertex v3;
//		v3.position = glm::vec3(-0.5f, 0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v3.textureCoordinate = glm::vec2(0.0f, 1.0f);
//		v3.transformationMatrix = glm::mat4(1.0f);
//
//		std::vector<assec::graphics::Vertex> vertices = { v0, v1, v2, v3 };
//		std::vector<int> indices = { 0, 1, 2, 0, 2, 3 };
//
//		assec::ref<assec::graphics::Mesh> mesh = std::make_shared<assec::graphics::Mesh>(vertices, indices);
//
//		assec::ref<assec::graphics::Renderable> renderable = std::make_shared<assec::graphics::Renderable2D>(mesh, material);
//
//
//		assec::util::Loader::TextureData dataa = assec::util::Loader::getLoader().loadImage("res/textures/rock_cliff/normal.jpg");
//		assec::graphics::Texture::TextureProps propsa = { assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true };
//		assec::ref<assec::graphics::Texture> texturea = assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(dataa.m_Width, dataa.m_Height, dataa.m_Data, propsa);
//
//		assec::ref<assec::graphics::Material> materiala = std::make_shared<assec::graphics::Material>(shader, texturea);
//
//
//		assec::graphics::Vertex v0a;
//		v0a.position = glm::vec3(-0.5f, -0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v0a.textureCoordinate = glm::vec2(0.0f, 0.0f);
//		v0a.transformationMatrix = glm::mat4(
//			1.0f, 0.0f, 0.0f, 0.0f,
//			0.0f, 1.0f, 0.0f, 0.0f,
//			0.0f, 0.0f, 1.0f, 0.0f,
//			2.0f, 0.0f, 0.0f, 1.0f
//		);
//		v0a.texID = 1;
//
//		assec::graphics::Vertex v1a;
//		v1a.position = glm::vec3(0.5f, -0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v1a.textureCoordinate = glm::vec2(1.0f, 0.0f);
//		v1a.transformationMatrix = v0a.transformationMatrix;
//		v1a.texID = 1;
//
//		assec::graphics::Vertex v2a;
//		v2a.position = glm::vec3(0.5f, 0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v2a.textureCoordinate = glm::vec2(1.0f, 1.0f);
//		v2a.transformationMatrix = v0a.transformationMatrix;
//		v2a.texID = 1;
//
//
//		assec::graphics::Vertex v3a;
//		v3a.position = glm::vec3(-0.5f, 0.5f, 0.0f);
//		//v0.normal = glm::vec3(1.0f);
//		v3a.textureCoordinate = glm::vec2(0.0f, 1.0f);
//		v3a.transformationMatrix = v0a.transformationMatrix;
//		v3a.texID = 1;
//
//
//		std::vector<assec::graphics::Vertex> verticesa = { v0a, v1a, v2a, v3a };
//		std::vector<int> indicesa = { 0, 1, 2, 0, 2, 3 };
//
//		assec::ref<assec::graphics::Mesh> mesha = std::make_shared<assec::graphics::Mesh>(verticesa, indicesa);
//
//		assec::ref<assec::graphics::Renderable> renderablea = std::make_shared<assec::graphics::Renderable2D>(mesha, materiala);
//
//		// TEMP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
//		while (!assec::Assec::getInstance().AC_WINDOW_MANAGER->empty())
//		{
//			TIME_FUNCTION;
//			assec::Assec::getInstance().AC_WINDOW_MANAGER->prepare();
//
//			renderer2D->beginScene(camera->getViewProjectionMatrix());
//
//			for (int i = 0; i < 1; i++)
//			{
//				renderer2D->submit(assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0], renderable);
//				renderer2D->submit(assec::Assec::getInstance().AC_WINDOW_MANAGER->getWindows()[0], renderablea);
//			}
//
//			renderer2D->endScene();
//
//			assec::Assec::getInstance().AC_WINDOW_MANAGER->finish();
//			assec::Assec::getInstance().handleEvents();
//		}
//	}
//	void cleanup()
//	{
//		TIME_FUNCTION;
//	}
//}
//
//int main()
//{
//	client::init();
//	client::update();
//	client::cleanup();
//}
