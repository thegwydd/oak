#include "stdafx.h"
#include "EditorFatory.h"
#include "SelectorWindow.h"

namespace oak
    {

    //////////////////////////////////////////////////////////////////////////
    UiEditor::Ptr EditorFactory::CreateEditor(Core * core, EditorType type)
        {
        UiEditor::Ptr ret = nullptr;

        switch (type)
            {
            case EditorType::Selector:
                ret = std::make_shared<SelectorWindow>(core);
                break;
            case EditorType::iOS:
                break;
            case EditorType::Android:
                break;
            case EditorType::Resource:
                break;
            case EditorType::Config:
                break;
            case EditorType::Console:
                break;
            case EditorType::MainClock:
                break;
            case EditorType::Plugin:
                break;
            case EditorType::Display:
                break;
            case EditorType::Render:
                break;
            case EditorType::Mouse:
                break;
            case EditorType::Input:
                break;
            case EditorType::InputSet:
                break;
            case EditorType::Locale:
                break;
            case EditorType::Language:
                break;
            case EditorType::Physics:
                break;
            case EditorType::SoundSystem:
                break;
            case EditorType::Screenshot:
                break;
            case EditorType::Param:
                break;
            case EditorType::Object:
                break;
            case EditorType::Graphic:
                break;
            case EditorType::Text:
                break;
            case EditorType::Font:
                break;
            case EditorType::Body:
                break;
            case EditorType::BodyPartSphere:
                break;
            case EditorType::BodyPartBox:
                break;
            case EditorType::BodyPartMesh:
                break;
            case EditorType::RevoluteJoint:
                break;
            case EditorType::PrismaticJoint:
                break;
            case EditorType::SpringJoint:
                break;
            case EditorType::RopeJoint:
                break;
            case EditorType::PulleyJoint:
                break;
            case EditorType::SuspensionJoint:
                break;
            case EditorType::WeldJoint:
                break;
            case EditorType::FrictionJoint:
                break;
            case EditorType::GearJoint:
                break;
            case EditorType::AnimationSet:
                break;
            case EditorType::Animation:
                break;
            case EditorType::Animation1:
                break;
            case EditorType::Viewport:
                break;
            case EditorType::Camera:
                break;
            case EditorType::Clock:
                break;
            case EditorType::Sound:
                break;
            case EditorType::FX:
                break;
            case EditorType::FXSlot:
                break;
            case EditorType::Spawner:
                break;
            case EditorType::Shader:
                break;
            case EditorType::TimeLineTrack:
                break;

            default:
                break;

            }

        return ret;
        }




    }