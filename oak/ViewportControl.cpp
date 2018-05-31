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
        orxFLOAT vpW, vpH;
        orxFLOAT vpX, vpY;
        bool modified = false;
        orxViewport_GetSize(m_viewport, &vpW, &vpH);

        if ((vpW != m_size.x) || (vpH != m_size.y))
            {
            orxViewport_SetSize(m_viewport, m_size.x, m_size.y);
            modified = true;
            }

        orxViewport_GetPosition(m_viewport, &vpX, &vpY);

        if ((vpX != m_position.x) || (vpY != m_position.y))
            {
            orxViewport_SetPosition(m_viewport, m_position.x, m_position.y);
            modified = true;
            }

        if (modified)
            {
            orxAABOX frustum;
            orxCamera_GetFrustum(m_camera, &frustum);

            orxVECTOR cam_pos;
            orxCamera_GetPosition(m_camera, &cam_pos);
            orxCamera_SetFrustum(m_camera, m_size.x, m_size.y, frustum.vTL.fZ, frustum.vBR.fZ);
            orxCamera_SetPosition(m_camera, &cam_pos);
            }

        }


    }
