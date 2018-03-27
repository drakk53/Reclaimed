#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

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

		MessageBox(nullptr, "SHUTTING DOWN!!!", "", MB_OK);
		game_dispose();
	}

	bool apply_core_patches()
	{
		auto module_base_address = (char *)module_get_base_address();

		// disable tag checksums
		if (!patch_memory(module_base_address + 0x83934, "\xEB", 1)) return false;
		if (!patch_memory(module_base_address + 0x83CC1, "\x90\x90", 2)) return false;
		if (!patch_memory(module_base_address + 0x847AB, "\x90\x90", 2)) return false;

		// disable preferences.dat checksums
		if (!patch_memory(module_base_address + 0x9FAF8, "\x90\x90\x90\x90\x90\x90", 6)) return false;

		// disable --account args
		if (!patch_memory(module_base_address + 0x6499E, "\xEB\x0E", 2)) return false;
		if (!patch_memory(module_base_address + 0x364925, "\xEB\x03", 2)) return false;

		// hook the game_disposing function
		if (!patch_call(module_base_address + 0x150F, game_disposing)) return false;

		return true;
	}

	bool game_attach()
	{
		// disable dpi scaling
		SetProcessDPIAware();

		// apply patches
		if (!apply_core_patches()) return false;

		return true;
	}

	bool game_detach()
	{
		return true;
	}
}

extern "C" bool __declspec(dllexport) __cdecl get_process_memory_info(HANDLE Process, PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb)
{
	return K32GetProcessMemoryInfo(Process, ppsmemCounters, cb);
}

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		return blam::game_attach();

	case DLL_PROCESS_DETACH:
		return blam::game_detach();

	default:
		break;
	}

	return TRUE;
}