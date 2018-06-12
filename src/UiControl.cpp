#include "stdafx.h"
#include "UiControl.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    UiControl::UiControl(Core * core, const std::string & _name) :
        m_core(core),
        m_name(_name)
        {
        }
            
    //////////////////////////////////////////////////////////////////////////
    UiControl::~UiControl()
        {
        }


    }
