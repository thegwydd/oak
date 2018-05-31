#include "stdafx.h"
#include "NodeTypes.h"
#include "StringUtility.h"

#include <filesystem>

namespace filesystem = std::experimental::filesystem;

namespace oak
    {

    DEFINE_ENUM_ENTRY_BEGIN(NodeFileType)
    DEFINE_ENUM_ENTRY(NodeFileType::not_a_file, "not_a_file")
    DEFINE_ENUM_ENTRY(NodeFileType::unknown, "unknown")
    DEFINE_ENUM_ENTRY(NodeFileType::config, "config")
    DEFINE_ENUM_ENTRY(NodeFileType::script, "script")
    DEFINE_ENUM_ENTRY(NodeFileType::image, "image")
    DEFINE_ENUM_ENTRY(NodeFileType::sound, "sound")
    DEFINE_ENUM_ENTRY(NodeFileType::shader, "shader")
    DEFINE_ENUM_ENTRY(NodeFileType::executable, "executable")
    DEFINE_ENUM_ENTRY(NodeFileType::library, "library")
    DEFINE_ENUM_ENTRY(NodeFileType::font, "font")
    DEFINE_ENUM_ENTRY_END()

    
    //////////////////////////////////////////////////////////////////////////
    RootNode::RootNode(const std::string & n) : GraphNode(n, NodeType::root) 
        {}

    //////////////////////////////////////////////////////////////////////////
    RootNode::~RootNode()
        {}




    //////////////////////////////////////////////////////////////////////////
    DirectoryNode::DirectoryNode(const std::string & n) : GraphNode(n, NodeType::directory) 
        {
        m_full_path = n;
        filesystem::path cur_path = n;
        Name(cur_path.filename().string());
        }

    //////////////////////////////////////////////////////////////////////////
    DirectoryNode::~DirectoryNode() 
        {}




    //////////////////////////////////////////////////////////////////////////
    FileNode::FileNode(const std::string & n) : GraphNode(n, NodeType::file) 
        {
        m_full_path = n;
        filesystem::path cur_path = n;
        Name(cur_path.filename().string());
        }

    //////////////////////////////////////////////////////////////////////////
    FileNode::~FileNode()
        {}




    //////////////////////////////////////////////////////////////////////////
    IncludeNode::IncludeNode(const std::string & n) : GraphNode(n, NodeType::include) 
        {}

    //////////////////////////////////////////////////////////////////////////
    IncludeNode::~IncludeNode()
        {}




    //////////////////////////////////////////////////////////////////////////
    SectionNode::SectionNode(const std::string & n) : GraphNode(n, NodeType::section) 
        {}

    //////////////////////////////////////////////////////////////////////////
    SectionNode::~SectionNode()
        {}




    //////////////////////////////////////////////////////////////////////////
    PropertyNode::PropertyNode(const std::string & n, const std::string & v) : 
        GraphNode(n, NodeType::property),
        m_value(v)
        {}

    //////////////////////////////////////////////////////////////////////////
    PropertyNode::~PropertyNode()
        {}





    }
