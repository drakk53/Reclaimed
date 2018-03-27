#include <cstring>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "cseries\cseries.hpp"
#include "memory\patching.hpp"

namespace blam
{
	bool patch_memory(void *const address, const char *const data)
	{
		dword temp;
		auto length = strlen(data);

		if (!VirtualProtect(address, length, PAGE_READWRITE, &temp))
			return false;

		memcpy(address, data, length);
		VirtualProtect(address, length, temp, &temp);

		return true;
	}

	bool patch_call(void *const address, void *const function)
	{
		dword temp;

		if (!VirtualProtect(address, 5, PAGE_READWRITE, &temp))
			return false;

		byte temp_jmp[5] = { 0xE8, 0x90, 0x90, 0x90, 0x90 };
		dword jmp_size = ((dword)function - (dword)address - 5);

		memcpy(&temp_jmp[1], &jmp_size, 4);
		memcpy(address, temp_jmp, 5);
		VirtualProtect(address, 5, temp, &temp);

		return true;
	}

	bool patch_jump(void *const address, void *const function, bool equal)
	{
		dword temp;
		dword patch_size = equal ? 6 : 5;

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