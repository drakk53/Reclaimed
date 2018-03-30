#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include "cseries\cseries.hpp"
#include "memory\patching.hpp"
#include "memory\memory.hpp"
#include "main.hpp"

namespace blam
{
	bool map_file_validation(void *)
	{
		return true;
	}

	inline void game_dispose()
	{
		return static_cast<void(*)()>(module_get_address(0x1140))();
	}

	void game_disposing()
	{
		//
		// TODO: finalize/dispose/shutdown other things here
		//

		game_dispose();
	}

	bool apply_core_patches()
	{
		// disable tag checksums
		if (patch_call(module_get_address(0x8392D), map_file_validation)) return true;
		if (patch_memory(module_get_address(0x83CC1), "\x90\x90", 2)) return true;
		if (patch_memory(module_get_address(0x847A9), "\x90\x90", 2)) return true;

		// disable preferences checksum
		if (patch_memory(module_get_address(0x9FAF8), "\x90\x90", 2)) return true;

		// hook the game_disposing function
		if (patch_call(module_get_address(0x150F), game_disposing)) return true;

		return false;
	}

	bool game_attach(HMODULE module)
	{
		SetProcessDPIAware();
		DisableThreadLibraryCalls(module);

		unprotect_memory();

		if (apply_core_patches()) return true;

		return false;
	}

	bool game_detach()
	{
		return false;
	}
}

// This is required to meet the modified executable DLLImport
extern "C" __declspec(dllexport) void ms30(void) { }

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		if (blam::game_attach(module))
			return FALSE;
		return true;

	case DLL_PROCESS_DETACH:
		if (blam::game_detach())
			return FALSE;
		return TRUE;

	default:
		break;
	}

	return TRUE;
}