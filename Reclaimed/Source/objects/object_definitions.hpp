#pragma once

#include "cseries\cseries.hpp"
#include "..\tag_files\tag_groups.hpp"

namespace blam
{
	enum
	{
		_object_group_tag = 'obje'
	};

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
}