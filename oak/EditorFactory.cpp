#include "stdafx.h"
#include "EditorFactory.h"
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
            case EditorType::MainSettings:
                break;
            case EditorType::Localization:
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
            case EditorType::BodyPart:
                break;
            case EditorType::Joint:
                break;
            case EditorType::Animation:
                break;
            case EditorType::Viewport:
                break;
            case EditorType::Camera:
                break;
            case EditorType::Clock:
                break;
            case EditorType::Sound:
                break;
            case EditorType::Effect:
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