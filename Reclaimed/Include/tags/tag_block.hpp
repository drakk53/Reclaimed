#pragma once

namespace blam
{
	struct tag_block_base
	{
		long count;
		void *address;
		long : 32;

		tag_block_base();
		tag_block_base(const long count, void *const address);
		tag_block_base(const tag_block_base &other);

		bool operator==(const tag_block_base &other) const;
		bool operator!=(const tag_block_base &other) const;

		operator void*() const;
	};
	static_assert(sizeof(tag_block_base) == 0xC);

	template <typename element>
	struct tag_block : tag_block_base
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
	static_assert(sizeof(tag_block<bool>) == 0xC);
}