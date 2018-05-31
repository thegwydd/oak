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

            void SelectedNode(oak::GraphNode::Ptr node) { m_selected_node = node; };
            oak::GraphNode::Ptr SelectedNode() { return m_selected_node; };

            void OnCreateNewDirectory(GraphNode::Ptr node);
            void OnRenameDirectory(GraphNode::Ptr node);
            void OnDeleteDirectory(GraphNode::Ptr node);

            void OnRenameFile(GraphNode::Ptr node);
            void OnDeleteFile(GraphNode::Ptr node);

            void OnRenameInclude(GraphNode::Ptr node);
            void OnDeleteInclude(GraphNode::Ptr node);

            void OnCreateSection(GraphNode::Ptr node, EditorType type);
            void OnEditSectionAs(GraphNode::Ptr node, EditorType type);
            void OnRenameSection(GraphNode::Ptr node);
            void OnDeleteSection(GraphNode::Ptr node);

        public:
            oak::Graph & Graph() { return m_graph; }

        private:
            static orxSTATUS orxFASTCALL StaticEventHandler(const orxEVENT *_pstEvent) { return Core::Get().OnEvent(_pstEvent); }
            void InitGui();
            orxSTATUS OnEvent(const orxEVENT *_pstEvent);

        private:
            oak::Graph          m_graph;
            oak::MainWindow     m_main_window;
            oak::GraphNode::Ptr m_selected_node;
        };

    }
