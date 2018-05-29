#include "stdafx.h"
#include "ResourceTree.h"
#include "Core.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    ResourceTree::ResourceTree(Core * core) : UiControl(core, "ResourceTree")
        {
        m_core->Graph().m_Event += this;
        }

    //////////////////////////////////////////////////////////////////////////
    ResourceTree::~ResourceTree()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::Render()
        {
        GraphNodeList & nodes = m_core->Graph().Nodes();
        if (nodes.size())
            {
            ImGui::Text("Hierarchy");

            GraphNode::Ptr root_node = *nodes.begin();
            if (ImGui::TreeNodeEx(root_node->Name().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
                {
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 2); // Increase spacing to differentiate leaves from expanded contents.
                ShowNodeList(root_node->Children());

                ImGui::PopStyleVar();
                ImGui::TreePop();
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::OnGraphEvent(GraphEvent evt, GraphNode::Ptr node)
        {
        switch (node->Type())
            {
            case NodeType::unknown:
                node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                break;
            case NodeType::root:
                node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
                break;
            case NodeType::directory:
                node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
                break;
            case NodeType::file:
                {
                switch (node->FileType())
                    {
                    case NodeFileType::config:
                        node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
                        break;
                    case NodeFileType::not_a_file:
                    case NodeFileType::unknown:
                    case NodeFileType::script:
                    case NodeFileType::image:
                    case NodeFileType::sound:
                    case NodeFileType::shader:
                    case NodeFileType::executable:
                    case NodeFileType::library:
                    case NodeFileType::font:
                    default:
                        node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        break;
                    }
                }
                break;
            case NodeType::include:
                node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                break;
            case NodeType::section:
                node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
                break;
            case NodeType::property:
                node->VisualState(std::make_shared<TreeVisualState>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                break;
            default:
                break;
            }
        }

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::ShowNodeList(const GraphNodeList & nodes)
        {
        for (auto node : nodes)
            ShowNode(node);
        }

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::ShowNode(GraphNode::Ptr node)
        {

        TreeVisualState::Ptr vstate = std::static_pointer_cast<TreeVisualState>(node->VisualState());
        ImGuiTreeNodeFlags node_flags = vstate->m_flags | ((m_selected == node) ? ImGuiTreeNodeFlags_Selected : 0);

        if (ImGui::TreeNodeEx((void*)(intptr_t)node.get(), node_flags, node->Name().c_str()))
            {
            if (ImGui::IsItemClicked())
                {
                if (m_selected != node)
                    m_core->SelectedNode(node);
                m_selected = node;
                }

            const GraphNodeList & children = node->Children();

            if (children.size())
                ShowNodeList(children);

            ImGui::TreePop();
            }
        }


    }
