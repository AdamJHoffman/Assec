#pragma once

#include "include/Assec.h"

#include <imnodes.h>
#include <imgui.h>

#include <glm/glm.hpp>

#include <stack>
#include <any>

#include "util/UUID.h"

namespace assec::editor
{
	template<typename T>
	class Dispatcher
	{
		template<typename F> using TransactionFn = std::function<void(const F&)>;
	public:
		Dispatcher(const T& object) : m_Object(*const_cast<T*>(&object)) {}

		template<typename T> void dispatch(TransactionFn<T> function)
		{
			TIME_FUNCTION;
			if (typeid(m_Object) == typeid(T) || dynamic_cast<T*>(&m_Object) != nullptr)
			{
				function(*(T*)&m_Object);
			}
		}
	private:
		T& m_Object;
	};

	struct AbstractPin
	{
		AbstractPin(CONST_REF(uint32_t) uuid, CONST_REF(std::string) name, CONST_REF(std::string) pintype)
			: UUID(uuid), name(name), pintype(pintype) {}
		AbstractPin() = default;
		virtual ~AbstractPin() = default;

		uint32_t UUID = uuid::generateUUID();
		std::string name = "Unnamed Pin", pintype = "invalid";

		virtual void renderImGUI()
		{ 
			ImGui::TextUnformatted(this->name.c_str()); 
		};

		bool operator==(const AbstractPin & other)
		{
			return this->UUID == other.UUID;
		}
	};

	struct AbstractOutputPin;

	struct AbstractInputPin : AbstractPin
	{
		AbstractInputPin(CONST_REF(uint32_t) uuid, CONST_REF(std::string) name, CONST_REF(std::string) pintype)
			: AbstractPin(uuid, name, pintype) {}
		AbstractInputPin()
		{
			this->name = "input";
		}
		virtual ~AbstractInputPin() = default;

		void onLink(REF(AbstractOutputPin) other);
		void onUnlink() { this->valuePointer = &this->m_Value; }

		std::any* valuePointer = nullptr;
		std::any m_Value;		
	};

	struct AbstractOutputPin : AbstractPin
	{
		AbstractOutputPin(CONST_REF(uint32_t) uuid, CONST_REF(std::string) name, CONST_REF(std::string) pintype)
			: AbstractPin(uuid, name, pintype) {}
		AbstractOutputPin()
		{
			this->name = "ouput";
		}
		virtual ~AbstractOutputPin() = default;

		void onLink(REF(AbstractInputPin))
		{

		}
		void onUnlink()
		{

		}

		std::any value;
	};

	template<typename T>
	struct InputPin : public AbstractInputPin
	{
		InputPin(CONST_REF(std::string) name)
			: AbstractInputPin(uuid::generateUUID(), name, typeid(T).name()) 
		{
			this->m_Value = static_cast<std::any>(T());
			this->valuePointer = &this->m_Value;
		}
		InputPin()
		{
			this->pintype = typeid(T).name();
			this->m_Value = static_cast<std::any>(T());
			this->valuePointer = &this->m_Value;
		}
		~InputPin() = default;
		void renderImGUI() override
		{
			ImGui::TextUnformatted(this->name.c_str());
			Dispatcher<InputPin<T>> dispatcher = Dispatcher(*this);
			dispatcher.dispatch<InputPin<float>>([](CONST_REF(InputPin<float>) input)
				{
					ImGui::SameLine();
					if (input.valuePointer == &input.m_Value)
						ImGui::DragFloat(std::string("##" + input.name).c_str(), std::any_cast<float>(input.valuePointer));
					else
						ImGui::TextUnformatted(std::to_string(*std::any_cast<float>(input.valuePointer)).c_str());
				});
			dispatcher.dispatch<InputPin<glm::vec2>>([](CONST_REF(InputPin<glm::vec2>) input)
				{
					ImGui::SameLine();
					if (input.valuePointer == &input.m_Value)
						ImGui::DragFloat2(std::string("##" + input.name).c_str(), glm::value_ptr(*std::any_cast<glm::vec2>(input.valuePointer)));
				});
			dispatcher.dispatch<InputPin<glm::vec3>>([](CONST_REF(InputPin<glm::vec3>) input)
				{
					ImGui::SameLine();
					if (input.valuePointer == &input.m_Value)
						ImGui::DragFloat3(std::string("##" + input.name).c_str(), glm::value_ptr(*std::any_cast<glm::vec3>(input.valuePointer)));
				});
			dispatcher.dispatch<InputPin<glm::vec4>>([](CONST_REF(InputPin<glm::vec4>) input)
				{
					ImGui::SameLine();
					if (input.valuePointer == &input.m_Value)
						ImGui::DragFloat4(std::string("##" + input.name).c_str(), glm::value_ptr(*std::any_cast<glm::vec4>(input.valuePointer)));
				});
		};
	};

