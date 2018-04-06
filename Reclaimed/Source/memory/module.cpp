#include "input\input.hpp"
#include "memory\module.hpp"

namespace blam
{
	extern "C" int __declspec(dllexport) __cdecl module_get_version()
	{
		return 0;
	}

	bool map_file_validation(void *)
	{
		return true;
	}

	inline BOOL shell_dispose_internal()
	{
		return static_cast<BOOL(*)()>(module_get_address(0x1140))();
	}

	BOOL shell_dispose()
	{
		return shell_dispose_internal();
	}

	byte *init_hf2p_system() { return nullptr; }
	int sub_6DA2A0() { return 0; }
	int sub_6DAD00(float, float) { return 0; }
	int sub_712850() { return 0; }
	int sub_72F270() { return 0; }
	char *sub_7313D0() { return nullptr; }
	char *sub_756200() { return nullptr; }
	void __stdcall sub_759BB0(void *) {}
	char *sub_7616C0() { return nullptr; }
	int sub_769410() { return 0; }
	int sub_7738C0() { return 0; }
	int __stdcall sub_7B2570(dword *) { return 0; }
	dword *sub_7BF8B0() { return nullptr; }
	char *__stdcall sub_8F25C0(int) { return nullptr; }
	int sub_A17460() { return 0; }
	int sub_A174C0() { return 0; }
	int sub_A17520() { return 0; }
	int sub_A17580() { return 0; }
	void *__cdecl sub_B8EC1B(size_t) { return nullptr; }

	inline void *game_tick_internal()
	{
		return static_cast<void *(*)()>(module_get_address(0xCF170))();
	}

	inline bool __stdcall map_load(long map_id, long campaign_id, const char *map_name)
	{
		return static_cast<bool(__stdcall *)(long, long, const char *)>(module_get_address(0x7EF40))(map_id, campaign_id, map_name);
	}

	void *game_tick()
	{
		if (input_key_is_down(_key_escape, _input_type_special))
			map_load(320, -1, "maps\\guardian.map"); // not working atm...

		return game_tick_internal();
	}

	bool module_initialize(HMODULE module)
	{
		SetProcessDPIAware();
		DisableThreadLibraryCalls(module);

		module_unprotect_memory();

		// temporary title change *patch*
		if (!module_patch_memory(0xDA6528, "H3Reclaimed", 11)) return false;

		// disable tag checksums
		if (!module_patch_call(0x8392D, map_file_validation)) return false;
		if (!module_patch_memory(0x83CC1, "\x90\x90", 2)) return false;
		if (!module_patch_memory(0x847A9, "\x90\x90", 2)) return false;

		// disable preferences checksum
		if (!module_patch_memory(0x9FAF8, "\x90\x90", 2)) return false;

		// hook the game_disposing function
		if (!module_patch_call(0x150F, shell_dispose)) return false;

		// disable hf2p/scaleform (crappily)
		if (!module_patch_call(0x2BD12B, init_hf2p_system)) return false;
		if (!module_patch_call(0x2BD117, sub_A174C0)) return false;
		if (!module_patch_call(0x2BD11C, sub_A17520)) return false;
		if (!module_patch_call(0x2BD1A4, sub_7313D0)) return false;
		if (!module_patch_call(0x2BD1C2, sub_B8EC1B)) return false;
		if (!module_patch_call(0x2BD1DA, sub_7B2570)) return false;
		if (!module_patch_call(0x2BD1EF, sub_6DA2A0)) return false;
		if (!module_patch_call(0x2BD1FF, sub_6DAD00)) return false;
		if (!module_patch_call(0x2BD213, sub_756200)) return false;
		if (!module_patch_call(0x2BD218, sub_769410)) return false;
		if (!module_patch_call(0x2BD24A, sub_8F25C0)) return false;
		if (!module_patch_call(0x2BD251, sub_B8EC1B)) return false;
		if (!module_patch_call(0x2BD290, sub_7BF8B0)) return false;
		if (!module_patch_call(0x2BD2B3, sub_712850)) return false;
		if (!module_patch_call(0x2BD2DB, sub_7616C0)) return false;
		if (!module_patch_call(0x2BD2E0, sub_7738C0)) return false;
		if (!module_patch_call(0x2BD312, sub_8F25C0)) return false;
		if (!module_patch_call(0x2BD317, sub_72F270)) return false;
		if (!module_patch_call(0x2BD349, sub_8F25C0)) return false;
		if (!module_patch_call(0x2BD34E, sub_759BB0)) return false;

		// game tick
		if (!module_patch_call(0x95EBE, game_tick)) return false;
		if (!module_patch_call(0x97083, game_tick)) return false;
		if (!module_patch_call(0x97094, game_tick)) return false;
		if (!module_patch_call(0x971B0, game_tick)) return false;

		return true;
	}

	bool module_dispose()
	{
		return true;
	}

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

	void module_unprotect_memory()
	{
		MEMORY_BASIC_INFORMATION MemInfo;

		for (auto offset = 0; VirtualQuery(module_get_address(offset), &MemInfo, sizeof(MEMORY_BASIC_INFORMATION));)
		{
			offset += MemInfo.RegionSize;

			if (MemInfo.Protect == PAGE_EXECUTE_READ)
				VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize, PAGE_EXECUTE_READWRITE, &MemInfo.Protect);
		}
	}

	bool module_patch_memory(const dword offset, const void *const data, const long element_count, const long element_size)
	{
		dword temp;
		auto length = element_count * element_size;
		auto address = module_get_address(offset);

		if (!VirtualProtect(address, length, PAGE_READWRITE, &temp))
			return false;

		memcpy(address, data, length);
		VirtualProtect(address, length, temp, &temp);

		return true;
	}

	bool module_patch_call(const dword offset, void *const function)
	{
		dword temp;

		auto address = module_get_address(offset);

		if (!VirtualProtect(address, 5, PAGE_READWRITE, &temp))
			return false;

		byte temp_jmp[5] = { 0xE8, 0x90, 0x90, 0x90, 0x90 };
		dword jmp_size = ((dword)function - (dword)address - 5);

		memcpy(&temp_jmp[1], &jmp_size, 4);
		memcpy(address, temp_jmp, 5);
		VirtualProtect(address, 5, temp, &temp);

		return true;
	}

	bool module_patch_jump(const dword offset, void *const function, bool equal)
	{
		dword temp;
		dword patch_size = equal ? 6 : 5;

		auto address = module_get_address(offset);

		if (!VirtualProtect(address, patch_size, PAGE_READWRITE, &temp))
			return false;

		dword jmp_size = ((dword)function - (dword)address - patch_size);

		if (equal)
		{
			byte temp_je[6] = { 0x0F, 0x84, 0x90, 0x90, 0x90, 0x90 };

			memcpy(&temp_je[2], &jmp_size, 4);
			memcpy(address, temp_je, 6);
		}
		else
		{
			byte temp_jmp[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };

			memcpy(&temp_jmp[1], &jmp_size, 4);
			memcpy(address, temp_jmp, 5);
		}

		VirtualProtect(address, patch_size, temp, &temp);

		return true;
	}
}