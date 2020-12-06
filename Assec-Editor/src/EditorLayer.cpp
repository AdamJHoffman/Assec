#include "EditorLayer.h"

#include "core/Input.h"

#include "util/Loader.h"

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
			events::Dispatcher dispatcher = events::Dispatcher(event);
			dispatcher.dispatch<events::AppUpdateEvent>([&](const events::AppUpdateEvent& event)
				{
					TIME_FUNCTION;
					if (Input::isKeyDown(KEY::KEY_A))
						this->getComponent<scene::TransformComponent>().translation.x -= speed * event.m_Delta;
					if (Input::isKeyDown(KEY::KEY_D))
						this->getComponent<scene::TransformComponent>().translation.x += speed * event.m_Delta;
					if (Input::isKeyDown(KEY::KEY_W))
						this->getComponent<scene::TransformComponent>().translation.y += speed * event.m_Delta;
					if (Input::isKeyDown(KEY::KEY_S))
						this->getComponent<scene::TransformComponent>().translation.y -= speed * event.m_Delta;
					return false;
				});
		}
	};

	EditorLayer::EditorLayer(EditorApplication& application) : m_Application(&application) {}
	EditorLayer::~EditorLayer() {}
	void EditorLayer::onEvent(const events::Event& event)
	{
		events::Dispatcher dispatcher = events::Dispatcher(event);
		dispatcher.dispatch<events::AppRenderEvent>([&](const events::AppRenderEvent& event)
			{
				TIME_FUNCTION;
				if (this->m_ViewportSize.x != this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Width || this->m_ViewportSize.y != this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Height)
				{
					this->m_Application->m_FrameBuffer->resize();
				}

				this->m_Application->m_FrameBuffer->bind();
				graphics::WindowManager::clear();
				graphics::Renderer::beginScene(this->m_Application->m_ActiveScene->getActiveCamera());
				this->m_Application->m_ActiveScene->reg().view<scene::MeshComponent, scene::MaterialComponent, scene::TransformComponent>().each([&](auto entityID, auto& mesh, auto& material, auto& transform)
					{
						mesh.m_Mesh->setTransformationMatrix(transform.toMatrix());
						graphics::Renderer::submit(*graphics::WindowManager::getWindows()[0], graphics::Renderable2D(mesh, material));
					});
				graphics::Renderer::endScene();
				this->m_Application->m_FrameBuffer->unbind();

				this->m_ViewportSize = { this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Width, this->m_Application->m_FrameBuffer->getFrameBufferProps().m_Height };
				return false;
			});
	}
	void EditorLayer::onAttach()
	{
		scene::ScriptableEntity::s_Scripts.emplace(typeid(CameraController).name(), new CameraController());
		
		graphics::WindowManager::getMainWindow().setIcon({ "res/textures/icon.png" });
	}
	void EditorLayer::onDetach()
	{

	}
} // assec::editor
