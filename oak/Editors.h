#pragma once

#include "EnumUtility.h"

namespace oak
    {

    enum class EditorType
        {
        Selector,

        // main settings
        iOS,
        Android,
        Resource,
        Config,
        Console,
        MainClock,
        Plugin,
        Display,
        Render,
        Mouse,
        Input,
        InputSet,
        Locale,
        Language,
        Physics,
        SoundSystem,
        Screenshot,
        Param,

        // game stuff
        Object,
        Graphic,
        Text,
        Font,
        Body,
        BodyPartSphere,
        BodyPartBox,
        BodyPartMesh,
        RevoluteJoint,
        PrismaticJoint,
        SpringJoint,
        RopeJoint,
        PulleyJoint,
        SuspensionJoint,
        WeldJoint,
        FrictionJoint,
        GearJoint,
        AnimationSet,
        Animation,
        Animation1,
        Viewport,
        Camera,
        Clock,
        Sound,
        FX,
        FXSlot,
        Spawner,
        Shader,
        TimeLineTrack,

        // end of enum
        EndOfEnum,
        };

    DECLARE_ENUM_ENTRY(EditorType);



    }
