#include "stdafx.h"
#include "oak.h"
#include "core.h"


extern "C"
    {
    //////////////////////////////////////////////////////////////////////////
    OAK_API orxSTATUS /*orxFASTCALL*/ oak_init()
        {
        return oak::core::get().init();
        }

    //////////////////////////////////////////////////////////////////////////
    OAK_API orxSTATUS /*orxFASTCALL*/ oak_run()
        {
        return oak::core::get().run();
        }

    //////////////////////////////////////////////////////////////////////////
    OAK_API void /*orxFASTCALL*/ oak_exit()
        {
        oak::core::get().exit();
        }
    }
