#pragma once

namespace oak
    {

    class Core;
    //////////////////////////////////////////////////////////////////////////
    // base class for all ui components
    class UiControl
        {
        public:
            using Ptr = std::shared_ptr<UiControl>;

            UiControl(Core * core, const std::string & _name);
            virtual ~UiControl();

        public:
            virtual bool Initialize() = 0;
            virtual void Deinitialize() = 0;
            virtual void Render() = 0;

        public:
            const std::string & Name() const { return m_name; }
            void Name(const std::string & n) { m_name = n; }

            const ImVec2 & Position() const { return m_position; }
            void Position(const ImVec2 & n) { m_position = n; }

            const ImVec2 & Size() const { return m_size; }
            void Size(const ImVec2 & n) { m_size = n; }

            const float & Alpha() const { return m_alpha; }
            void Alpha(const float & n) { m_alpha = n; }

            const ImGuiWindowFlags & Flags() const { return m_flags; }
            void Flags(const ImGuiWindowFlags & n) { m_flags = n; }

        protected:
            Core *              m_core = nullptr;
            std::string         m_name;
            ImVec2              m_position;
            ImVec2              m_size;
            float               m_alpha;
            ImGuiWindowFlags    m_flags;

        };

    using UiControls = std::vector<UiControl::Ptr>;


    }
