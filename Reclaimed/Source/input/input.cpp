#include "input.hpp"

namespace blam
{
	bool input_key_is_down(short_enum key_code, long_enum input_type)
	{
		return static_cast<bool(__fastcall *)(int, int)>(module_get_address(0x81B70))(key_code, input_type);
	}
}