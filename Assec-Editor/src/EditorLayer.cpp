#include "EditorLayer.h"

namespace assec::editor
{

	class CameraController : public scene::Entity
	{
	public:
		CameraController(entt::entity handle, scene::Scene* scene) : Entity::Entity(handle, scene) {}
		~CameraController() {}
		void onCreate()
		{
		}

		void onDestroy()
		{
		}

		void onEvent(const events::Event& event)
		{
			auto& transform = this->getComponent<scene::TransformComponent>().m_Transform;
			float speed = 0.5f;

			events::Dispatcher dispatcher = events::Dispatcher(event);
			dispatcher.dispatch<events::AppUpdateEvent>([&](const events::AppUpdateEvent& event)
				{
					TIME_FUNCTION;
					if (Input::isKeyDown(AC_KEY_A))
						transform[3][0] -= speed * event.m_Delta;
					if (Input::isKeyDown(AC_KEY_D))
						transform[3][0] += speed * event.m_Delta;
					if (Input::isKeyDown(AC_KEY_W))
						transform[3][1] += speed * event.m_Delta;
					if (Input::isKeyDown(AC_KEY_S))
						transform[3][1] -= speed * event.m_Delta;
					this->getComponent<scene::OrthoCameraComponent>().setViewMatrix(transform);
					return false;
				});
		}
	};

