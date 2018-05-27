#include "stdafx.h"
#include "graph_node.h"

namespace oak
    {

    DEFINE_ENUM_ENTRY_BEGIN(node_type)
    DEFINE_ENUM_ENTRY(node_type::unknown, "unknown")
    DEFINE_ENUM_ENTRY(node_type::root, "root")
    DEFINE_ENUM_ENTRY(node_type::directory, "directory")
    DEFINE_ENUM_ENTRY(node_type::file, "file")
    DEFINE_ENUM_ENTRY(node_type::include, "include")
    DEFINE_ENUM_ENTRY(node_type::section, "section")
    DEFINE_ENUM_ENTRY(node_type::property, "property")
    DEFINE_ENUM_ENTRY_END()


    DEFINE_ENUM_ENTRY_BEGIN(node_file_type)
    DEFINE_ENUM_ENTRY(node_file_type::not_a_file, "not_a_file")
    DEFINE_ENUM_ENTRY(node_file_type::unknown, "unknown")
    DEFINE_ENUM_ENTRY(node_file_type::config, "config")
    DEFINE_ENUM_ENTRY(node_file_type::script, "script")
    DEFINE_ENUM_ENTRY(node_file_type::image, "image")
    DEFINE_ENUM_ENTRY(node_file_type::sound, "sound")
    DEFINE_ENUM_ENTRY(node_file_type::shader, "shader")
    DEFINE_ENUM_ENTRY(node_file_type::executable, "executable")
    DEFINE_ENUM_ENTRY(node_file_type::library, "library")
    DEFINE_ENUM_ENTRY(node_file_type::font, "font")
    DEFINE_ENUM_ENTRY_END()


    //////////////////////////////////////////////////////////////////////////
    graph_node::graph_node(const std::string & n, node_type t) : graph_node(n, "", t)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    graph_node::graph_node(const std::string & n, const std::string & tooltip, node_type t) : graph_node(n, "", "", t)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    graph_node::graph_node(const std::string & n, const std::string & tooltip, const std::string & desc, node_type t) :
        m_name(n),
        m_tooltip(tooltip),
        m_description(desc),
        m_type(t),
        m_file_type(node_file_type::not_a_file)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    graph_node::~graph_node()
        {
        }



    }
