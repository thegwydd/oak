#include "stdafx.h"
#include "GraphNode.h"
#include "StringUtility.h"

namespace oak
    {

    DEFINE_ENUM_ENTRY_BEGIN(NodeType)
    DEFINE_ENUM_ENTRY(NodeType::unknown, "unknown")
    DEFINE_ENUM_ENTRY(NodeType::root, "root")
    DEFINE_ENUM_ENTRY(NodeType::directory, "directory")
    DEFINE_ENUM_ENTRY(NodeType::file, "file")
    DEFINE_ENUM_ENTRY(NodeType::include, "include")
    DEFINE_ENUM_ENTRY(NodeType::section, "section")
    DEFINE_ENUM_ENTRY(NodeType::property, "property")
    DEFINE_ENUM_ENTRY_END()


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

    DEFINE_ENUM_ENTRY_BEGIN(GraphEvent)
    DEFINE_ENUM_ENTRY(GraphEvent::add, "add")
    DEFINE_ENUM_ENTRY(GraphEvent::remove, "remove")
    DEFINE_ENUM_ENTRY(GraphEvent::rename, "rename")
    DEFINE_ENUM_ENTRY(GraphEvent::move, "move")
    DEFINE_ENUM_ENTRY(GraphEvent::update, "update")
    DEFINE_ENUM_ENTRY_END()





    std::vector<std::string> g_config_extensions = { ".ini" };
    std::vector<std::string> g_script_extensions = { ".lua", ".js", ".as", ".c", ".cpp", ".c++", ".h", ".hpp", ".h++" };
    std::vector<std::string> g_image_extensions = { ".jpg", ".jpeg", ".png", ".bmp", ".gif" };
    std::vector<std::string> g_sound_extensions = { ".wav", ".ogg", ".mp3" };
    std::vector<std::string> g_shader_extensions = { ".glslv", ".glslf", ".frag", ".vert" };
    std::vector<std::string> g_executable_extensions = { ".exe", ".com" };
    std::vector<std::string> g_library_extensions = { ".dll" };
    std::vector<std::string> g_font_extensions = { ".ttf", ".otf" };


    std::vector<std::string> g_system_files = { "imgui.ini", "oak.ini" };



    //////////////////////////////////////////////////////////////////////////
    GraphNode::GraphNode(const std::string & n, NodeType t) : GraphNode(n, "", t)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    GraphNode::GraphNode(const std::string & n, const std::string & desc, NodeType t) :
        m_name(n),
        m_description(desc),
        m_type(t),
        m_file_type(NodeFileType::not_a_file)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    GraphNode::~GraphNode()
        {
        }








    //////////////////////////////////////////////////////////////////////////
    Graph::Graph() : Graph(filesystem::current_path().string())
        {
        }

    //////////////////////////////////////////////////////////////////////////
    Graph::Graph(const std::string & folder) :
        m_folder(folder)
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void Graph::Rebuild()
        {
        Rebuild(m_folder);
        }

    //////////////////////////////////////////////////////////////////////////
    void Graph::Rebuild(const std::string & folder)
        {
        TRACE_S_NFO("resource_tree", __FUNCTION__);

        filesystem::path root_path = folder;

        GraphNodeList nodes;
        GraphNode::Ptr root_node = nodes.emplace_back(std::make_shared<GraphNode>("root", root_path.string(), NodeType::root));
        m_Event.Signal([=](IGraphListener * l) { l->OnGraphEvent(GraphEvent::add, root_node); });
        BuildDirectory(root_node, root_path);

        m_nodes = nodes;
        }

    //////////////////////////////////////////////////////////////////////////
    void Graph::BuildDirectory(GraphNode::Ptr parent_node, filesystem::path current_dir)
        {
        TRACE_S_NFO("resource_tree", "{} - building directory : {}", __FUNCTION__, current_dir.string());

        filesystem::directory_entry dir_entry(current_dir);
        for (auto & fs_node : filesystem::directory_iterator(dir_entry))
            {
            filesystem::path cur_path = fs_node.path();
            if (filesystem::is_directory(cur_path))
                {
                GraphNode::Ptr cur_node = std::make_shared<GraphNode>(cur_path.filename().string(), cur_path.string(), NodeType::directory);
                parent_node->AddChild(cur_node);
                m_Event.Signal([=](IGraphListener * l) { l->OnGraphEvent(GraphEvent::add, cur_node); });
                BuildDirectory(cur_node, cur_path);
                }
            else if (filesystem::is_regular_file(cur_path))
                {
                TRACE_S_NFO("resource_tree", "{} - found file : {}", __FUNCTION__, cur_path.filename().string());

                if (!IsInGroup(cur_path.filename().string(), g_system_files))
                    {
                    GraphNode::Ptr cur_node = std::make_shared<GraphNode>(cur_path.filename().string(), cur_path.string(), NodeType::file);
                    parent_node->AddChild(cur_node);

                    // detect type of file
                    std::string extension = cur_path.extension().string();
                    if (IsInGroup(extension, g_config_extensions))
                        {
                        cur_node->FileType(NodeFileType::config);
                        BuildIniFile(cur_node, cur_path);
                        }
                    else if (IsInGroup(extension, g_script_extensions))
                        cur_node->FileType(NodeFileType::script);
                    else if (IsInGroup(extension, g_image_extensions))
                        cur_node->FileType(NodeFileType::image);
                    else if (IsInGroup(extension, g_sound_extensions))
                        cur_node->FileType(NodeFileType::sound);
                    else if (IsInGroup(extension, g_shader_extensions))
                        cur_node->FileType(NodeFileType::shader);
                    else if (IsInGroup(extension, g_executable_extensions))
                        cur_node->FileType(NodeFileType::executable);
                    else if (IsInGroup(extension, g_library_extensions))
                        cur_node->FileType(NodeFileType::library);
                    else if (IsInGroup(extension, g_font_extensions))
                        cur_node->FileType(NodeFileType::font);
                    else
                        cur_node->FileType(NodeFileType::unknown);

                    // signal event
                    m_Event.Signal([=](IGraphListener * l) { l->OnGraphEvent(GraphEvent::add, cur_node); });
                    }
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    void Graph::BuildIniFile(GraphNode::Ptr parent_node, filesystem::path filename)
        {
        OrxIniFile * pfile = m_ini_container.LoadFile(filename.string());
        for (auto item : pfile->GetSections())
            {
            GraphNode::Ptr cur_node = std::make_shared<GraphNode>(item->GetName(), NodeType::section);
            parent_node->AddChild(cur_node);
            m_Event.Signal([=](IGraphListener * l) { l->OnGraphEvent(GraphEvent::add, cur_node); });

            for (auto pp : item->GetKeys())
                {
                GraphNode::Ptr prop_node = std::make_shared<GraphNode>(pp->GetName(), NodeType::property);
                cur_node->AddChild(prop_node);
                m_Event.Signal([=](IGraphListener * l) { l->OnGraphEvent(GraphEvent::add, prop_node); });
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    bool Graph::IsInGroup(const std::string & extension, const std::vector<std::string> & extensions_group)
        {
        for (auto & ext : extensions_group)
            if (::case_ins_compare(ext, extension))
                return true;
        return false;
        }





    }
