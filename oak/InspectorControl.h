#pragma once

#include "UiWindow.h"
#include "ResourceTree.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    class InspectorControl : public UiControl
        {
        public:
            InspectorControl(Core * core);
            ~InspectorControl();

            virtual bool Initialize() override;
            virtual void Deinitialize() override;
            virtual void Render() override;

        };



    }
