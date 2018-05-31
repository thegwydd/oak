#include "stdafx.h"
#include "ResourceTree.h"
#include "Core.h"
#include "NodeTypes.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    ResourceTree::ResourceTree(Core * core) : UiControl(core, "ResourceTree")
        {
        }

    //////////////////////////////////////////////////////////////////////////
    ResourceTree::~ResourceTree()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    bool ResourceTree::Initialize() 
        { 
        m_core->Graph().m_Event += this;

        
        m_menu_map[NodeType::unknown] = {};
        m_menu_map[NodeType::root] = {};
        m_menu_map[NodeType::directory] = {
                { "Create new", [&](GraphNode::Ptr node) { m_core->OnCreateNewDirectory(node); } },
                { "Rename", [&](GraphNode::Ptr node) { m_core->OnRenameDirectory(node); } },
                { "Delete", [&](GraphNode::Ptr node) { m_core->OnDeleteDirectory(node); } },
            };

        m_menu_map[NodeType::file] = {
                { "Rename", [&](GraphNode::Ptr node) { m_core->OnRenameFile(node); } },
                { "Delete", [&](GraphNode::Ptr node) { m_core->OnDeleteFile(node); } },
            };

        m_menu_map[NodeType::include] = {
                { "Rename", [&](GraphNode::Ptr node) { m_core->OnRenameInclude(node); } },
                { "Delete", [&](GraphNode::Ptr node) { m_core->OnDeleteInclude(node); } },
            };

        MenuItems create_section_menu_items;
        for (int a = 0; a < (uint32_t)EditorType::EndOfEnum; ++a)
            {
            create_section_menu_items.push_back({
                 EnumMapper::GetText<EditorType>((EditorType)a),
                 [&, a](GraphNode::Ptr node) { m_core->OnCreateSection(node, (EditorType)a); }
                });
            }

        MenuItems edit_section_menu_items;
        for (int a = 0; a < (uint32_t)EditorType::EndOfEnum; ++a)
            {
            edit_section_menu_items.push_back({
                EnumMapper::GetText<EditorType>((EditorType)a),
                [&, a](GraphNode::Ptr node) { m_core->OnEditSectionAs(node, (EditorType)a); }
                });
            }

        m_menu_map[NodeType::section] = {
                { "Create new...", nullptr, create_section_menu_items },
                { "", nullptr },
                { "Rename", [&](GraphNode::Ptr node) { m_core->OnRenameSection(node); } },
                { "Delete", [&](GraphNode::Ptr node) { m_core->OnDeleteSection(node); } },
                { "", nullptr },
                {"Edit as...", nullptr, edit_section_menu_items }
            };

        m_menu_map[NodeType::property] = {};

        return true;
        }

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::Deinitialize() 
        {
        //m_core->Graph().m_Event -= this;
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
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf, m_menu_map[node->Type()]));
                break;
            case NodeType::root:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag, m_menu_map[node->Type()]));
                break;
            case NodeType::directory:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag, m_menu_map[node->Type()]));
                break;
            case NodeType::file:
                {
                FileNode::Ptr fnode = dynamic_pointer_cast<FileNode>(node);
                switch (fnode->FileType())
                    {
                    case NodeFileType::config:
                        node->VisualState(std::make_shared<TreeVisualState>(false, base_flag, m_menu_map[node->Type()]));
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
                        node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf, m_menu_map[node->Type()]));
                        break;
                    }
                }
                break;
            case NodeType::include:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf, m_menu_map[node->Type()]));
                break;
            case NodeType::section:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf, m_menu_map[node->Type()]));
                break;
            case NodeType::property:
                node->VisualState(std::make_shared<TreeVisualState>(false, base_flag | ImGuiTreeNodeFlags_Leaf, m_menu_map[node->Type()]));
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

            if (vstate->m_menu_items.size())
                {
                if (ImGui::BeginPopupContextItem())
                    {
                    for (auto menu_item : vstate->m_menu_items)
                        ShowMenu(node, menu_item);

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

    //////////////////////////////////////////////////////////////////////////
    void ResourceTree::ShowMenu(GraphNode::Ptr node, MenuItem & item)
        {
        if (item.m_text.empty())
            ImGui::Separator();
        else
            {
            if (!item.m_subitems.size())
                {
                if (ImGui::MenuItem(item.m_text.c_str()))
                    {
                    if (item.m_callback)
                        item.m_callback(node);
                    }
                }
            else
                {
                if (ImGui::BeginMenu(item.m_text.c_str()))
                    {
                    for (auto sub_menu : item.m_subitems)
                        ShowMenu(node, sub_menu);
                    ImGui::EndMenu();
                    }

                }
            }
        }


    }
