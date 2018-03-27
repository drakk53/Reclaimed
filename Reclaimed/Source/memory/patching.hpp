#pragma once

namespace blam
{
	bool patch_memory(void *const address, const char *const data);
	bool patch_call(void *const address, void *const function);
	bool patch_jump(void *const address, void *const function, bool equal = false);
}