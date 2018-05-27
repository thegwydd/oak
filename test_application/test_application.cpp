// oak.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "application.h"

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#elif defined(__cplusplus)
# define UNUSED(x)
#else
# define UNUSED(x) x
#endif


orxSTATUS orxFASTCALL init() { return application::get().init(); }
orxSTATUS orxFASTCALL run() { return application::get().run(); }
void  orxFASTCALL exit() { return application::get().exit(); }

#ifndef __orxMSVC__
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
    {
    orx_Execute(argc, argv, init, run, exit);
    return EXIT_SUCCESS;
    }
#else  // __orxMSVC__
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
    UNUSED(hInstance);
    UNUSED(hPrevInstance);
    UNUSED(lpCmdLine);
    UNUSED(nCmdShow);

    orx_WinExecute(init, run, exit);

    // Done!
    return EXIT_SUCCESS;
    }
#endif // __orxMSVC__
