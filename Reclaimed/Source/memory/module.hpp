#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Psapi.h>

#include "cseries\cseries.hpp"

namespace blam
{
	// initializes the game module
	bool module_initialize(HMODULE module);

	// disposes the game module
	bool module_dispose();

	// unprotects the memory of the game module
	void module_unprotect_memory();

	// gets the base address of the game module
	void *module_get_address(const dword offset = 0);

	// gets the thread local storage address of the game module
	void *module_get_tls_address(const dword offset = 0);

	// patches an address in the game module
	bool module_patch_memory(const dword offset, const void *const data, const long element_count, const long element_size = sizeof(char));

	// patches a function call in the game module
	bool module_patch_call(const dword offset, void *const function);

	// patches a function jump in the game module
	bool module_patch_jump(const dword offset, void *const function, bool equal = false);
}