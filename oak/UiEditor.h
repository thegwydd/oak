#pragma once
#include "UiContainer.h"
#include "GraphNode.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    class UiEditor : public UiContainer
        {
        public:
            using Ptr = std::shared_ptr<UiEditor>;

        public:
            UiEditor(Core * core, const std::string & _name);
            ~UiEditor();

        public:
            virtual bool Initialize() override { return true; };
            virtual void Deinitialize() override {};
            virtual void Render();

        };


    }
