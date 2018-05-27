#pragma once


namespace oak
    {
    //////////////////////////////////////////////////////////////////////////
    enum class node_type
        {
        unknown,    // default 
        root,       // a root node
        directory,  // a directory
        file,       // a file (see file_type)
        include,    // and include inside a config file
        section,    // a ini file section
        property,   // a ini section property
        };

    DECLARE_ENUM_ENTRY(node_type);


    //////////////////////////////////////////////////////////////////////////
    enum class node_file_type
        {
        not_a_file,
        unknown,
        config,
        script,
        image,
        sound,
        shader,
        executable,
        library,
        font,
        };

    DECLARE_ENUM_ENTRY(node_file_type);

    class graph_node;
    using graph_node_list = std::list<std::shared_ptr<graph_node>>;

    //////////////////////////////////////////////////////////////////////////
    class graph_node
        {
        public:
            using ptr = std::shared_ptr<graph_node>;

        public:
            graph_node(const std::string & n = "", node_type t = node_type::unknown);
            graph_node(const std::string & n, const std::string & tooltip, node_type t);
            graph_node(const std::string & n, const std::string & tooltip, const std::string & desc, node_type t);
            virtual ~graph_node();


        public:
            node_type type() const { return m_type; }
            void type(node_type n) { m_type = n; }

            const std::string & name() const { return m_name; }
            void name(const std::string & n) { m_name = n; }

            const node_file_type & file_type() const { return m_file_type; }
            void file_type(node_file_type n) { m_file_type = n; }

            const std::string & tooltip() const { return m_tooltip; }
            void tooltip(const std::string & n) { m_tooltip = n; }

            const std::string & description() const { return m_description; }
            void description(const std::string & n) { m_description = n; }

            const graph_node_list & children() const { return m_children; }
            void add_child(graph_node::ptr n) { m_children.push_back(n); }

        protected:
            std::string     m_name;
            std::string     m_tooltip;
            std::string     m_description;
            node_type       m_type;
            node_file_type  m_file_type;
            graph_node_list m_children;

        };



    }
