#pragma once

#include "UiWindow.h"
#include "ResourceTree.h"
#include "InspectorControl.h"
#include "ViewportControl.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    class MainWindow : public UiWindow
        {
        public:
            MainWindow(Core * core, const std::string & _name);
            ~MainWindow();

            virtual bool Initialize() override;
            virtual void Deinitialize() override;
            virtual void Render() override;

        protected:
            ResourceTree        m_resource_tree;
            InspectorControl    m_inspector;
            ViewportControl     m_viewport;
        };



    }
