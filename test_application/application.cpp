#include "stdafx.h"
#include "application.h"


//////////////////////////////////////////////////////////////////////////
application::application()
    {
    }

//////////////////////////////////////////////////////////////////////////
application::~application()
    {
    }

//////////////////////////////////////////////////////////////////////////
orxSTATUS application::init()
    {
    // Creates main viewport
    m_main_viewport = orxViewport_CreateFromConfig("MainViewport");
    // Gets main camera
    m_main_camera = orxViewport_GetCamera(m_main_viewport);
    // setup event handler to resize viewport    
    orxEvent_AddHandler(orxEVENT_TYPE_DISPLAY, application::static_event_handler);

    oak_init();

    return orxSTATUS_SUCCESS;
    }

//////////////////////////////////////////////////////////////////////////
orxSTATUS application::run()
    {
    oak_run();

    return orxSTATUS_SUCCESS;
    }

//////////////////////////////////////////////////////////////////////////
void application::exit()
    {
    oak_exit();
    }

//////////////////////////////////////////////////////////////////////////
orxSTATUS application::on_event(const orxEVENT *_pstEvent)
    {
    if (_pstEvent->eType == orxEVENT_TYPE_DISPLAY)
        resize_viewport();

    return orxSTATUS_SUCCESS;
    }

//////////////////////////////////////////////////////////////////////////
void application::resize_viewport()
    {
    orxFLOAT scr_w, scr_h;
    orxDisplay_GetScreenSize(&scr_w, &scr_h);

    orxFLOAT vwp_w, vwp_h;
    orxViewport_GetSize(m_main_viewport, &vwp_w, &vwp_h);

    orxAABOX frustum;
    orxCamera_GetFrustum(m_main_camera, &frustum);

    orxVECTOR cam_pos;
    orxCamera_GetPosition(m_main_camera, &cam_pos);
    orxCamera_SetFrustum(m_main_camera, vwp_w, vwp_h, frustum.vTL.fZ, frustum.vBR.fZ);
    orxCamera_SetPosition(m_main_camera, &cam_pos);

    orxDEBUG_PRINT(orxDEBUG_LEVEL_LOG, "Viewport Size : %f, %f", vwp_w, vwp_h);
    }
