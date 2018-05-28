#include "stdafx.h"
#include "UiWindow.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    UiWindow::UiWindow(Core * core, const std::string & _name) : UiContainer(core, _name)
        {
        }


    //////////////////////////////////////////////////////////////////////////
    UiWindow::~UiWindow()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void UiWindow::Render()
        {
        ImGui::SetNextWindowPos(m_position);
        ImGui::Begin(m_name.c_str(), nullptr, m_size, m_alpha, m_flags);

        UiContainer::Render();

        ImGui::End();
        }

    }
