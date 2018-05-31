#pragma once

#include "UiEditor.h"
#include "ResourceTree.h"
#include "InspectorControl.h"
#include "ViewportControl.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    class SelectorWindow : public UiEditor
        {
        public:
            SelectorWindow(Core * core);
            ~SelectorWindow();

            virtual bool Initialize() override;
            virtual void Deinitialize() override;
            virtual void Render() override;

        protected:
            ResourceTree        m_resource_tree;
            InspectorControl    m_inspector;

            float               m_ResourceTreeHeight = 500;
            float               m_SplitterSize = 8.0f;

        };



    }
