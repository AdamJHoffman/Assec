#include "acpch.h"

#include "ExilusBaseLayer.h"

namespace exilus
{

	class CameraController : public assec::scene::ScriptableEntity
	{
	public:
		CameraController() = default;
		CameraController(const entt::entity& entity, assec::scene::Scene* scene) : assec::scene::ScriptableEntity(entity, scene) {}
		~CameraController() {}

		void bind(assec::scene::NativeScriptComponent& script) override
		{
			script.bind<std::remove_reference<decltype(*this)>::type>();
		}

		void onCreate() override
		{
			this->addField("speed", new assec::util::OrmField<float>(assec::util::Access::PUBLIC, 0.3f));
		}

		void onEvent(const assec::events::Event& event) override
		{
			float speed = this->getField<float>("speed").getValue();
			assec::util::Dispatcher dispatcher = assec::events::Dispatcher(event);
			dispatcher.dispatch<assec::events::AppUpdateEvent>([&](const assec::events::AppUpdateEvent& event)
				{
					TIME_FUNCTION;
					if (assec::Input::isKeyDown(assec::KEY::KEY_A))
						this->getComponent<assec::scene::TransformComponent>().translation.x -= speed * event.m_Delta;
					if (assec::Input::isKeyDown(assec::KEY::KEY_D))
						this->getComponent<assec::scene::TransformComponent>().translation.x += speed * event.m_Delta;
					if (assec::Input::isKeyDown(assec::KEY::KEY_W))
						this->getComponent<assec::scene::TransformComponent>().translation.y += speed * event.m_Delta;
					if (assec::Input::isKeyDown(assec::KEY::KEY_S))
						this->getComponent<assec::scene::TransformComponent>().translation.y -= speed * event.m_Delta;
					return false;
				});
		}
	};

	ExilusBaseLayer::ExilusBaseLayer(const assec::Application& application) : m_Application(&application) {}
	ExilusBaseLayer::~ExilusBaseLayer() {}
	void ExilusBaseLayer::onEvent(const assec::events::Event& event)
	{
		assec::events::Dispatcher dispatcher = assec::events::Dispatcher(event);
		dispatcher.dispatch<assec::events::AppRenderEvent>([&](const assec::events::AppRenderEvent& event)
			{
				TIME_FUNCTION;
				assec::graphics::WindowManager::clear();
				assec::graphics::Renderer::beginScene(this->m_Application->m_ActiveScene->getActiveCamera());
				this->m_Application->m_ActiveScene->reg().view<assec::scene::MeshComponent, assec::scene::MaterialComponent, assec::scene::TransformComponent>().each([&](auto entityID, auto& mesh, auto& material, auto& transform)
					{
						mesh.m_Mesh->setTransformationMatrix(transform.toMatrix());
						assec::graphics::Renderer::submit(*assec::graphics::WindowManager::getWindows()[0], assec::graphics::Renderable2D(mesh, material));
					});
				assec::graphics::Renderer::endScene();
				return false;
			});
	}
	void ExilusBaseLayer::onAttach()
	{
		assec::scene::ScriptableEntity::s_Scripts.emplace(typeid(CameraController).name(), new CameraController());

		assec::graphics::WindowManager::getMainWindow().setIcon({ "res/textures/icon.png" });
	}
	void ExilusBaseLayer::onDetach()
	{

	}
} // exilus
