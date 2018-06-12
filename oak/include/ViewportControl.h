#pragma once

#include "UiWindow.h"
#include "ResourceTree.h"

namespace oak
    {


    //////////////////////////////////////////////////////////////////////////
    class ViewportControl : public UiControl
        {
        public:
            ViewportControl(Core * core);
            ~ViewportControl();

            virtual bool Initialize() override;
            virtual void Deinitialize() override;
            virtual void Render() override;

        protected:
            orxVIEWPORT *   m_viewport;
            orxCAMERA *     m_camera;

        };



    }
