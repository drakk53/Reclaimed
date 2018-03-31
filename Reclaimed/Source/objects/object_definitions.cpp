#include "object_definitions.hpp"

namespace blam
{
	const tag_enum_option object_type_enum_options[] =
	{
		{ "none", _object_type_none },
		{ "biped", _object_type_biped },
		{ "vehicle", _object_type_vehicle },
		{ "weapon", _object_type_weapon },
		{ "armor", _object_type_armor },
		{ "equipment", _object_type_equipment },
		{ "arg_device", _object_type_arg_device },
		{ "terminal", _object_type_terminal },
		{ "projectile", _object_type_projectile },
		{ "scenery", _object_type_scenery },
		{ "machine", _object_type_machine },
		{ "control", _object_type_control },
		{ "sound_scenery", _object_type_sound_scenery },
		{ "crate", _object_type_crate },
		{ "creature", _object_type_creature },
		{ "giant", _object_type_giant },
		{ "effect_scenery", _object_type_effect_scenery },
		{ nullptr, -1 }
	};
	const tag_enum_definition object_type_enum =
	{
		"object_type",
		_tag_enum_short,
		object_type_enum_options
	};

	const tag_enum_option object_flags_enum_options[] =
	{
		{ "does_not_cast_shadow", _object_does_not_cast_shadow_bit },
		{ "search_cardinal_direction_maps", _object_search_cardinal_direction_maps_bit },
		{ "flags", _object_flags_bit2 },
		{ "not_a_pathfinding_obstacle", _object_not_a_pathfinding_obstacle_bit },
		{ "extension_of_parent", _object_extension_of_parent_bit },
		{ "does_not_cause_collision_damage", _object_does_not_cause_collision_damage_bit },
		{ "early_mover", _object_early_mover_bit },
		{ "early_mover_localized_physics", _object_early_mover_localized_physics_bit },
		{ "use_static_massive_lightmap_sample", _object_use_static_massive_lightmap_sample_bit },
		{ "object_scales_attachments", _object_object_scales_attachments_bit },
		{ "inherits_players_appearance", _object_inherits_players_appearance_bit },
		{ "dead_bipeds_cant_localize", _object_dead_bipeds_cant_localize_bit },
		{ "attach_to_clusters_by_dynamic_sphere", _object_attach_to_clusters_by_dynamic_sphere_bit },
		{ "effects_do_not_spawn_objects_in_multiplayer", _object_effects_do_not_spawn_objects_in_multiplayer_bit },
		{ nullptr, -1 }
	};
	const tag_enum_definition object_flags_enum =
	{
		"object_flags",
		_tag_enum_word,
		object_flags_enum_options
	};

	const tag_field_definition object_definition_struct_fields[] =
	{
		{ _field_short_enum, "object_type", &object_type_enum },
		{ _field_word_flags, "object_flags", &object_flags_enum },
		/* TODO: define more fields... */
	};
	const tag_struct_definition object_definition_struct =
	{
		"object_definition",
		sizeof(object_definition),
		object_definition_struct_fields
	};
}