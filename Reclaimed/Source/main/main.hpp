#pragma once

namespace blam
{
	// gets the base address of the game module
	void *module_get_address(const dword offset = 0);

	// applies the core/necessary patches to run the game
	bool apply_core_patches();
}