#include "acpch.h"

#include "NodeEditor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>

#include "util/UUID.h"

namespace assec::editor
{
    void ImGuiEx_BeginColumn()
    {
        ImGui::BeginGroup();
    }

    void ImGuiEx_NextColumn()
    {
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginGroup();
    }

    void ImGuiEx_EndColumn()
    {
        ImGui::EndGroup();
    }
	void NodeEditor::renderImGUI()
	{
		ImGui::Begin("Node Editor");
        ax::NodeEditor::Begin("Node Editor Internal", ImGui::GetContentRegionAvail());
        int uniqueId = 1;

        //
        // 1) Commit known data to editor
        //

        // Submit Node A
        ax::NodeEditor::NodeId nodeA_Id = uniqueId++;
        ax::NodeEditor::PinId  nodeA_InputPinId = uniqueId++;
        ax::NodeEditor::PinId  nodeA_OutputPinId = uniqueId++;

        ax::NodeEditor::BeginNode(nodeA_Id);
        ImGui::Text("Node A");
        ax::NodeEditor::BeginPin(nodeA_InputPinId, ax::NodeEditor::PinKind::Input);
        ImGui::Text("-> In");
        ax::NodeEditor::EndPin();
        ImGui::SameLine();
        ax::NodeEditor::BeginPin(nodeA_OutputPinId, ax::NodeEditor::PinKind::Output);
        ImGui::Text("Out ->");
        ax::NodeEditor::EndPin();
        ax::NodeEditor::EndNode();

        // Submit Node B
        ax::NodeEditor::NodeId nodeB_Id = uniqueId++;
        ax::NodeEditor::PinId  nodeB_InputPinId1 = uniqueId++;
        ax::NodeEditor::PinId  nodeB_InputPinId2 = uniqueId++;
        ax::NodeEditor::PinId  nodeB_OutputPinId = uniqueId++;

        ax::NodeEditor::BeginNode(nodeB_Id);
        ImGui::Text("Node B");
        ImGuiEx_BeginColumn();
        ax::NodeEditor::BeginPin(nodeB_InputPinId1, ax::NodeEditor::PinKind::Input);
        ImGui::Text("-> In1");
        ax::NodeEditor::EndPin();
        ax::NodeEditor::BeginPin(nodeB_InputPinId2, ax::NodeEditor::PinKind::Input);
        ImGui::Text("-> In2");
        ax::NodeEditor::EndPin();
        ImGuiEx_NextColumn();
        ax::NodeEditor::BeginPin(nodeB_OutputPinId, ax::NodeEditor::PinKind::Output);
        ImGui::Text("Out ->");
        ax::NodeEditor::EndPin();
        ImGuiEx_EndColumn();
        ax::NodeEditor::EndNode();

        // Submit Links
        for (auto& linkInfo : this->m_Links)
            ax::NodeEditor::Link(linkInfo.Id, linkInfo.InputId, linkInfo.OutputId);

        if (ax::NodeEditor::BeginCreate())
        {
            ax::NodeEditor::PinId inputPinId, outputPinId;
            if (ax::NodeEditor::QueryNewLink(&inputPinId, &outputPinId))
            {
                // QueryNewLink returns true if editor want to create new link between pins.
                //
                // Link can be created only for two valid pins, it is up to you to
                // validate if connection make sense. Editor is happy to make any.
                //
                // Link always goes from input to output. User may choose to drag
                // link from output pin or input pin. This determine which pin ids
                // are valid and which are not:
                //   * input valid, output invalid - user started to drag new ling from input pin
                //   * input invalid, output valid - user started to drag new ling from output pin
                //   * input valid, output valid   - user dragged link over other pin, can be validated

                if (inputPinId && outputPinId) // both are valid, let's accept link
                {
                    // ed::AcceptNewItem() return true when user release mouse button.
                    if (ax::NodeEditor::AcceptNewItem())
                    {
                        // Since we accepted new link, lets add one to our list of links.
                        this->m_Links.push_back({ ax::NodeEditor::LinkId(uuid::generate_uuid_v4i()), inputPinId, outputPinId });

                        // Draw new link.
                        ax::NodeEditor::Link(this->m_Links.back().Id, this->m_Links.back().InputId, this->m_Links.back().OutputId);
                    }

                    // You may choose to reject connection between these nodes
                    // by calling ed::RejectNewItem(). This will allow editor to give
                    // visual feedback by changing link thickness and color.
                }
            }
        }
        ax::NodeEditor::EndCreate(); // Wraps up object creation action handling.

         // Handle deletion action
        if (ax::NodeEditor::BeginDelete())
        {
            // There may be many links marked for deletion, let's loop over them.
            ax::NodeEditor::LinkId deletedLinkId;
            while (ax::NodeEditor::QueryDeletedLink(&deletedLinkId))
            {
                // If you agree that link can be deleted, accept deletion.
                if (ax::NodeEditor::AcceptDeletedItem())
                {
                    // Then remove link from your data.
                    for (auto& link : this->m_Links)
                    {
                        if (link.Id == deletedLinkId)
                        {
                            this->m_Links.erase(std::remove(this->m_Links.begin(), this->m_Links.end(), link), this->m_Links.end());
                            break;
                        }
                    }
                }

                // You may reject link deletion by calling:
                // ed::RejectDeletedItem();
            }
        }
        ax::NodeEditor::EndDelete(); // Wrap up deletion action

        ax::NodeEditor::End();
		ImGui::End();
	}
}