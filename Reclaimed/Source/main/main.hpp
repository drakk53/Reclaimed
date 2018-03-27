#pragma once

namespace blam
{
	// gets the base address of the game module
	void *module_get_base_address();

	// applies the core/necessary patches to run the game
	void patches_apply_core();
}