#pragma once

#include "ui_component.h"
#include "graph_node.h"


namespace oak
    {
    namespace filesystem = std::experimental::filesystem;

    //////////////////////////////////////////////////////////////////////////
    struct tree_visual_state : public visual_state
        {
        using ptr = std::shared_ptr<tree_visual_state>;

        tree_visual_state(bool opened, ImGuiTreeNodeFlags flags) :
            m_opened(opened),
            m_flags(flags)
            {}
        virtual ~tree_visual_state() {}

        bool                    m_opened;
        ImGuiTreeNodeFlags      m_flags;
        };


    //////////////////////////////////////////////////////////////////////////
    class resource_tree : public ui_component
        {
        public:
            resource_tree();
            ~resource_tree();

        public:
            virtual void render() override;

        private:
            void show_node_list(const graph_node_list & nodes);
            void show_node(graph_node::ptr node);

        private:

        public:
            const graph_node_list & nodes() const { return m_nodes; }
            void rebuild();

        private:
            void build_directory(graph_node::ptr parent_node, filesystem::path current_dir);
            void build_ini_file(graph_node::ptr parent_node, filesystem::path filename);
            bool is_in_group(const std::string & extension, const std::vector<std::string> & extensions_group);


        private:
            graph_node::ptr     m_selected = nullptr;
            graph_node_list     m_nodes;


        };



    }
