#pragma once

#include "ui_component.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    class config_file_tree : public ui_component
        {
        public:
            config_file_tree();
            ~config_file_tree();

        public:
            virtual void render() override;


        };

    }
