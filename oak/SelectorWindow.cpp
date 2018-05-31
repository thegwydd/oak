#include "stdafx.h"
#include "SelectorWindow.h"
#include "imgui_dock.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    SelectorWindow::SelectorWindow(Core * core) : 
        UiEditor(core, "Selector"),
        m_resource_tree(core),
        m_inspector(core)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    SelectorWindow::~SelectorWindow()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    bool SelectorWindow::Initialize()
        {
        bool ret = m_resource_tree.Initialize();
        if (ret)
            ret = m_inspector.Initialize();
        return ret;
        }
    
    //////////////////////////////////////////////////////////////////////////
    void SelectorWindow::Deinitialize()
        {
        m_resource_tree.Deinitialize();
        m_inspector.Deinitialize();
        }

    //////////////////////////////////////////////////////////////////////////
    void SelectorWindow::Render()
        {
        ImVec2 last_size = ImVec2(0, 0);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, last_size);

        ImGui::BeginChild("Hierarchy", ImVec2(m_size.x - 2 * m_SplitterSize, m_ResourceTreeHeight), true, ImGuiWindowFlags_HorizontalScrollbar);
        m_resource_tree.Render();
        ImGui::EndChild();

        ImGui::InvisibleButton("hsplitter", ImVec2(-1, m_SplitterSize));
        if (ImGui::IsItemActive())
            m_ResourceTreeHeight += ImGui::GetIO().MouseDelta.y;

        last_size = ImVec2(m_size.x - 2 * m_SplitterSize, 0);
        ImGui::BeginChild("Inspector", last_size, true);
        m_inspector.Render();
        ImGui::EndChild();

        ImGui::PopStyleVar();
        }

    }
