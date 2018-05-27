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

        protected:
            std::string     m_name;

        };


    }
