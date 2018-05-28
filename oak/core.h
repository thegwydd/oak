#pragma once

#include "MainWindow.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    class Core
        {
        public:
            Core();
            ~Core();

        public:
            static Core & Get()
                {
                static Core * m_instance;
                if (m_instance == nullptr)
                    m_instance = new Core;
                return *m_instance;
                }

            orxSTATUS Init();
            orxSTATUS Run();
            void Exit();

        public:
            oak::Graph & Graph() { return m_graph; }

        private:
            static orxSTATUS orxFASTCALL StaticEventHandler(const orxEVENT *_pstEvent) { return Core::Get().OnEvent(_pstEvent); }
            void InitGui();
            orxSTATUS OnEvent(const orxEVENT *_pstEvent);

        private:
            oak::Graph          m_graph;
            oak::MainWindow     m_main_window;

        };

    }
