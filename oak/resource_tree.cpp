#include "stdafx.h"
#include "resource_tree.h"
#include "string_utility.h"
#include "ini.h"


std::vector<std::string> g_config_extensions = { ".ini" };
std::vector<std::string> g_script_extensions = { ".lua", ".js", ".as", ".c", ".cpp", ".c++", ".h", ".hpp", ".h++" };
std::vector<std::string> g_image_extensions = { ".jpg", ".jpeg", ".png", ".bmp", ".gif" };
std::vector<std::string> g_sound_extensions = { ".wav", ".ogg", ".mp3" };
std::vector<std::string> g_shader_extensions = { ".glslv", ".glslf", ".frag", ".vert" };
std::vector<std::string> g_executable_extensions = { ".exe", ".com" };
std::vector<std::string> g_library_extensions = { ".dll" };
std::vector<std::string> g_font_extensions = { ".ttf", ".otf" };

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    resource_tree::resource_tree()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    resource_tree::~resource_tree()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::rebuild()
        {
        filesystem::path root_path = filesystem::current_path();

        graph_node_list nodes;
        graph_node::ptr root_node = nodes.emplace_back(std::make_shared<graph_node>("root", root_path.string(), "Root element", node_type::root));

        build_directory(root_node, root_path);
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::build_directory(graph_node::ptr parent_node, filesystem::path current_dir)
        {
        filesystem::directory_entry dir_entry(current_dir);
        for (auto & fs_node : filesystem::directory_iterator(dir_entry))
            {
            filesystem::path cur_path = fs_node.path();
            if (filesystem::is_directory(cur_path))
                {
                graph_node::ptr cur_node = std::make_shared<graph_node>(cur_path.filename().string(), cur_path.string(), "", node_type::directory);
                parent_node->add_child(cur_node);
                build_directory(cur_node, cur_path);
                }
            else if (filesystem::is_regular_file(cur_path))
                {
                graph_node::ptr cur_node = std::make_shared<graph_node>(cur_path.filename().string(), cur_path.string(), "", node_type::file);
                parent_node->add_child(cur_node);

                // detect type of file
                std::string extension = cur_path.extension().string();
                if (extentension_is_in_group(extension, g_config_extensions))
                    {
                    cur_node->file_type(node_file_type::config);
                    build_ini_file(cur_node, cur_path);
                    }
                else if (extentension_is_in_group(extension, g_script_extensions))
                    cur_node->file_type(node_file_type::script);
                else if (extentension_is_in_group(extension, g_image_extensions))
                    cur_node->file_type(node_file_type::image);
                else if (extentension_is_in_group(extension, g_sound_extensions))
                    cur_node->file_type(node_file_type::sound);
                else if (extentension_is_in_group(extension, g_shader_extensions))
                    cur_node->file_type(node_file_type::shader);
                else if (extentension_is_in_group(extension, g_executable_extensions))
                    cur_node->file_type(node_file_type::executable);
                else if (extentension_is_in_group(extension, g_library_extensions))
                    cur_node->file_type(node_file_type::library);
                else if (extentension_is_in_group(extension, g_font_extensions))
                    cur_node->file_type(node_file_type::font);
                else
                    cur_node->file_type(node_file_type::unknown);
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::build_ini_file(graph_node::ptr parent_node, filesystem::path filename)
        {
        INI<> ini_file(filename.string(), true);
        for (auto item : ini_file.sections)
            {
            graph_node::ptr cur_node = std::make_shared<graph_node>(item.first, node_type::section);
            parent_node->add_child(cur_node);

            for (auto pp : *item.second)
                {
                graph_node::ptr prop_node = std::make_shared<graph_node>(item.first, node_type::property);
                cur_node->add_child(prop_node);
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    bool resource_tree::extentension_is_in_group(const std::string & extension, const std::vector<std::string> & extensions_group)
        {
        for (auto & ext : extensions_group)
            if (::case_ins_compare(ext, extension))
                return true;
        return false;
        }

    }
