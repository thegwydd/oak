#include "stdafx.h"
#include "MainWindow.h"
#include "imgui_dock.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    MainWindow::MainWindow(Core * core, const std::string & _name) : 
        UiWindow(core, _name),
        m_selector(core),
        m_viewport(core)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    MainWindow::~MainWindow()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    bool MainWindow::Initialize()
        {
        bool ret = m_selector.Initialize();
        if (ret)
            ret = m_viewport.Initialize();
        return ret;
        }
    
    //////////////////////////////////////////////////////////////////////////
    void MainWindow::Deinitialize()
        {
        m_selector.Deinitialize();
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
            ImVec2 last_size = ImVec2(0, 0);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, last_size);
            
            ImGui::BeginChild("Editor", ImVec2(m_LeftPaneWidth, m_LeftPaneHeight), true, ImGuiWindowFlags_HorizontalScrollbar);
            RenderLeftPane();
            ImGui::EndChild();
            
            ImGui::SameLine();

            ImGui::InvisibleButton("vsplitter", ImVec2(m_SplitterSize, m_LeftPaneHeight));
            if (ImGui::IsItemActive())
                m_LeftPaneWidth += ImGui::GetIO().MouseDelta.x;
            
            ImGui::SameLine();
            
            last_size = ImVec2(0, m_LeftPaneHeight);
            ImGui::BeginChild("Viewport", last_size, true);
            m_viewport.Position(ImGui::GetWindowPos());
            m_viewport.Size(ImGui::GetWindowSize());
            m_viewport.Render();
            ImGui::EndChild();

            ImGui::PopStyleVar();
           }
        ImGui::End();

        }


    //////////////////////////////////////////////////////////////////////////
    void MainWindow::RenderLeftPane()
        {
        m_selector.Size(ImVec2(m_LeftPaneWidth, 0));
        m_selector.Render();
        }


    }
