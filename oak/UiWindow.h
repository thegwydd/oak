#pragma once
#include "UiContainer.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    class UiWindow : public UiContainer
        {
        public:
            UiWindow(Core * core, const std::string & _name);
            ~UiWindow();

        public:
            virtual void Render() override;

        };


    }
