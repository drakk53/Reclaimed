#pragma once

#include "cseries\cseries.hpp"

namespace blam
{
	struct preferences_data
	{
		byte unknown0;
		bool is_dirty;
		word unknown2;
		dword unknown4;
		dword unknown8;
		dword unknownC;
		dword unknown10;
		dword unknown14;
		dword unknown18;
		dword unknown1C;
		dword unknown20;
		dword language;
		dword unknown28;
		dword unknown2C[2];
		dword minor_version;
		dword unknown38;
		dword unknown3C;
		dword unknown40;
		dword unknown44;
		dword unknown48;
		dword unknown4C;
		byte unknown50[0x4C];
		byte unknown98[0x78];
		dword unknown110;
		dword unknown114;
		byte unknown118[0x80];
		byte unknown19C[0x44];
		byte unknown1E0;
		dword unknown1E4;
		dword unknown1E8;
		byte unknown1EC[0x148];
		dword unknown330;
		byte unknown334[0x40];
		dword unknown398;
		dword unknown378;
		byte unknown380;
		byte unknown381[1135];
		dword unknown7F0;
		byte unknown7F4[0xFC];
		dword unknown8F0;
		byte unknown8F4[0xE19C];
		dword unknownEA90;
		dword unknownEA94;
		dword unknownEA98;
		byte unknownEA9C[0xFC];
		dword unknownEB98;
		byte unknownEB9C[0xE19C];
		dword unknown1CD38;
		dword unknown1CD3C;
		dword unknown1CD40;
		dword unknown1CD44;
		dword unknown1CD48;
		dword unknown1CD4C;
		dword unknown1CD50;
		dword unknown1CD54;
		byte unknown1CD58[0x1A55D];
		dword unknown372B8;
		dword display_subtitles;
		dword fullscreen;
		dword unknown372C4;
		dword contrast;
		dword brightness;
		dword unknown372D0;
		dword screen_resolution_width;
		dword screen_resolution_height;
		dword texture_resolution;
		dword shadow_quality;
		dword texture_filtering_quality;
		dword lighting_quality;
		dword effects_quality;
		dword details_quality;
		dword postprocessing_quality;
		bool motion_blur;
		bool vertical_sync;
		bool antialiasing;
		byte unknown372FB;
		bool hide_watermark;
		byte unknown372D[3];
		dword unknown37300;
		byte unknown37304[0x38];
		dword master_volume;
		dword sfx_volume;
		dword music_volume;
		dword voice_volume;
		dword voice_chat_control;
		dword voice_chat_volume;
		bool toggle_crouch;
		bool hud_shake;
		byte unknown37356;
		byte unknown37357;
		dword team_color;
		real camera_fov;
		byte unknown37360;
		byte unknown37361;
		byte unknown37362;
		byte unknown37363;
		dword controls_method;
		dword mouse_sensitivity_vertical;
		dword mouse_sensitivity_horizontal;
		dword mouse_sensitivity_vehicle_vertical;
		dword mouse_sensitivity_vehicle_horizontal;
		dword mouse_acceleration;
		bool mouse_filter;
		bool invert_mouse;
		word unknown3737E;
		dword unknown37380;
		byte bindings[0x208];
		byte unknown3758C[0xA72];
	};
	static_assert(sizeof(preferences_data) == 0x38000);

	bool preferences_initialize();
}