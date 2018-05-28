#include "stdafx.h"
#include "MainWindow.h"
#include "imgui_dock.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    MainWindow::MainWindow(Core * core, const std::string & _name) : 
        UiWindow(core, _name),
        m_resource_tree(core)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    MainWindow::~MainWindow()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void MainWindow::Render()
        {
        ImGui::SetNextWindowPos(m_position);
        ImGui::SetNextWindowSize(m_size, ImGuiCond_Always);
        if (ImGui::Begin(m_name.c_str(), nullptr, m_size, m_alpha, m_flags))
            {
            // dock layout by hard-coded or .ini file
            if (ImGui::BeginDockspace())
                {
                ImGui::SetNextDock(m_name.c_str(), ImGuiDockSlot_Left);
                if (ImGui::BeginDock("Resources"))
                    {
                    m_resource_tree.Render();
                    }
                ImGui::EndDock();

                ImGui::SetNextDock(m_name.c_str(), ImGuiDockSlot_Bottom);
                if (ImGui::BeginDock("Assets"))
                    {
                    ImGui::Text("I'm BentleyBlanks!");
                    }
                ImGui::EndDock();

                ImGui::SetNextDock(m_name.c_str(), ImGuiDockSlot_None);
                if (ImGui::BeginDock("Viewport"))
                    {
                    ImGui::Text("I'm LonelyWaiting!");
                    }
                ImGui::EndDock();
                }
            ImGui::EndDockspace();
           }
        ImGui::End();

        }


    }
