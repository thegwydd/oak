#pragma once

#include "UiControl.h"
#include "GraphNode.h"


namespace oak
    {
    namespace filesystem = std::experimental::filesystem;


    //////////////////////////////////////////////////////////////////////////
    struct TreeVisualState : public VisualState
        {
        using Ptr = std::shared_ptr<TreeVisualState>;

        TreeVisualState(bool opened, ImGuiTreeNodeFlags flags) :
            m_opened(opened),
            m_flags(flags)
            {}
        virtual ~TreeVisualState() {}

        bool                    m_opened;
        ImGuiTreeNodeFlags      m_flags;
        };


    //////////////////////////////////////////////////////////////////////////
    class ResourceTree : public UiControl, IGraphListener
        {
        public:
            ResourceTree(Core * core);
            ~ResourceTree();

        public:
            virtual bool Initialize() override { return true; }
            virtual void Deinitialize() override {}
            virtual void Render() override;
            virtual void OnGraphEvent(GraphEvent evt, GraphNode::Ptr node) override;

        private:
            void ShowNodeList(const GraphNodeList & nodes);
            void ShowNode(GraphNode::Ptr node);

        private:
            GraphNode::Ptr      m_selected = nullptr;

        };



    }
