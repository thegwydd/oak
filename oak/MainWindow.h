#pragma once

#include "UiWindow.h"
#include "ResourceTree.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    class MainWindow : public UiWindow
        {
        public:
            MainWindow(Core * core, const std::string & _name);
            ~MainWindow();

            virtual void Render() override;

        protected:
            ResourceTree    m_resource_tree;

        };



    }
