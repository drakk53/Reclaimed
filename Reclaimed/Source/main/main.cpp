#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "cseries\cseries.hpp"
#include "memory\data.hpp"
#include "memory\module.hpp"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		if (!blam::module_initialize(module))
			return FALSE;
		return true;

	case DLL_PROCESS_DETACH:
		if (!blam::module_dispose())
			return FALSE;
		return TRUE;

	default:
		break;
	}

	return TRUE;
}