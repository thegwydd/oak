#pragma once

#include "Event.h"

namespace filesystem = std::experimental::filesystem;

namespace oak
    {
    //////////////////////////////////////////////////////////////////////////
    enum class NodeType
        {
        unknown,    // default 
        root,       // a root node
        directory,  // a directory
        file,       // a file (see file_type)
        include,    // and include inside a config file
        section,    // a ini file section
        property,   // a ini section property
        };

    DECLARE_ENUM_ENTRY(NodeType);

    //////////////////////////////////////////////////////////////////////////
    enum class GraphEvent
        {
        add,
        remove,
        rename,
        move,
        update,
        };

    DECLARE_ENUM_ENTRY(GraphEvent);

    class GraphNode;
    using GraphNodeList = std::list<std::shared_ptr<GraphNode>>;

    //////////////////////////////////////////////////////////////////////////
    struct VisualState
        {
        using Ptr = std::shared_ptr<VisualState>;
        VisualState() {}
        virtual ~VisualState() {}
        };

    //////////////////////////////////////////////////////////////////////////
    class GraphNode
        {
        public:
            using Ptr = std::shared_ptr<GraphNode>;

        public:
            GraphNode(const std::string & n = "", NodeType t = NodeType::unknown);
            virtual ~GraphNode();

        public:
            NodeType Type() const { return m_type; }
            void Type(NodeType n) { m_type = n; }

            const std::string & Name() const { return m_name; }
            void Name(const std::string & n) { m_name = n; }

            const GraphNodeList & Children() const { return m_children; }
            void AddChild(GraphNode::Ptr n) { m_children.push_back(n); }

            const VisualState::Ptr & VisualState() const { return m_visual_state; }
            void VisualState(VisualState::Ptr n) { m_visual_state = n; }

        protected:
            std::string         m_name;
            NodeType            m_type;
            GraphNodeList       m_children;
            VisualState::Ptr    m_visual_state;
        };

    //////////////////////////////////////////////////////////////////////////
    class IGraphListener
        {
        public:
            virtual void OnGraphEvent(GraphEvent evt, GraphNode::Ptr node) = 0;
        };

    //////////////////////////////////////////////////////////////////////////
    class Graph
        {
        public:
            using Ptr = std::shared_ptr<Graph>;
            using GraphListeners = std::list<IGraphListener>;

        public:
            Graph();
            Graph(const std::string & folder);

            void Rebuild();
            void Rebuild(const std::string & folder);
            GraphNodeList & Nodes() { return m_nodes; }

        public:
            Event<IGraphListener>   m_Event;

        private:
            void BuildDirectory(GraphNode::Ptr parent_node, filesystem::path current_dir);
            void BuildIniFile(GraphNode::Ptr parent_node, filesystem::path filename);
            bool IsInGroup(const std::string & extension, const std::vector<std::string> & extensions_group);

        private:
            std::string             m_folder;
            OrxIniContainer         m_ini_container;
            GraphNodeList           m_nodes;
        };




    }
