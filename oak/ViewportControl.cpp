#include "stdafx.h"
#include "ViewportControl.h"
    
namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    ViewportControl::ViewportControl(Core * core) :
        UiControl(core, "Viewport"),
        m_viewport(nullptr),
        m_camera(nullptr)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    ViewportControl::~ViewportControl()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    bool ViewportControl::Initialize()
        {
        bool ret = true;

        m_viewport = orxViewport_CreateFromConfig("OakViewport");
        m_camera = orxViewport_GetCamera(m_viewport);

        return ret;
        }

    //////////////////////////////////////////////////////////////////////////
    void ViewportControl::Deinitialize()
        {
        orxViewport_Delete(m_viewport);
        m_viewport = nullptr;
        }

    //////////////////////////////////////////////////////////////////////////
    void ViewportControl::Render()
        {
        orxFLOAT vpX, vpY;
        orxViewport_GetSize(m_viewport, &vpX, &vpY);

        if ((vpX != m_size.x) || (vpY != m_size.y))
            orxViewport_SetSize(m_viewport, m_size.x, m_size.y);

        orxViewport_GetPosition(m_viewport, &vpX, &vpY);

        if ((vpX != m_position.x) || (vpY != m_position.y))
            orxViewport_SetPosition(m_viewport, m_position.x, m_position.y);
        }


    }
