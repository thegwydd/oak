#include "stdafx.h"
#include "core.h"

//////////////////////////////////////////////////////////////////////////
orxSTATUS orxFASTCALL oak_debug_callback(orxDEBUG_LEVEL _eLevel, const orxSTRING _zFunction, const orxSTRING _zFile, orxU32 _u32Line, const orxSTRING _zLog)
    {
    return orxSTATUS_SUCCESS;
    }


namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    core::core()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    core::~core()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    orxSTATUS core::init()
        {
        orxDEBUG_SET_LOG_CALLBACK(oak_debug_callback);

        TRACE_S_NFO("core", __FUNCTION__);

        // Initialize gui
        init_gui();

        return orxSTATUS_SUCCESS;
        }

    //////////////////////////////////////////////////////////////////////////
    orxSTATUS core::run()
        {
        ImGui_Orx_NewFrame();

        m_resource_tree.render();

        ImGui::Render();

        return orxSTATUS_SUCCESS;
        }

    //////////////////////////////////////////////////////////////////////////
    void core::exit()
        {
        TRACE_S_NFO("core", __FUNCTION__);
        }

    //////////////////////////////////////////////////////////////////////////
    void core::init_gui()
        {
        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();

        /* create the gui context */
        ImGui::CreateContext();

        /* initialize the gui port */
        ImGui_Orx_Init();

        /* add events to manage */
        orxEvent_AddHandler(orxEVENT_TYPE_RENDER, core::static_event_handler);

        // Setup style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your core (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'misc/fonts/README.txt' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);
         
        m_resource_tree.rebuild();

        }

    //////////////////////////////////////////////////////////////////////////
    orxSTATUS core::on_event(const orxEVENT *_pstEvent)
        {
        switch (_pstEvent->eType)
            {
            case orxEVENT_TYPE_RENDER:
                {
                /* we render ImGui stuff on the top so we call it at the end of Orx frame rendering cycle */
                if (_pstEvent->eID == orxRENDER_EVENT_STOP)
                    ImGui_Orx_Render(NULL, ImGui::GetDrawData());
                }
                break;

            default:
                break;
            }

        return orxSTATUS_SUCCESS;
        }


    }

