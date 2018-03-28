#include "memory.hpp"
#include <Windows.h>
#include <TlHelp32.h>

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

	void *module_get_virtual_address(const dword offset)
	{
		auto address = dword((char*)(offset)-0x400000);
		return module_get_address(address);
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

}