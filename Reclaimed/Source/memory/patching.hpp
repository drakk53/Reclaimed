#pragma once

namespace blam
{
	bool patch_memory(void *const address, const void *const data, const long element_count, const long element_size = sizeof(char));
	bool patch_call(void *const address, void *const function);
	bool patch_jump(void *const address, void *const function, bool equal = false);
}