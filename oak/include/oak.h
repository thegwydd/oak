#pragma once

#ifdef _OAK_DLL
#define OAK_API __declspec(dllexport)
#else
#define OAK_API __declspec(dllimport)
#endif

extern "C"
    {
    OAK_API orxSTATUS /*orxFASTCALL*/ oak_init();
    OAK_API orxSTATUS /*orxFASTCALL*/ oak_run();
    OAK_API void /*orxFASTCALL*/ oak_exit();
    }
