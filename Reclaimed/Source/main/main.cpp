#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include "cseries\cseries.hpp"
#include "memory\patching.hpp"
#include "main.hpp"

namespace blam
{
	void *module_get_base_address()
	{
		static void *base_address = nullptr;

		if (base_address == nullptr)
		{
			auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());

			if (snapshot == INVALID_HANDLE_VALUE)
				return nullptr;

			MODULEENTRY32 module_entry;
			module_entry.dwSize = sizeof(MODULEENTRY32);

			auto result = Module32First(snapshot, &module_entry);
			CloseHandle(snapshot);

			base_address = (result != 0) ? (void *)module_entry.modBaseAddr : nullptr;
		}

		return base_address;
	}

	const auto game_dispose = (void(*)())0x42E410;

	void game_disposing()
	{
		//
		// TODO: finalize/dispose/shutdown other things here
		//

		game_dispose();
	}

	void patches_apply_core()
	{
		auto module_base_address = (char *)module_get_base_address();

		// disable tag checksums
		patch_memory(module_base_address + 0x83934, "\xEB", 1);
		patch_memory(module_base_address + 0x83CC1, "\x90\x90", 2);
		patch_memory(module_base_address + 0x847AB, "\x90\x90", 2);

		// disable preferences.dat checksums
		patch_memory(module_base_address + 0x9FAF8, "\x90\x90\x90\x90\x90\x90", 6);

		// disable --account args
		patch_memory(module_base_address + 0x36499E, "\xEB\x0E", 2);
		patch_memory(module_base_address + 0x364925, "\xEB\x03", 2);

		// hook the game_disposing function
		patch_call(module_base_address + 0x150F, game_disposing);
	}
}

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