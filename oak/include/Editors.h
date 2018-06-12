#pragma once

#include "EnumUtility.h"

namespace oak
    {

    enum class EditorType
        {
        Selector,

        // main settings
        MainSettings,
        Inputs,
        Localization,

        // game stuff
        Object,
        Graphic,
        Text,
        Font,
        Body,
        BodyPart,
        Joint,
        Animation,
        Viewport,
        Camera,
        Clock,
        Sound,
        Effect,
        Spawner,
        Shader,
        TimeLineTrack,

        // end of enum
        EndOfEnum,
        };

    DECLARE_ENUM_ENTRY(EditorType);



    }
