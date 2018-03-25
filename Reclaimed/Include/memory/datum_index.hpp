#pragma once

namespace blam
{
	struct datum_index
	{
		unsigned long value;

		static const datum_index none;

		datum_index();
		datum_index(const unsigned long value);
		datum_index(const unsigned short salt, const unsigned short index);
		datum_index(const datum_index &other);

		unsigned short salt() const;
		unsigned short index() const;

		bool operator==(const datum_index &other) const;
		bool operator!=(const datum_index &other) const;

		operator unsigned long() const;
		operator bool() const;
	};
	static_assert(sizeof(datum_index) == 0x4);
}