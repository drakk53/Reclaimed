#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "cseries\cseries.hpp"
#include "memory\patching.hpp"

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}