	template<typename T>
	struct OutputPin : public AbstractOutputPin
	{
		OutputPin(CONST_REF(std::string) name)
			: AbstractOutputPin(uuid::generateUUID(), name, typeid(T).name())
		{
			this->value = T();
		}
		OutputPin()
		{
			this->pintype = typeid(T).name();
			this->value = T();
		}
		~OutputPin() = default;
	};

	struct Link
	{
		Link() = default;
		~Link() = default;

		uint32_t UUID = uuid::generateUUID();
		AbstractInputPin* input = nullptr;
		AbstractOutputPin* output = nullptr;

		bool operator==(const Link& other)
		{
			return this->UUID == other.UUID;
		}
	};

	struct Node
	{
		Node() = default;
		virtual ~Node() = default;

		REF(std::vector<ref<AbstractInputPin>>) getInputPins() { return this->inputPins; }
		REF(std::vector<ref<AbstractOutputPin>>) getOutputPins() { return this->outputPins; }

		void submitInputPin(CONST_REF(ref<AbstractInputPin>) input) { this->inputPins.push_back(input); }
		void submitOutputPin(CONST_REF(ref<AbstractOutputPin>) output) { this; this->outputPins.push_back(output); }

		virtual void update() {}

		uint32_t UUID = uuid::generateUUID();
		std::string name = "Unnamed Node";

		glm::vec4 titleBarColor = glm::vec4(11.0f, 109.0f, 191.0f, 255.0f);
		glm::vec4 titleBarHovoredColor = glm::vec4(66.0f, 150.0f, 250.0f, 255.0f);
		glm::vec4 titleBarSelectedColor = glm::vec4(81.0f, 148.0f, 204.0f, 255.0f);
		float width = 100.0f;
		std::function<void(CONST_REF(Node))> renderImGUI = [](CONST_REF(Node) node)
		{
			imnodes::PushColorStyle(
				imnodes::ColorStyle_TitleBar, IM_COL32(node.titleBarColor.r, node.titleBarColor.g,
					node.titleBarColor.b, node.titleBarColor.a));
			imnodes::PushColorStyle(
				imnodes::ColorStyle_TitleBarHovered, IM_COL32(node.titleBarColor.r, node.titleBarColor.g,
					node.titleBarColor.b, node.titleBarColor.a));
			imnodes::PushColorStyle(
				imnodes::ColorStyle_TitleBarSelected, IM_COL32(node.titleBarSelectedColor.r, node.titleBarSelectedColor.g,
					node.titleBarSelectedColor.b, node.titleBarSelectedColor.a));
			imnodes::BeginNode(node.UUID);
			imnodes::BeginNodeTitleBar();
			ImGui::TextUnformatted(node.name.c_str());
			imnodes::EndNodeTitleBar();
			for (auto& pin : node.inputPins)
			{
				imnodes::BeginInputAttribute(pin->UUID);
				ImGui::PushItemWidth(node.width - ImGui::CalcTextSize(pin->name.c_str()).x);
				pin->renderImGUI();
				ImGui::PopItemWidth();
				imnodes::EndInputAttribute();
			}
			for (auto& pin : node.outputPins)
			{
				imnodes::BeginOutputAttribute(pin->UUID);
				ImGui::Indent(node.width - ImGui::CalcTextSize(pin->name.c_str()).x);
				ImGui::PushItemWidth(ImGui::CalcTextSize(pin->name.c_str()).x);
				pin->renderImGUI();
				ImGui::PopItemWidth();
				imnodes::EndOutputAttribute();
			}
			imnodes::EndNode();
			imnodes::PopColorStyle();
			imnodes::PopColorStyle();
		};

