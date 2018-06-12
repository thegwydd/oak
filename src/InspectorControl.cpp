#include "stdafx.h"
#include "InspectorControl.h"
#include "Core.h"
#include "NodeTypes.h"
#include <imgui_internal.h>

#include <memory>

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
        if (node && node->Type() == NodeType::section)
            {
            SectionNode::Ptr snode = dynamic_pointer_cast<SectionNode>(node);
            ImGui::Text(snode->Name().c_str());

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            ImGui::Columns(2);
            ImGui::Separator();

            for (auto child_node : node->Children())
                {
                if (child_node->Type() == NodeType::property)
                    {
                    PropertyNode::Ptr pnode = dynamic_pointer_cast<PropertyNode>(child_node);

                    ImGui::PushID(pnode.get());   // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
                    ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.

                    ImGui::Text(pnode->Name().c_str());

                    ImGui::NextColumn();
                    ImGui::AlignTextToFramePadding();

                    ImGui::Text(pnode->Value().c_str());

                    ImGui::NextColumn();

                    ImGui::PopID();
                    }
                }

            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::PopStyleVar();

            }

        }


    }
