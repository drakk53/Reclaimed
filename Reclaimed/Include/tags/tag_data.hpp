#pragma once

namespace blam
{
	struct tag_data_base
	{
		long size;
		long : 32;
		long : 32;
		void *address;
		long : 32;

		tag_data_base();
		tag_data_base(const long count, void *const address);
		tag_data_base(const tag_data_base &other);

		bool operator==(const tag_data_base &other) const;
		bool operator!=(const tag_data_base &other) const;

		operator void*() const;
	};
	static_assert(sizeof(tag_data_base) == 0x14);

	template <typename element>
	struct tag_data : tag_data_base
	{
		operator element *() const
		{
			return reinterpret_cast<element *>(address);
		}

		element *operator->() const
		{
			return operator element *();
		}

		element &operator[](const long element_index) const
		{
			return operator->()[element_index];
		}
	};
	static_assert(sizeof(tag_data<bool>) == 0x14);
}