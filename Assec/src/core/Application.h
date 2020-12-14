#pragma once
#include "event/EventQueue.h"

#include "layers/LayerStack.h"

#include "scene/Scene.h"

namespace assec
{
	/*
	The base application class containing the layerstack and eventqueue. 
	Every client application will enherit from this class.
	*/
	class Application
	{
	public:
		Application(CONST_REF(std::string) name = "Assec");
		virtual ~Application();

		void onEvent(ref<events::Event> event);
		void handleEvents();

		void init();
		void run();
		void close();

		INLINE CONST_REF(layersystem::LayerStack) getLayerStack() const 
		{ TIME_FUNCTION; return *this->m_LayerStack; }
		INLINE CONST_REF(events::EventQueue) getEventQueue() const 
		{ TIME_FUNCTION; return *this->m_EventQueue; }
		INLINE CONST_REF(scene::Scene) getActiveScene() const 
		{ TIME_FUNCTION; return *this->m_ActiveScene; }
		INLINE ref<scene::Scene> getRawActiveScene() const 
		{ TIME_FUNCTION; return this->m_ActiveScene; }

		INLINE REF(layersystem::LayerStack) getLayerStack() 
		{ TIME_FUNCTION; return *this->m_LayerStack; }
		INLINE REF(events::EventQueue) getEventQueue() 
		{ TIME_FUNCTION; return *this->m_EventQueue; }
		INLINE REF(scene::Scene) getActiveScene() 
		{ TIME_FUNCTION; return *this->m_ActiveScene; }
		INLINE ref<scene::Scene> getRawActiveScene() 
		{ TIME_FUNCTION; return this->m_ActiveScene; }

		
		INLINE void setActiveScene(CONST_REF(ref<scene::Scene>) activescene)
		{ TIME_FUNCTION; this->m_ActiveScene = activescene; }
		
	protected:
		virtual void onEvent0(ref<events::Event> event) {}
		virtual void init0() {};
		virtual void run0() {}

		std::string m_Name = "Assec";
		ref<layersystem::LayerStack> m_LayerStack = std::make_shared<layersystem::LayerStack>();
		ref<events::EventQueue> m_EventQueue = std::make_shared<events::EventQueue>();
		ref<scene::Scene> m_ActiveScene = std::make_shared<scene::Scene>();
	private:
		void cleanup() const;

		bool m_ShouldClose = false;
	};
} // namespace assec
