#include "stdafx.h"
#include "ResourceTree.h"
#include "Core.h"
#include "NodeTypes.h"

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
            ImGui::Separator();
            GraphNode::Ptr root_node = *nodes.begin();
            if (ImGui::TreeNodeEx(root_node->Name().c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen))
                {
                ShowNodeList(root_node->Children());
                ImGui::TreePop();
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::OnGraphEvent(GraphEvent evt, GraphNode::Ptr node)
        {
        ImGuiTreeNodeFlags base_flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

        switch (node->Type())
            {
            case NodeType::unknown:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf));
                break;
            case NodeType::root:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag));
                break;
            case NodeType::directory:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag));
                break;
            case NodeType::file:
                {
                FileNode::Ptr fnode = dynamic_pointer_cast<FileNode>(node);
                switch (fnode->FileType())
                    {
                    case NodeFileType::config:
                        node->VisualState(std::make_shared<TreeVisualState>(false, base_flag));
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
                        node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf));
                        break;
                    }
                }
                break;
            case NodeType::include:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf));
                break;
            case NodeType::section:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf));
                break;
            case NodeType::property:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf));
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
        if (node->Type() != NodeType::property)
            {
            TreeVisualState::Ptr vstate = std::static_pointer_cast<TreeVisualState>(node->VisualState());
            ImGuiTreeNodeFlags node_flags = vstate->m_flags | ((m_selected == node) ? ImGuiTreeNodeFlags_Selected : 0);

            bool opened = ImGui::TreeNodeEx((void*)(intptr_t)node.get(), node_flags, node->Name().c_str());

            if (ImGui::IsItemClicked())
                {
                if (m_selected != node)
                    m_core->SelectedNode(node);
                m_selected = node;
                }

            if (node->Type() == NodeType::section)
                {
                if (ImGui::BeginPopupContextItem())
                    {
                    if (ImGui::MenuItem("New camera"))
                        {
                        ImGui::Text("plopl");
                        }

                    if (ImGui::MenuItem("New camera2"))
                        {
                        }

                    ImGui::EndPopup();
                    }                }

            if (opened)
                {
                const GraphNodeList & children = node->Children();

                if (children.size())
                    ShowNodeList(children);

                ImGui::TreePop();
                }
            }

        }


    }
