#pragma once

#include "graph_node.h"


namespace oak
    {
    namespace filesystem = std::experimental::filesystem;

    //////////////////////////////////////////////////////////////////////////
    class resource_tree
        {
        public:
            resource_tree();
            ~resource_tree();

        public:
            const graph_node_list & nodes() const { return m_nodes; }
            void rebuild();

        private:
            void build_directory(graph_node::ptr parent_node, filesystem::path current_dir);
            void build_ini_file(graph_node::ptr parent_node, filesystem::path filename);
            bool extentension_is_in_group(const std::string & extension, const std::vector<std::string> & extensions_group);


        private:
            graph_node_list     m_nodes;


        };



    }
