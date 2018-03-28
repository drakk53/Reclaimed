#pragma once

#include "cseries\cseries.hpp"

namespace blam
{
	void unprotect_memory();
	void *module_get_virtual_address(const dword offset);
	void *module_get_address(const dword offset);
}