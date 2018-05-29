#include "stdafx.h"
#include "MainWindow.h"
#include "imgui_dock.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    MainWindow::MainWindow(Core * core, const std::string & _name) : 
        UiWindow(core, _name),
        m_resource_tree(core),
        m_viewport(core),
        m_inspector(core)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    MainWindow::~MainWindow()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    bool MainWindow::Initialize()
        {
        bool ret = m_resource_tree.Initialize();
        if (ret)
            ret = m_inspector.Initialize();
        if (ret)
            ret = m_viewport.Initialize();
        return ret;
        }
    
    //////////////////////////////////////////////////////////////////////////
    void MainWindow::Deinitialize()
        {
        m_resource_tree.Deinitialize();
        m_inspector.Deinitialize();
        m_viewport.Deinitialize();
        }

    //////////////////////////////////////////////////////////////////////////
    void MainWindow::Render()
        {
        ImGui::SetNextWindowPos(m_position);
        ImGui::SetNextWindowSize(m_size, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSizeConstraints(m_size, m_size);
        if (ImGui::Begin(m_name.c_str(), nullptr, m_size, m_alpha, m_flags))
            {
            static float w = 200.0f;
            static float h = m_size.y;
            
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            
            ImGui::BeginChild("Hierarchy", ImVec2(w, h), true, ImGuiWindowFlags_HorizontalScrollbar);
            m_resource_tree.Render();
            m_inspector.Render();
            ImGui::EndChild();
            
            ImGui::SameLine();
            
            ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, h));
            if (ImGui::IsItemActive())
                w += ImGui::GetIO().MouseDelta.x;
            
            ImGui::SameLine();
            
            ImGui::BeginChild("Viewport", ImVec2(0, h), true);
            m_viewport.Render();
            ImGui::EndChild();

/*  third at the bottom
            ImGui::InvisibleButton("hsplitter", ImVec2(-1, 8.0f));
            if (ImGui::IsItemActive())
                h += ImGui::GetIO().MouseDelta.y;

            ImGui::BeginChild("Dunno", ImVec2(0, 0), true);
            ImGui::EndChild();

*/
            ImGui::PopStyleVar();
           }
        ImGui::End();

        }


    }
