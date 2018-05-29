#include "stdafx.h"
#include "InspectorControl.h"
#include "Core.h"
    
namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    InspectorControl::InspectorControl(Core * core) :
        UiControl(core, "Inspector")
        {
        }

    //////////////////////////////////////////////////////////////////////////
    InspectorControl::~InspectorControl()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    bool InspectorControl::Initialize()
        {
        bool ret = true;
        return ret;
        }

    //////////////////////////////////////////////////////////////////////////
    void InspectorControl::Deinitialize()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void InspectorControl::Render()
        {
        oak::GraphNode::Ptr node = m_core->SelectedNode();
        if (node)
            {
            ImGui::Text(node->Name().c_str());

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            ImGui::Columns(2);
            ImGui::Separator();

            for (auto child_node : node->Children())
                {
                if (child_node->Type() == NodeType::property)
                    {
                    ImGui::PushID(child_node.get());   // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
                    ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
                    bool node_open = ImGui::TreeNode("Object", child_node->Name().c_str());
                    ImGui::NextColumn();
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Values");
                    ImGui::NextColumn();
                    if (node_open)
                        {
                        ImGui::PushID(0); // Use field index as identifier.

                        // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("Field", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet, "Field_%d", 0);
                        ImGui::NextColumn();
                        ImGui::PushItemWidth(-1);
                        ImGui::Text("value!");

                        ImGui::PopItemWidth();
                        ImGui::NextColumn();

                        ImGui::PopID();

                        ImGui::TreePop();
                        }
                    ImGui::PopID();
                    }
                }

            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::PopStyleVar();

            }

        }


    }
