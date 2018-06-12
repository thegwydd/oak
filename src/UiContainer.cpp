#include "stdafx.h"
#include "UiContainer.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    UiContainer::UiContainer(Core * core, const std::string & _name) : UiControl(core, _name)
        {
        }


    //////////////////////////////////////////////////////////////////////////
    UiContainer::~UiContainer()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void UiContainer::Render()
        {
        for (auto control : m_controls)
            control->Render();
        }

    }
