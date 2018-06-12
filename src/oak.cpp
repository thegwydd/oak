#include "stdafx.h"
#include "oak.h"
#include "core.h"


extern "C"
    {
    //////////////////////////////////////////////////////////////////////////
    OAK_API orxSTATUS /*orxFASTCALL*/ oak_init()
        {
        return oak::Core::Get().Init();
        }

    //////////////////////////////////////////////////////////////////////////
    OAK_API orxSTATUS /*orxFASTCALL*/ oak_run()
        {
        return oak::Core::Get().Run();
        }

    //////////////////////////////////////////////////////////////////////////
    OAK_API void /*orxFASTCALL*/ oak_exit()
        {
        oak::Core::Get().Exit();
        }
    }
