#include "memory\module.hpp"
#include "network.hpp"

namespace blam
{
	dword __fastcall managed_session_create_session_internal(char *a1, char *a2)
	{
		// TODO: map out structure of a1 and a2

		dword is_online = *(dword *)a2;
		bool is_host = *(word *)(a2 + 284) & 1;
		
		auto result = static_cast<dword(__fastcall *)(char *, char *)>(module_get_address(0x28C40))(a1, a2);

		if (is_host)
		{
			if (is_online == 1)
			{
				// TODO: start server here...
			}
			else
			{
				// TODO: stop server here...
			}
		}

		return result;
	}

	bool network_apply_patches()
	{
		return true;
	}
}