	EditorLayer::EditorLayer(const assec::Application& application, graphics::FrameBuffer* frameBuffer) : m_Application(&application), m_FrameBuffer(frameBuffer) {}
	EditorLayer::~EditorLayer() {}
	void EditorLayer::onEvent(const events::Event& event)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([&](const events::AppRenderEvent& event)
			{
				TIME_FUNCTION;
				if (this->m_ViewportSize.x != this->m_FrameBuffer->getFrameBufferProps().m_Width || this->m_ViewportSize.y != this->m_FrameBuffer->getFrameBufferProps().m_Height)
				{
					this->m_FrameBuffer->resize();
				}

				this->m_FrameBuffer->bind();
				graphics::WindowManager::clear();
				graphics::Renderer::beginScene(this->m_Application->m_ActiveScene->getActiveCamera());
				this->m_Application->m_ActiveScene->reg().view<scene::MeshComponent, scene::MaterialComponent, scene::TransformComponent>().each([&](auto entityID, auto& mesh, auto& material, auto& transform)
					{
						mesh.m_Mesh->setTransformationMatrix(transform);
						graphics::Renderer::submit(*graphics::WindowManager::getWindows()[0], graphics::Renderable2D(mesh, material));
					});
				graphics::Renderer::endScene();
				this->m_FrameBuffer->unbind();

				this->m_ViewportSize = { this->m_FrameBuffer->getFrameBufferProps().m_Width, this->m_FrameBuffer->getFrameBufferProps().m_Height };
				return false;
			});
	}
	void EditorLayer::onAttach()
	{
		// TEMP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//std::string fragment = assec::util::Loader::getLoader().loadFile("res/renderer2D/shaders/color/color.fragment");
		//std::string vertex = assec::util::Loader::getLoader().loadFile("res/renderer2D/shaders/color/color.vertex");
		std::string vertex = assec::util::Loader::loadFile("res/renderer2D/shaders/texture/texture.vertex");
		std::string fragment = assec::util::Loader::loadFile("res/renderer2D/shaders/texture/texture.fragment");

		assec::util::Loader::TextureData data = assec::util::Loader::loadImage("C:/OneDrive/OneDrive - Kantonsschule Wettingen/Personal/Workspace/Visual Studio/Assec/Assec-Editor/res/textures/rock_cliff/albedo.jpg");
		assec::graphics::Texture::TextureProps props = { data.m_Width, data.m_Height, assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true, Type::RGB, Type::RGB, Type::UNSIGNED_BYTE };
		assec::graphics::Texture& texture = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(data.m_Data, props);

		assec::graphics::ShaderProgram& shader = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createShaderProgram(vertex.c_str(), fragment.c_str());

		assec::graphics::Vertex v0;
		v0.position = glm::vec3(-0.5f, -0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v0.textureCoordinate = glm::vec2(0.0f, 0.0f);
		v0.transformationMatrix = glm::mat4(1.0f);

		assec::graphics::Vertex v1;
		v1.position = glm::vec3(0.5f, -0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v1.textureCoordinate = glm::vec2(1.0f, 0.0f);
		v1.transformationMatrix = glm::mat4(1.0f);

		assec::graphics::Vertex v2;
		v2.position = glm::vec3(0.5f, 0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v2.textureCoordinate = glm::vec2(1.0f, 1.0f);
		v2.transformationMatrix = glm::mat4(1.0f);

		assec::graphics::Vertex v3;
		v3.position = glm::vec3(-0.5f, 0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v3.textureCoordinate = glm::vec2(0.0f, 1.0f);
		v3.transformationMatrix = glm::mat4(1.0f);

		std::vector<assec::graphics::Vertex> vertices = { v0, v1, v2, v3 };
		std::vector<int> indices = { 0, 1, 2, 0, 2, 3 };

		assec::util::Loader::TextureData dataa = assec::util::Loader::loadImage("res/textures/rock_cliff/normal.jpg");
		assec::graphics::Texture::TextureProps propsa = { dataa.m_Width, dataa.m_Height, assec::Type::CLAMP_TO_EDGE, glm::vec4(1.0), assec::Type::LINEAR_MIPMAP_LINEAR, assec::Type::LINEAR, true, true, Type::RGB, Type::RGB, Type::UNSIGNED_BYTE };
		assec::graphics::Texture& texturea = graphics::WindowManager::getWindows()[0]->getWindowData().m_GraphicsContext->createTexture2D(dataa.m_Data, propsa);


		assec::graphics::Vertex v0a;
		v0a.position = glm::vec3(-0.5f, -0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v0a.textureCoordinate = glm::vec2(0.0f, 0.0f);
		v0a.transformationMatrix = glm::mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			2.0f, 0.0f, 0.0f, 1.0f
		);
		v0a.texID = 1;

		assec::graphics::Vertex v1a;
		v1a.position = glm::vec3(0.5f, -0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v1a.textureCoordinate = glm::vec2(1.0f, 0.0f);
		v1a.transformationMatrix = v0a.transformationMatrix;
		v1a.texID = 1;

		assec::graphics::Vertex v2a;
		v2a.position = glm::vec3(0.5f, 0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v2a.textureCoordinate = glm::vec2(1.0f, 1.0f);
		v2a.transformationMatrix = v0a.transformationMatrix;
		v2a.texID = 1;


		assec::graphics::Vertex v3a;
		v3a.position = glm::vec3(-0.5f, 0.5f, 0.0f);
		//v0.normal = glm::vec3(1.0f);
		v3a.textureCoordinate = glm::vec2(0.0f, 1.0f);
		v3a.transformationMatrix = v0a.transformationMatrix;
		v3a.texID = 1;


		std::vector<assec::graphics::Vertex> verticesa = { v0a, v1a, v2a, v3a };
		std::vector<int> indicesa = { 0, 1, 2, 0, 2, 3 };

		auto& squareTwo = this->m_Application->m_ActiveScene->createEntity("sqaure one");
		squareTwo.addComponent<scene::MeshComponent>(vertices, indices);
		squareTwo.addComponent<scene::MaterialComponent>(shader, texturea);

		for (int i = 0; i < 1; ++i)
		{
			auto& squareOne = this->m_Application->m_ActiveScene->createEntity("square two");
			squareOne.addComponent<scene::MeshComponent>(verticesa, indicesa);
			squareOne.addComponent<scene::MaterialComponent>(shader, texture);
		}

		// TEMP ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		scene::Entity camera = this->m_Application->m_ActiveScene->createEntity("camera");
		camera.addComponent<scene::NativeScriptComponent>().bind<CameraController>();
		this->m_Application->m_ActiveScene->setActiveCamera(camera.addComponent<scene::OrthoCameraComponent>(assec::scene::Camera(glm::ortho(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f))).m_Camera.m_Projection);
		camera.getComponent<scene::OrthoCameraComponent>().orthographic(2.0f, 1.0f, -1.0f);
		camera.getComponent<scene::OrthoCameraComponent>().setViewportSize(graphics::WindowManager::getWindows()[0]->getWindowData().m_Width, graphics::WindowManager::getWindows()[0]->getWindowData().m_Height);
		//this->m_Application->m_ActiveScene->setActiveCamera(this->m_EditorCamera->getViewProjectionMatrix());

	}
	void EditorLayer::onDetach()
	{

	}
} // assec::editor
