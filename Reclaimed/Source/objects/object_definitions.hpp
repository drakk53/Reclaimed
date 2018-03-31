#pragma once

#include "cseries\cseries.hpp"
#include "tag_files\tag_groups.hpp"
#include "tag_files\tag_definitions.hpp"

#include "object_types.hpp"

namespace blam
{
	enum : tag { _object_group_tag = 'obje' };

	enum : word_flags /* object flags */
	{
		_object_does_not_cast_shadow_bit,
		_object_search_cardinal_direction_maps_bit,
		_object_flags_bit2,
		_object_not_a_pathfinding_obstacle_bit,
		_object_extension_of_parent_bit,
		_object_does_not_cause_collision_damage_bit,
		_object_early_mover_bit,
		_object_early_mover_localized_physics_bit,
		_object_use_static_massive_lightmap_sample_bit,
		_object_object_scales_attachments_bit,
		_object_inherits_players_appearance_bit,
		_object_dead_bipeds_cant_localize_bit,
		_object_attach_to_clusters_by_dynamic_sphere_bit,
		_object_effects_do_not_spawn_objects_in_multiplayer_bit
	};

	enum : short_enum /* object lightmap shadow modes */
	{
		_object_lightmap_shadow_mode_default,
		_object_lightmap_shadow_mode_never,
		_object_lightmap_shadow_mode_always,
		_object_lightmap_shadow_mode_blur
	};

	enum : char_enum /* object sweetener sizes */
	{
		_object_sweetener_size_small,
		_object_sweetener_size_medium,
		_object_sweetener_size_large
	};

	enum : char_enum /* object water densities */
	{
		_object_water_density_default,
		_object_water_density_least,
		_object_water_density_some,
		_object_water_density_equal,
		_object_water_density_more,
		_object_water_density_more_still,
		_object_water_density_lots_more
	};

	struct object_early_mover_properties
	{
		string_id name;
		real_bounds x_bounds;
		real_bounds y_bounds;
		real_bounds z_bounds;
		real_euler_angles3d angles;
	};
	static_assert(sizeof(object_early_mover_properties) == 0x28);

	struct object_definition
	{
		short_enum object_type;
		word_flags object_flags;
		real bounding_radius;
		real_point3d bounding_offset;
		real acceleration_scale;
		short_enum lightmap_shadow_mode;
		char_enum sweetener_size;
		char_enum water_density;
		long_flags runtime_flags;
		real dynamic_light_sphere_radius;
		real_point3d dynamic_light_sphere_offset;
		string_id default_model_variant;
		tag_reference model;
		tag_reference collision_damage;
		tag_block early_mover_properties;
		tag_reference creation_effect;
		tag_reference material_effects;
		tag_reference armor_sounds;
		tag_reference melee_impact;
		tag_block ai_properties;
		tag_block functions;
		short hud_text_message_index;
		short : 16;
		tag_block attachments;
		tag_block widgets;
		tag_block change_colors;
		tag_block node_maps;
		tag_block multiplayer_object_properties;
		tag_reference simulation_interpolation;
		tag_block reviving_equipment;
		tag_block model_object_data;
	};
	static_assert(sizeof(object_definition) == 0x120);
	extern const tag_struct_definition object_definition_struct;
}