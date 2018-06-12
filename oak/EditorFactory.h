#pragma once

#include "Editors.h"
#include "UiEditor.h"

namespace oak
    {

    class Core;
    //////////////////////////////////////////////////////////////////////////
    class EditorFactory
        {
        public:
            static UiEditor::Ptr CreateEditor(Core * core, EditorType type);
        };



    }
