#pragma once


namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    // base class for all ui components
    class ui_component
        {
        public:
            ui_component(const std::string & _name);
            virtual ~ui_component();

        public:
            virtual void render() = 0;

        public:
            const std::string & name() const { return m_name; }
            void name(const std::string & n) { m_name = n; }

            const ImVec2 & position() const { return m_position; }
            void position(const ImVec2 & n) { m_position = n; }

            const ImVec2 & size() const { return m_size; }
            void size(const ImVec2 & n) { m_size = n; }

            const float & alpha() const { return m_alpha; }
            void alpha(const float & n) { m_alpha = n; }

            const ImGuiWindowFlags & flags() const { return m_flags; }
            void flags(const ImGuiWindowFlags & n) { m_flags = n; }

        protected:
            std::string         m_name;
            ImVec2              m_position;
            ImVec2              m_size;
            float               m_alpha;
            ImGuiWindowFlags    m_flags;

        };


    }
