// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "ErrorCodes.h"

void *hModule{ nullptr };

BOOL APIENTRY DllMain( HMODULE hMod,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		hModule = reinterpret_cast<void *>(hMod);

		if (!CreateUserErrorMessageTable(hMod, static_cast<unsigned int>(specFuncs::errors.size()), specFuncs::errors.data()))
		{
			return FALSE;
		}

		specFuncs::initializeUserEfi(hMod);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		hModule = nullptr;
        break;
    }
    return TRUE;
}

