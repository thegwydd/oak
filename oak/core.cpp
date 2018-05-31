#include "stdafx.h"
#include "Core.h"
#include "imgui_dock.h"

//////////////////////////////////////////////////////////////////////////
orxSTATUS orxFASTCALL oak_debug_callback(orxDEBUG_LEVEL _eLevel, const orxSTRING _zFunction, const orxSTRING _zFile, orxU32 _u32Line, const orxSTRING _zLog)
    {
    OutputDebugString(_zLog);
    return orxSTATUS_SUCCESS;
    }


namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    Core::Core() :
        m_main_window(this, "oak - orx army knife")
        {
        }

    //////////////////////////////////////////////////////////////////////////
    Core::~Core()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    orxSTATUS Core::Init()
        {
        orxDEBUG_SET_LOG_CALLBACK(oak_debug_callback);

        TRACE_S_NFO("Core", __FUNCTION__);

        // Initialize gui
        InitGui();
        
        orxConfig_Load("oak.ini");

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoResize;
        flags |= ImGuiWindowFlags_NoTitleBar;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;

        m_main_window.Initialize();

        m_main_window.Flags(flags);
        m_main_window.Position(ImVec2(0,0));
        m_main_window.Alpha(0);

        // build the graph
        m_graph.Rebuild();

        return orxSTATUS_SUCCESS;
        }

    //////////////////////////////////////////////////////////////////////////
    orxSTATUS Core::Run()
        {
        m_main_window.Size(ImGui::GetIO().DisplaySize);

        ImGui_Orx_NewFrame();

        //ImGui::ShowDemoWindow();

        m_main_window.Render();
            
        ImGui::Render();

        return orxSTATUS_SUCCESS;
        }

    //////////////////////////////////////////////////////////////////////////
    void Core::Exit()
        {
        m_main_window.Deinitialize();

        TRACE_S_NFO("Core", __FUNCTION__);
        }

    //////////////////////////////////////////////////////////////////////////
    void Core::InitGui()
        {
        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();

        /* create the gui context */
        ImGui::CreateContext();

        /* avoid loadin/storing to/from imgui.ini*/
        ImGui::GetIO().IniFilename = NULL;

        /* initialize the gui port */
        ImGui_Orx_Init();

        /* add events to manage */
        orxEvent_AddHandler(orxEVENT_TYPE_RENDER, Core::StaticEventHandler);
        orxEvent_AddHandler(orxEVENT_TYPE_DISPLAY, Core::StaticEventHandler);

        // Setup style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        ImGui::InitDock();
        }

    //////////////////////////////////////////////////////////////////////////
    orxSTATUS Core::OnEvent(const orxEVENT *_pstEvent)
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

            case orxEVENT_TYPE_DISPLAY:
                m_main_window.Size(ImGui::GetIO().DisplaySize);
                break;

            default:
                break;
            }

        return orxSTATUS_SUCCESS;
        }


    //////////////////////////////////////////////////////////////////////////
    void Core::OnCreateNewDirectory(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnRenameDirectory(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnDeleteDirectory(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnRenameFile(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnDeleteFile(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnRenameInclude(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnDeleteInclude(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnCreateSection(GraphNode::Ptr node, EditorType type)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnEditSectionAs(GraphNode::Ptr node, EditorType type)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnRenameSection(GraphNode::Ptr node)
        {

        }

    //////////////////////////////////////////////////////////////////////////
    void Core::OnDeleteSection(GraphNode::Ptr node)
        {

        }



    }

