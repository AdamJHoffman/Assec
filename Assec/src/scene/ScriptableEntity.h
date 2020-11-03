#pragma once

#include "Entity.h"

#include "event/Event.h"

#include "util/Orm.h"

namespace assec::scene
{
	class ScriptableEntity : public util::BaseOrm
	{
	public:
		ScriptableEntity(const entt::entity& entity, Scene* scene) : m_Entity(entity, scene) {}
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& getComponent()
		{
			return m_Entity.getComponent<T>();
		}
		virtual void onCreate() {}
		virtual void onDestroy() {}
		virtual void onEvent(const events::Event& event) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};
}
