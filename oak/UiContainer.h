#pragma once
#include "UiControl.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    class UiContainer : public UiControl
        {
        public:
            UiContainer(Core * core, const std::string & _name);
            ~UiContainer();

        public:
            virtual void Render() override;
            UiControls & Controls() { return m_controls; }

        protected:
            UiControls    m_controls;

        };


    }
