#pragma once

//////////////////////////////////////////////////////////////////////////
class application
    {
    public:
        application();
        ~application();

    public:
        static application & get()
            {
            static application * m_instance;
            if (m_instance == nullptr)
                m_instance = new application;
            return *m_instance;
            }


        orxSTATUS init();
        orxSTATUS run();
        void exit();

    private:
        static orxSTATUS orxFASTCALL static_event_handler(const orxEVENT *_pstEvent) { return application::get().on_event(_pstEvent); }
        orxSTATUS on_event(const orxEVENT *_pstEvent);
        void resize_viewport();

    protected:
        orxVIEWPORT * m_main_viewport = nullptr;
        orxCAMERA * m_main_camera = nullptr;

    };
