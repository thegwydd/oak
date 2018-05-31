#include "stdafx.h"
#include "UiEditor.h"
#include "Core.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    UiEditor::UiEditor(Core * core, const std::string & _name) : UiContainer(core, _name)
        {
        }


    //////////////////////////////////////////////////////////////////////////
    UiEditor::~UiEditor()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void UiEditor::Render()
        {
        ImGui::Text(m_core->SelectedNode()->Name().c_str());
        }

    }
