#include "stdafx.h"
#include "Editors.h"

namespace oak
    {

    DEFINE_ENUM_ENTRY_BEGIN(EditorType)
    DEFINE_ENUM_ENTRY(EditorType::Selector, "Selector")

    DEFINE_ENUM_ENTRY(EditorType::MainSettings, "MainSettings")
    DEFINE_ENUM_ENTRY(EditorType::Inputs, "Inputs")
    DEFINE_ENUM_ENTRY(EditorType::Localization, "Localization")

    DEFINE_ENUM_ENTRY(EditorType::Object, "Object")
    DEFINE_ENUM_ENTRY(EditorType::Graphic, "Graphic")
    DEFINE_ENUM_ENTRY(EditorType::Text, "Text")
    DEFINE_ENUM_ENTRY(EditorType::Font, "Font")
    DEFINE_ENUM_ENTRY(EditorType::Body, "Body")
    DEFINE_ENUM_ENTRY(EditorType::BodyPart, "BodyPart")
    DEFINE_ENUM_ENTRY(EditorType::Joint, "Joint")
    DEFINE_ENUM_ENTRY(EditorType::Animation, "Animation")
    DEFINE_ENUM_ENTRY(EditorType::Viewport, "Viewport")
    DEFINE_ENUM_ENTRY(EditorType::Camera, "Camera")
    DEFINE_ENUM_ENTRY(EditorType::Clock, "Clock")
    DEFINE_ENUM_ENTRY(EditorType::Sound, "Sound")
    DEFINE_ENUM_ENTRY(EditorType::Effect, "Effect")
    DEFINE_ENUM_ENTRY(EditorType::Spawner, "Spawner")
    DEFINE_ENUM_ENTRY(EditorType::Shader, "Shader")
    DEFINE_ENUM_ENTRY(EditorType::TimeLineTrack, "TimeLineTrack")
    DEFINE_ENUM_ENTRY_END()



    }
