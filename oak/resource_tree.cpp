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

std::vector<std::string> g_system_files = { "imgui.ini", "oak.ini" };

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    resource_tree::resource_tree() : ui_component("resource_tree")
        {
        }

    //////////////////////////////////////////////////////////////////////////
    resource_tree::~resource_tree()
        {
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::render()
        {
        if (m_nodes.size())
            {
            ImGui::SetNextWindowPos(m_position);
            ImGui::Begin(m_name.c_str(), nullptr, m_size, m_alpha, m_flags);
            ImGui::Text("W:%d, H:%d", (int)m_size.x, (int)m_size.y);

            graph_node::ptr root_node = *m_nodes.begin();
            if (ImGui::TreeNode(root_node->name().c_str()))
                {
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 2); // Increase spacing to differentiate leaves from expanded contents.
                show_node_list(root_node->children());

                ImGui::PopStyleVar();
                ImGui::TreePop();
                }

            ImGui::End();
            }

        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::show_node_list(const graph_node_list & nodes)
        {
        for (auto node : nodes)
            show_node(node);
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::show_node(graph_node::ptr node)
        {

        tree_visual_state::ptr vstate = std::static_pointer_cast<tree_visual_state>(node->visual_state());
        ImGuiTreeNodeFlags node_flags = vstate->m_flags | ((m_selected == node) ? ImGuiTreeNodeFlags_Selected : 0);

        if (ImGui::TreeNodeEx((void*)(intptr_t)node.get(), node_flags, node->name().c_str()))
            {
            if (ImGui::IsItemClicked())
                m_selected = node;

            const graph_node_list & children = node->children();

            if (children.size())
                show_node_list(children);

            ImGui::TreePop();
            }
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::rebuild()
        {
        TRACE_S_NFO("resource_tree", __FUNCTION__);

        filesystem::path root_path = filesystem::current_path();

        graph_node_list nodes;
        graph_node::ptr root_node = nodes.emplace_back(std::make_shared<graph_node>("root", root_path.string(), "Root element", node_type::root));

        root_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));

        build_directory(root_node, root_path);

        m_nodes = nodes;
        }

    //////////////////////////////////////////////////////////////////////////
    void resource_tree::build_directory(graph_node::ptr parent_node, filesystem::path current_dir)
        {
        TRACE_S_NFO("resource_tree", "{} - building directory : {}", __FUNCTION__, current_dir.string());

        filesystem::directory_entry dir_entry(current_dir);
        for (auto & fs_node : filesystem::directory_iterator(dir_entry))
            {
            filesystem::path cur_path = fs_node.path();
            if (filesystem::is_directory(cur_path))
                {
                graph_node::ptr cur_node = std::make_shared<graph_node>(cur_path.filename().string(), cur_path.string(), "", node_type::directory);
                cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
                parent_node->add_child(cur_node);
                build_directory(cur_node, cur_path);
                }
            else if (filesystem::is_regular_file(cur_path))
                {
                TRACE_S_NFO("resource_tree", "{} - found file : {}", __FUNCTION__, cur_path.filename().string());

                if (!is_in_group(cur_path.filename().string(), g_system_files))
                    {
                    graph_node::ptr cur_node = std::make_shared<graph_node>(cur_path.filename().string(), cur_path.string(), "", node_type::file);
                    parent_node->add_child(cur_node);

                    // detect type of file
                    std::string extension = cur_path.extension().string();
                    if (is_in_group(extension, g_config_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
                        cur_node->file_type(node_file_type::config);
                        build_ini_file(cur_node, cur_path);
                        }
                    else if (is_in_group(extension, g_script_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::script);
                        }
                    else if (is_in_group(extension, g_image_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::image);
                        }
                    else if (is_in_group(extension, g_sound_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::sound);
                        }
                    else if (is_in_group(extension, g_shader_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::shader);
                        }
                    else if (is_in_group(extension, g_executable_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::executable);
                        }
                    else if (is_in_group(extension, g_library_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::library);
                        }
                    else if (is_in_group(extension, g_font_extensions))
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::font);
                        }
                    else
                        {
                        cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                        cur_node->file_type(node_file_type::unknown);
                        }
                    }
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
            cur_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick));
            parent_node->add_child(cur_node);

            for (auto pp : *item.second)
                {
                graph_node::ptr prop_node = std::make_shared<graph_node>(pp.first, node_type::property);
                prop_node->visual_state(std::make_shared<tree_visual_state>(false, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet));
                cur_node->add_child(prop_node);
                }
            }
        }

    //////////////////////////////////////////////////////////////////////////
    bool resource_tree::is_in_group(const std::string & extension, const std::vector<std::string> & extensions_group)
        {
        for (auto & ext : extensions_group)
            if (::case_ins_compare(ext, extension))
                return true;
        return false;
        }

    }
