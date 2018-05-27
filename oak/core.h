#pragma once

#include "resource_tree.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    class core
        {
        public:
            core();
            ~core();

        public:
            static core & get()
                {
                static core * m_instance;
                if (m_instance == nullptr)
                    m_instance = new core;
                return *m_instance;
                }

            orxSTATUS init();
            orxSTATUS run();
            void exit();

        public:
            oak::resource_tree & resource_tree() { return m_resource_tree; }

        private:
            static orxSTATUS orxFASTCALL static_event_handler(const orxEVENT *_pstEvent) { return core::get().on_event(_pstEvent); }
            void init_gui();
            orxSTATUS on_event(const orxEVENT *_pstEvent);

        private:
            oak::resource_tree     m_resource_tree;

        };

    }
