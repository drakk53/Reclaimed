#include "memory\module.hpp"
#include "preferences.hpp"

namespace blam
{
	void preferences_load()
	{
		static void(*preferences_load_internal)() = nullptr;

		if (preferences_load_internal == nullptr)
			preferences_load_internal = static_cast<void(*)()>(module_get_address(0x9F930));

		preferences_load_internal();
	}

	bool preferences_initialize()
	{
		// hook the preferences loading function
		if (!module_patch_call(0x9B3C8, preferences_load))
			return false;

		// disable preferences checksum
		if (!module_patch_memory(0x9FAF8, "\x90\x90", 2))
			return false;

		return true;
	}
}