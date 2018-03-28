#pragma once

namespace blam
{
	bool patch_memory(void *const address, const void *const data, const long element_count, const long element_size = sizeof(char));
	bool patch_call(void *const address, void *const function);
	bool patch_jump(void *const address, void *const function, bool equal = false);

	bool detour_function(void** source_pointer, void* hook_pointer);
	template<typename A, typename B>
	bool detour_function(A source_pointer, B hook_pointer)
	{
		return detour_function((void**)&(PVOID&)game_tick, (void*)game_tick_hook);
	}
}