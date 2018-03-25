#pragma once

namespace blam
{
	struct datum_index;
	struct tag;

	struct tag_reference
	{
		tag group_tag;
		long : 32;
		long : 32;
		datum_index tag_index;

		static const tag_reference none;

		tag_reference();
		tag_reference(const tag &group_tag, const datum_index &tag_index);
		tag_reference(const tag_reference &other);

		bool operator==(const tag_reference &other) const;
		bool operator!=(const tag_reference &other) const;

		operator tag() const;
		operator datum_index() const;
		operator bool() const;
	};
	static_assert(sizeof(tag_reference) == 0x10);
}