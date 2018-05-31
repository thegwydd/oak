#pragma once

#include "UiWindow.h"
#include "SelectorWindow.h"
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
            void RenderLeftPane();

        protected:
            SelectorWindow      m_selector;
            ViewportControl     m_viewport;

            float               m_LeftPaneWidth = 300;
            float               m_LeftPaneHeight = -1;

            float               m_SplitterSize = 8.0f;

        };



    }
