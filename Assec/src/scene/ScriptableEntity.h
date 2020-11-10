#pragma once

#include <any>

#include "Entity.h"

#include "event/Event.h"

#include "util/Orm.h"

namespace assec::scene
{
	struct NativeScriptComponent;
	class ScriptableEntity : public util::BaseOrm
	{
	public:
		ScriptableEntity() = default;
		ScriptableEntity(const entt::entity& entity, Scene* scene);
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& getComponent()
		{
			return m_Entity.getComponent<T>();
		}

		virtual void bind(NativeScriptComponent&) = 0;
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onEvent(const events::Event& event);
		static std::map<std::string, ScriptableEntity*> s_Scripts;
	private:
		Entity m_Entity;
	};
}