		bool operator==(const Node & other)
		{
			return this->UUID == other.UUID;
		}

	protected:
		std::vector<ref<AbstractInputPin>> inputPins;
		std::vector<ref<AbstractOutputPin>> outputPins;
	};

	struct Graph
	{
		Graph() = default;
		~Graph() = default;

		Node* findNode(CONST_REF(uint32_t) uuid);
		AbstractPin* findPin(CONST_REF(uint32_t) uuid);
		Link* findLink(CONST_REF(uint32_t) uuid);
		Node* findNode(CONST_REF(AbstractPin) pin);
		Link* findLink(CONST_REF(AbstractPin) pin);
		bool isPinLinked(CONST_REF(AbstractPin) pin) const;
		bool isInputPin(CONST_REF(AbstractPin) pin);
		bool isOutputPin(CONST_REF(AbstractPin) pin);

		std::vector<Link> links;
		std::vector<ref<Node>> nodes;
		Node* rootNode = nullptr;
	};

	struct ValueNode : public Node
	{
		ValueNode() : Node()
		{
			this->name = "Value Node";
			this->titleBarColor = glm::vec4(50, 168, 82, 255);
			this->titleBarHovoredColor = glm::vec4(75, 156, 97, 255);
			this->titleBarSelectedColor = glm::vec4(104, 156, 118, 255);
		}
		~ValueNode() = default;
	};

	struct DisplayNode : public Node
	{
		DisplayNode() : Node()
		{
			this->name = "Display Node";
			this->titleBarColor = glm::vec4(50, 168, 82, 255);
			this->titleBarHovoredColor = glm::vec4(75, 156, 97, 255);
			this->titleBarSelectedColor = glm::vec4(104, 156, 118, 255);
		}
		~DisplayNode() = default;
	};

