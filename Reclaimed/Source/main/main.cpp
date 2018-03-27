#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include "cseries\cseries.hpp"
#include "memory\patching.hpp"
#include "main.hpp"

namespace blam
{
	void *module_get_address(const dword offset)
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

		return (char *)base_address + offset;
	}

	void unprotect_memory()
	{
		MEMORY_BASIC_INFORMATION MemInfo;

		for (auto offset = 0; VirtualQuery(module_get_address(offset), &MemInfo, sizeof(MEMORY_BASIC_INFORMATION));)
		{
			offset += MemInfo.RegionSize;

			if (MemInfo.Protect == PAGE_EXECUTE_READ)
				VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize, PAGE_EXECUTE_READWRITE, &MemInfo.Protect);
		}
	}

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
		if (!patch_call(module_get_address(0x8392D), map_file_validation)) return false;

		// disable --account args
		if (!patch_memory(module_get_address(0x36499E), "\xEB\x0E", 2)) return false;
		if (!patch_memory(module_get_address(0x36492B), "\x00", 1)) return false;

		// hook the game_disposing function
		if (!patch_call(module_get_address(0x150F), game_disposing)) return false;

		return true;
	}

	bool game_attach(HMODULE module)
	{
		SetProcessDPIAware();
		DisableThreadLibraryCalls(module);

		unprotect_memory();

		if (!apply_core_patches()) return false;

		return true;
	}

	bool game_detach()
	{
		return true;
	}
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		if (!blam::game_attach(module))
			return FALSE;
		return true;

	case DLL_PROCESS_DETACH:
		if (!blam::game_detach())
			return FALSE;
		return TRUE;

	default:
		break;
	}

	return TRUE;
}