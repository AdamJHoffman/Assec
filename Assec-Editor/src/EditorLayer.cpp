#include "EditorLayer.h"

#include "input/Input.h"

#include "util/Loader.h"
#include "util/Dispatcher.h"

namespace assec::editor
{

	class CameraController : public scene::ScriptableEntity
	{
	public:
		CameraController() = default;
		CameraController(const entt::entity& entity, scene::Scene* scene) : scene::ScriptableEntity(entity, scene) {}
		~CameraController() {}

		void bind(scene::NativeScriptComponent& script) override
		{
			script.bind<std::remove_reference<decltype(*this)>::type>();
		}

		void onCreate() override
		{
			this->addField("speed", new assec::util::OrmField<float>(assec::util::Access::PUBLIC, 0.3f));
		}

		void onEvent(const events::Event& event) override
		{
			float speed = this->getField<float>("speed").getValue();
			util::Dispatcher dispatcher = util::Dispatcher(event);
			dispatcher.dispatch<events::AppUpdateEvent>([&](const events::AppUpdateEvent& event)
				{
					TIME_FUNCTION;
					if (input::Input::isKeyDown(KEY::KEY_A) || input::Input::getConnectedJoysticks()[0]->getGamepadState().getXButton())
						this->getComponent<scene::TransformComponent>().translation.x -= speed * event.getDeltaTime();
					if (input::Input::isKeyDown(KEY::KEY_D) || input::Input::getConnectedJoysticks()[0]->getGamepadState().getBButton())
						this->getComponent<scene::TransformComponent>().translation.x += speed * event.getDeltaTime();
					if (input::Input::isKeyDown(KEY::KEY_W) || input::Input::getConnectedJoysticks()[0]->getGamepadState().getYButton())
						this->getComponent<scene::TransformComponent>().translation.y += speed * event.getDeltaTime();
					if (input::Input::isKeyDown(KEY::KEY_S) || input::Input::getConnectedJoysticks()[0]->getGamepadState().getAButton())
						this->getComponent<scene::TransformComponent>().translation.y -= speed * event.getDeltaTime();
					return false;
				});
		}
	};

	EditorLayer::EditorLayer(EditorApplication& application) : m_Application(&application) {}
	EditorLayer::~EditorLayer() {}
	void EditorLayer::onEvent(const events::Event& event)
	{
		util::Dispatcher dispatcher = util::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([&](const events::AppRenderEvent& event)
			{
				TIME_FUNCTION;
				if (this->m_ViewportSize.x != this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Width || this->m_ViewportSize.y != this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Height)
				{
					this->m_ViewportSize = { this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Width, this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Height };
					this->m_Application->m_Camera.setViewportSize(this->m_ViewportSize.x, this->m_ViewportSize.y);
					this->m_Application->getActiveScene().onViewportResized(this->m_ViewportSize.x, this->m_ViewportSize.y);
					this->m_Application->m_FrameBuffer->resize();
				}

				this->m_Application->m_FrameBuffer->bind();
				graphics::WindowManager::clear();
				this->m_Application->m_FrameBuffer->getTextureAttachment(Type::COLOR_ATTACHMENT1).clear();
				graphics::Renderer::beginScene(this->m_Application->m_CurrentState == ApplicationState::EDITOR ? this->m_Application->m_Camera.getViewProjection() : this->m_Application->getActiveScene().getActiveCamera());
				this->m_Application->getActiveScene().reg().view<scene::MeshComponent, scene::MaterialComponent, scene::TransformComponent>().each([&](auto entityID, auto& mesh, auto& material, auto& transform)
					{
						mesh.m_Mesh->setTransformationMatrix(transform.toMatrix());
						graphics::Renderer::submit(*graphics::WindowManager::getWindows()[0], graphics::Renderable2D(mesh, material));
					});
				graphics::Renderer::endScene();
				this->m_Application->m_FrameBuffer->unbind();

				return false;
			});
	}
	void EditorLayer::onAttach()
	{
		scene::ScriptableEntity::s_Scripts.emplace(typeid(CameraController).name(), new CameraController());
		
		//graphics::WindowManager::getMainWindow().setIcon({ "res/textures/icon.png" });
	}
	void EditorLayer::onDetach()
	{

	}
} // assec::editor
