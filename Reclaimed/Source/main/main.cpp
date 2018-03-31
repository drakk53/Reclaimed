#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h>

#include "cseries\cseries.hpp"
#include "memory\data.hpp"
#include "memory\patching.hpp"
#include "main.hpp"

namespace blam
{
	void *module_get_address(const dword offset)
	{
		static void *base_address = nullptr;

		if (base_address == nullptr)
		{
			MODULEINFO module_info = { 0 };

			auto result = GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module_info, sizeof(module_info));
			
			if (!result)
				return nullptr;

			base_address = module_info.lpBaseOfDll;
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

	inline bool map_load_internal(void *data)
	{
		return static_cast<bool(__thiscall *)(void *)>(module_get_address(0xAB190))(data);
	}

	inline BOOL shell_dispose_internal()
	{
		return static_cast<BOOL(*)()>(module_get_address(0x1140))();
	}

	BOOL shell_dispose()
	{
		//
		// TODO: finalize/dispose/shutdown other things here
		//

		return shell_dispose_internal();
	}

	byte *init_hf2p_system()
	{
		return nullptr;
	}

	int sub_6DA2A0()
	{
		return 0;
	}

	int sub_6DAD00(float, float)
	{
		return 0;
	}

	bool apply_core_patches()
	{
		// temporary title change *patch*
		if (!patch_memory(module_get_address(0xDA6528), "H3Reclaimed", 11)) return false;

		// disable tag checksums
		if (!patch_call(module_get_address(0x8392D), map_file_validation)) return false;
		if (!patch_memory(module_get_address(0x83CC1), "\x90\x90", 2)) return false;
		if (!patch_memory(module_get_address(0x847A9), "\x90\x90", 2)) return false;

		// disable preferences checksum
		if (!patch_memory(module_get_address(0x9FAF8), "\x90\x90", 2)) return false;
		
		// hook the game_disposing function
		if (!patch_call(module_get_address(0x150F), shell_dispose)) return false;

		// disable hf2p/scaleform (crappily)
		if (!patch_call(module_get_address(0x2BD12B), init_hf2p_system)) return false;
		if (!patch_call(module_get_address(0x2BD1EF), sub_6DA2A0)) return false;
		if (!patch_call(module_get_address(0x2BD1FF), sub_6DAD00)) return false;

		return true;
	}

	bool game_attach(HMODULE module)
	{
		SetProcessDPIAware();
		DisableThreadLibraryCalls(module);

		unprotect_memory();

		if (!apply_core_patches())
		{
			MessageBox(nullptr, "Failed to apply core patches.", "Error", MB_OK);
			return false;
		}

		return true;
	}

	bool game_detach()
	{
		return true;
	}
}

int __declspec(dllexport) get_mod_version()
{
	return 0;
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