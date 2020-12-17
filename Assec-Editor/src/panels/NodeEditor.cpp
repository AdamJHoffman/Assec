#include "NodeEditor.h"

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <imnodes.h>

#include "util/UUID.h"
#include "input/Input.h"

namespace assec::editor
{

    void AbstractInputPin::onLink(REF(AbstractOutputPin) other)
    {
        this->valuePointer = &other.value;
    }

    Node* Graph::findNode(CONST_REF(uint32_t) uuid)
    {
        for (auto& node : this->nodes)
        {
            if (node->UUID == uuid)
                return &*node;
        }
        return nullptr;
    }
    AbstractPin* Graph::findPin(CONST_REF(uint32_t) uuid)
    {
        for (auto& node : this->nodes)
        {
            for (auto& pin : node->getInputPins())
            {
                if (pin->UUID == uuid)
                    return &*pin;
            }
            for (auto& pin : node->getOutputPins())
            {
                if (pin->UUID == uuid)
                    return &*pin;
            }
        }
        return nullptr;
    }
    Link* Graph::findLink(CONST_REF(uint32_t) uuid)
    {
        for (auto& link : this->links)
        {
            if (link.UUID == uuid)
                return &link;
        }
        return nullptr;
    }
    Node* Graph::findNode(CONST_REF(AbstractPin) pin)
    {
        for (auto& node : this->nodes)
        {
            for (auto& p : node->getInputPins())
            {
                if (*p == pin)
                    return &*node;
            }
            for (auto& p : node->getOutputPins())
            {
                if (*p == pin)
                    return &*node;
            }
        }
        return nullptr;
    }
    Link* Graph::findLink(CONST_REF(AbstractPin) pin)
    {
        for (auto& link : this->links)
        {
            if (link.input->UUID == pin.UUID || link.output->UUID == pin.UUID)
                return &link;
        }
        return nullptr;
    }
    bool Graph::isPinLinked(CONST_REF(AbstractPin) pin) const
    {
        for (auto& link : this->links)
        {
            if (link.input->UUID == pin.UUID || link.output->UUID == pin.UUID)
                return true;
        }
        return false;
    }
    bool Graph::isInputPin(CONST_REF(AbstractPin) pin)
    {
        auto& node = *this->findNode(pin);
        for (auto& p : node.getInputPins())
        {
            if (*p == pin)
                return true;
        }
        return false;
    }
    bool Graph::isOutputPin(CONST_REF(AbstractPin) pin)
    {
        return !this->isInputPin(pin);
    }
    void NodeEditor::begin0()
    {
        this->handleLinks();
        this->getSelectedNodes();
        this->getSelectedLinks();
        imnodes::BeginNodeEditor();
    }
    void NodeEditor::end0()
    {
        this->submitLinks();
        imnodes::EndNodeEditor();
        this->removeNodes();
        this->removeLinks();
    }
    void NodeEditor::render()
    {
        for (auto& node : this->m_Graph.nodes)
        {
            node->update();
        }
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));
        if (ImGui::BeginPopupContextWindow(0, 1, true))
        {
            ref<Node>node;
            if (ImGui::MenuItem("Create Empty Node"))
            {
                node = makeRef<Node>();
            }
            if (ImGui::MenuItem("Create Time Node"))
            {
                node = makeRef<TimeNode>();
            }
            if (ImGui::MenuItem("Create Sine Node"))
            {
                node = makeRef<SineNode>();
            }
            if (ImGui::MenuItem("Create Add Node"))
            {
                node = makeRef<AddNode>();
            }
            if (ImGui::MenuItem("Create Multiply Node"))
            {
                node = makeRef<MultiplyNode>();
            }
            if (ImGui::MenuItem("Create Graph Node"))
            {
                Graph graph = Graph();
                for (auto& node : this->m_SelectedNodes)
                {
                    for (auto& n : this->m_Graph.nodes)
                    {
                        if (n->UUID == node->UUID)
                        {
                            graph.nodes.push_back(n);
                        }
                    }
                    this->m_Graph.nodes.erase(std::remove_if(this->m_Graph.nodes.begin(), this->m_Graph.nodes.end(),
                        [&](CONST_REF(ref<Node>) n)
                        {
                            return n->UUID == node->UUID;
                        }), this->m_Graph.nodes.end());
                }
                for (auto& link : this->m_SelectedLink)
                {
                    graph.links.push_back(*link);
                }
                for (auto& node : graph.nodes)
                {
                    for (auto& pin : node->getOutputPins())
                    {
                        if (!graph.isPinLinked(*pin))
                        {
                            graph.rootNode = &*node;
                        }
                    }
                }
                node = makeRef<GraphNode>(graph);
            }
            if (ImGui::BeginMenu("Split Nodes", true))
            {
                if (ImGui::MenuItem("Vector2"))
                {
                    node = makeRef<Vector2SplitNode>();
                }
                if (ImGui::MenuItem("Vector3"))
                {
                    node = makeRef<Vector3SplitNode>();
                }
                if (ImGui::MenuItem("Vector4"))
                {
                    node = makeRef<Vector4SplitNode>();
                }
                if (ImGui::MenuItem("Mat4"))
                {
                    node = makeRef<Mat4SplitNode>();
                }
                ImGui::EndMenu();
            }
            if (node)
            {
                imnodes::SetNodeScreenSpacePos(node->UUID, ImGui::GetMousePos());
                this->m_Graph.nodes.push_back(node);
            }
            ImGui::EndPopup();
        }
        ImGui::PopStyleVar();

        for (auto& node : this->m_Graph.nodes)
        {
            node->renderImGUI(*node);
        }
    }

    void NodeEditor::submitLinks()
    {
        for (auto& link : this->m_Graph.links)
        {
            imnodes::Link(link.UUID, link.input->UUID, link.output->UUID);
        }
    }

    void NodeEditor::handleLinks()
    {
        int first, second;
        if (imnodes::IsLinkCreated(&first, &second))
        {
            AbstractInputPin* input = nullptr;
            AbstractOutputPin* output = nullptr;
            if (this->m_Graph.isInputPin(*this->m_Graph.findPin(static_cast<uint32_t>(first))))
            {
                input = dynamic_cast<AbstractInputPin*>(this->m_Graph.findPin(static_cast<uint32_t>(first)));
                output = dynamic_cast<AbstractOutputPin*>(this->m_Graph.findPin(static_cast<uint32_t>(second)));
            }
            else
            {
                input = dynamic_cast<AbstractInputPin*>(this->m_Graph.findPin(static_cast<uint32_t>(second)));
                output = dynamic_cast<AbstractOutputPin*>(this->m_Graph.findPin(static_cast<uint32_t>(first)));
            }
            if (this->m_Graph.isPinLinked(*input) || (input->pintype != output->pintype))
                return;
            this->m_Graph.links.push_back(Link{ uuid::generateUUID(), input, output });
            input->onLink(*output);
            output->onLink(*input);
        }
    }

    void NodeEditor::removeNodes()
    {
       
        if (input::Input::isKeyDown(KEY::KEY_BACKSPACE))
        {
            for (auto& node : this->m_SelectedNodes)
            {

                if (node)
                {
                    this->m_Graph.nodes.erase(std::remove_if(this->m_Graph.nodes.begin(), this->m_Graph.nodes.end(),
                        [&](CONST_REF(ref<Node>) n)
                        {
                            return n->UUID == node->UUID;
                        }), this->m_Graph.nodes.end());
                }

            }
        }
            
       
    }

    void NodeEditor::removeLinks()
    {

        if (input::Input::isKeyDown(KEY::KEY_BACKSPACE))
        {
            for (auto& link : this->m_SelectedLink)
            {

                if (link)
                {
                    link->input->onUnlink();
                    link->output->onUnlink(),
                        this->m_Graph.links.erase(std::remove_if(this->m_Graph.links.begin(), this->m_Graph.links.end(),
                            [&](CONST_REF(Link) l)
                            {
                                return l.UUID == link->UUID;
                            }), this->m_Graph.links.end());
                }

            }
        }
    }

    void NodeEditor::getSelectedNodes()
    {
        this->m_SelectedNodes.clear();
        const int numOfSelectedNodes = imnodes::NumSelectedNodes();
        if (numOfSelectedNodes > 0)
        {
            std::vector<int> selectedNodes;
            selectedNodes.resize(numOfSelectedNodes);
            imnodes::GetSelectedNodes(selectedNodes.data());
            for (auto& i : selectedNodes)
            {
                this->m_SelectedNodes.push_back(this->m_Graph.findNode(i));
            }
        }
    }

    void NodeEditor::getSelectedLinks()
    {
        this->m_SelectedLink.clear();
        const int numOfSelectedLinks = imnodes::NumSelectedLinks();
        if (numOfSelectedLinks > 0)
        {
            std::vector<int> selectedLinks;
            selectedLinks.resize(numOfSelectedLinks);
            imnodes::GetSelectedLinks(selectedLinks.data());
            for (auto& i : selectedLinks)
            {
                this->m_SelectedLink.push_back(this->m_Graph.findLink(i));
            }
        }
    }
}