	struct TimeNode : public ValueNode
	{
		TimeNode() : ValueNode()
		{
			ref<AbstractOutputPin> pin = makeRef<OutputPin<float>>("Time");
			this->submitOutputPin(pin);
			this->name = "Time Node";
			this->titleBarColor = glm::vec4(204, 108, 29, 255);
			this->titleBarHovoredColor = glm::vec4(204, 141, 90, 255);
			this->titleBarSelectedColor = glm::vec4(199, 162, 131, 255);
		}
		~TimeNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(graphics::WindowManager::m_WindowContext->getCurrentTime());
		}
	};

	struct SineNode : public Node
	{
		SineNode() : Node()
		{
			ref<AbstractInputPin> inpin = makeRef<InputPin<float>>();
			this->submitInputPin(inpin);
			ref<AbstractOutputPin> outpin = makeRef<OutputPin<float>>();
			this->submitOutputPin(outpin);
			this->name = "Sine Node";
			this->titleBarColor = glm::vec4(240.0f, 74.0f, 94.0f, 255.0f);
			this->titleBarHovoredColor = glm::vec4(230.0f, 78.0f, 96.0f, 255.0f);
			this->titleBarSelectedColor = glm::vec4(235.0f, 101.0f, 117.0f, 255.0f);
		}
		~SineNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(std::sin(std::any_cast<float>(*this->inputPins[0]->valuePointer)));
		}
	};

	struct AddNode : public Node
	{
		AddNode()
		{
			this->submitInputPin(makeRef<InputPin<float>>());
			this->submitInputPin(makeRef<InputPin<float>>());
			this->submitOutputPin(makeRef<OutputPin<float>>());
			this->name = "Add Node";
			this->titleBarColor = glm::vec4(219, 46, 162, 255);
			this->titleBarHovoredColor = glm::vec4(217, 98, 177, 255);
			this->titleBarSelectedColor = glm::vec4(217, 150, 194, 255);
		}
		~AddNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(std::any_cast<float>(*this->inputPins[0]->valuePointer) + std::any_cast<float>(*this->inputPins[1]->valuePointer));
		}
	};

	struct MultiplyNode : public Node
	{
		MultiplyNode()
		{
			this->submitInputPin(makeRef<InputPin<float>>());
			this->submitInputPin(makeRef<InputPin<float>>());
			this->submitOutputPin(makeRef<OutputPin<float>>());
			this->name = "Multiply Node";
			this->titleBarColor = glm::vec4(219, 46, 162, 255);
			this->titleBarHovoredColor = glm::vec4(217, 98, 177, 255);
			this->titleBarSelectedColor = glm::vec4(217, 150, 194, 255);
		}
		~MultiplyNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(std::any_cast<float>(*this->inputPins[0]->valuePointer) * std::any_cast<float>(*this->inputPins[1]->valuePointer));
		}
	};

	template<typename T>
	struct SplitNode : public Node
	{
		SplitNode()
		{
			this->submitInputPin(makeRef<InputPin<T>>());
			this->name = "Split Node";
			this->titleBarColor = glm::vec4(219, 46, 162, 255);
			this->titleBarHovoredColor = glm::vec4(217, 98, 177, 255);
			this->titleBarSelectedColor = glm::vec4(217, 150, 194, 255);
		}
		~SplitNode() = default;
		virtual void update() override = 0;
	};

	struct Vector2SplitNode : public SplitNode<glm::vec2>
	{
		Vector2SplitNode()
		{
			this->submitOutputPin(makeRef<OutputPin<float>>("x"));
			this->submitOutputPin(makeRef<OutputPin<float>>("y"));
			this->name = "Vector2 Split Node";
		}
		~Vector2SplitNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(std::any_cast<glm::vec2>(this->inputPins[0]->valuePointer)->x);
			this->outputPins[1]->value = static_cast<std::any>(std::any_cast<glm::vec2>(this->inputPins[0]->valuePointer)->y);
		}
	};

	struct Vector3SplitNode : public SplitNode<glm::vec3>
	{
		Vector3SplitNode()
		{
			this->submitOutputPin(makeRef<OutputPin<float>>("x"));
			this->submitOutputPin(makeRef<OutputPin<float>>("y"));
			this->submitOutputPin(makeRef<OutputPin<float>>("z"));
			this->name = "Vector3 Split Node";
		}
		~Vector3SplitNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(std::any_cast<glm::vec3>(this->inputPins[0]->valuePointer)->x);
			this->outputPins[1]->value = static_cast<std::any>(std::any_cast<glm::vec3>(this->inputPins[0]->valuePointer)->y);
			this->outputPins[2]->value = static_cast<std::any>(std::any_cast<glm::vec3>(this->inputPins[0]->valuePointer)->z);
		}
	};

	struct Vector4SplitNode : public SplitNode<glm::vec4>
	{
		Vector4SplitNode()
		{
			this->submitOutputPin(makeRef<OutputPin<float>>("x"));
			this->submitOutputPin(makeRef<OutputPin<float>>("y"));
			this->submitOutputPin(makeRef<OutputPin<float>>("z"));
			this->submitOutputPin(makeRef<OutputPin<float>>("w"));
			this->name = "Vector4 Split Node";
		}
		~Vector4SplitNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>(std::any_cast<glm::vec4>(this->inputPins[0]->valuePointer)->x);
			this->outputPins[1]->value = static_cast<std::any>(std::any_cast<glm::vec4>(this->inputPins[0]->valuePointer)->y);
			this->outputPins[2]->value = static_cast<std::any>(std::any_cast<glm::vec4>(this->inputPins[0]->valuePointer)->z);
			this->outputPins[3]->value = static_cast<std::any>(std::any_cast<glm::vec4>(this->inputPins[0]->valuePointer)->w);
		}
	};

	struct Mat4SplitNode : public SplitNode<glm::mat4>
	{
		Mat4SplitNode()
		{
			this->submitOutputPin(makeRef<OutputPin<glm::vec4>>("row 1"));
			this->submitOutputPin(makeRef<OutputPin<glm::vec4>>("row 2"));
			this->submitOutputPin(makeRef<OutputPin<glm::vec4>>("row 3"));
			this->submitOutputPin(makeRef<OutputPin<glm::vec4>>("row 4"));
			this->name = "Mat4 Split Node";
		}
		~Mat4SplitNode() = default;
		virtual void update() override
		{
			this->outputPins[0]->value = static_cast<std::any>((*std::any_cast<glm::mat4>(this->inputPins[0]->valuePointer))[0]);
			this->outputPins[1]->value = static_cast<std::any>((*std::any_cast<glm::mat4>(this->inputPins[0]->valuePointer))[1]);
			this->outputPins[2]->value = static_cast<std::any>((*std::any_cast<glm::mat4>(this->inputPins[0]->valuePointer))[2]);
			this->outputPins[3]->value = static_cast<std::any>((*std::any_cast<glm::mat4>(this->inputPins[0]->valuePointer))[3]);
		}
	};

	struct GraphNode : public Node
	{
		GraphNode(CONST_REF(Graph) graph) : m_Graph(graph)
		{
			this->name = "Graph Node";
			for (auto& pin : graph.rootNode->getOutputPins())
			{
				this->submitOutputPin(pin);
			}
			for (auto& node : graph.nodes)
			{
				for (auto& pin : node->getInputPins())
				{
					if (!graph.isPinLinked(*pin))
					{
						this->submitInputPin(pin);
					}
				}
			}
			this->titleBarColor = glm::vec4(50, 168, 82, 255);
			this->titleBarHovoredColor = glm::vec4(75, 156, 97, 255);
			this->titleBarSelectedColor = glm::vec4(104, 156, 118, 255);
		}
		~GraphNode() = default;
		virtual void update() override
		{
			for (int i = 0; i < this->outputPins.size(); ++i)
			{
				this->outputPins[i]->value = this->m_Graph.rootNode->getOutputPins()[i]->value;
			}
			for (auto& node : this->m_Graph.nodes)
			{
				int i = 0;
				for (auto& pin : node->getInputPins())
				{
					if (!this->m_Graph.isPinLinked(*pin))
					{
						pin->valuePointer = this->inputPins[i]->valuePointer;
						++i;
					}
				}
			}
			for (auto& node : this->m_Graph.nodes)
			{
				node->update();
			}
		}
	private:
		Graph m_Graph;
	};

	class NodeEditor
	{
	public:
		NodeEditor()
		{
			// TEMP

			ref<Node> root = makeRef<DisplayNode>();
			root->name = "Shader output";
			this->m_Graph.nodes.push_back(root);
			this->m_Graph.rootNode = &*this->m_Graph.nodes.back();
			
			ref<AbstractInputPin> inpin = makeRef<InputPin<glm::vec4>>();
			inpin->name = "gl_Position";
			root->submitInputPin(inpin);

			inpin = makeRef<InputPin<glm::vec2>>();
			inpin->name = "p_textureCoord";
			root->submitInputPin(inpin);
			
			inpin = makeRef<InputPin<float>>();
			inpin->name = "p_texID";
			root->submitInputPin(inpin);
						
			ref<Node> node = makeRef<ValueNode>();
			node->name = "Shader Attribute Inputs";
			this->m_Graph.nodes.push_back(node);

			ref<AbstractOutputPin> pin = makeRef<OutputPin<glm::vec3>>();
			pin->name = "a_position";
			node->submitOutputPin(pin);
			
			pin = makeRef<OutputPin<glm::vec3>>();
			pin->name = "a_normal";
			node->submitOutputPin(pin);
			
			pin = makeRef<OutputPin<glm::vec2>>();
			pin->name = "a_textureCoord";
			node->submitOutputPin(pin);
			
			pin = makeRef<OutputPin<glm::vec3>>();
			pin->name = "a_color";
			node->submitOutputPin(pin);
			
			pin = makeRef<OutputPin<glm::mat4>>();
			pin->name = "a_transform";
			node->submitOutputPin(pin);
			
			pin = makeRef<OutputPin<float>>();
			pin->name = "a_texID";
			node->submitOutputPin(pin);

			node = makeRef<ValueNode>();
			node->name = "Shader Uniform Inputs";
			this->m_Graph.nodes.push_back(node);

			pin = makeRef<OutputPin<glm::mat4>>();
			pin->name = "u_viewProjection";
			node->submitOutputPin(pin);

			// TEMP
		}
		~NodeEditor() = default;
		void renderImGUI();
	private:
		void submitLinks();
		void handleLinks();
		void removeNodes();
		void removeLinks();

		void getSelectedNodes();
		void getSelectedLinks();

		void begin();
		void end();

		Graph m_Graph;
		std::vector<Node*> m_SelectedNodes;
		std::vector<Link*> m_SelectedLink;
	};
}