#pragma once

#include "UiControl.h"
#include "GraphNode.h"

#include <functional>

namespace oak
    {
    namespace filesystem = std::experimental::filesystem;

    using MenuCallback = std::function<void(GraphNode::Ptr)>;

    //////////////////////////////////////////////////////////////////////////
    struct MenuItem
        {
        MenuItem() : MenuItem("") {};
        MenuItem(const std::string t, MenuCallback cb = nullptr) : m_text(t), m_callback(cb) {};
        virtual ~MenuItem() {};

        std::string         m_text;
        MenuCallback        m_callback;
        };

    using MenuItems = std::list<MenuItem>;

    //////////////////////////////////////////////////////////////////////////
    struct TreeVisualState : public VisualState
        {
        using Ptr = std::shared_ptr<TreeVisualState>;

        TreeVisualState(bool opened, ImGuiTreeNodeFlags flags = 0) :
            m_opened(opened),
            m_flags(flags)
            {}
        virtual ~TreeVisualState() {}

        bool                    m_opened;
        ImGuiTreeNodeFlags      m_flags;
        MenuItems               m_menu_items;
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
