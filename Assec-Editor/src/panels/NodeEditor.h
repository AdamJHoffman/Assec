#pragma once

#include "include/Assec.h"

#include <imgui_node_editor.h>
#include <imgui.h>

#include "util/UUID.h"

namespace assec::editor
{
	class Node
	{
	public:
		Node(CONST_REF(uint64_t) uuid) : m_Uuid(uuid) {}

		virtual void renderImGUI() = 0;
	protected:
		uint64_t m_Uuid;
	};

	class SinNode : public Node
	{
	public:
		SinNode(CONST_REF(uint64_t) uuid) : Node(uuid) {}

		virtual void renderImGUI() override
		{
			
		}
	private:
		float m_Input = 0.f, m_Output = 0.0f;
	};

	class NodeEditor
	{
		struct LinkInfo
		{
			ax::NodeEditor::LinkId Id;
			ax::NodeEditor::PinId  InputId;
			ax::NodeEditor::PinId  OutputId;

			bool operator==(const LinkInfo& other)
			{
				return this->Id == other.Id;
			}
		};
	public:
		NodeEditor() = default;
		~NodeEditor() = default;
		void renderImGUI();
	private:
		SinNode m_Node = SinNode(uuid::generate_uuid_v4i());
		std::vector<LinkInfo> m_Links;               
	};
}
