#include <memory\datum_index.hpp>

namespace blam
{
	const datum_index datum_index::none = 0xFFFFFFFF;

	datum_index::datum_index() :
		datum_index(none)
	{
	}

	datum_index::datum_index(const unsigned long value) :
		value(value)
	{
	}

	datum_index::datum_index(const unsigned short salt, const unsigned short index) :
		datum_index((unsigned long)(salt << 16) | index)
	{
	}

	datum_index::datum_index(const datum_index &other) :
		datum_index(other.value)
	{
	}

	unsigned short datum_index::salt() const
	{
		return (unsigned short)(value >> 16);
	}

	unsigned short datum_index::index() const
	{
		return (unsigned short)(value & 0xFFFF);
	}

	bool datum_index::operator==(const datum_index &other) const
	{
		return value == other.value;
	}

	bool datum_index::operator!=(const datum_index &other) const
	{
		return !(*this == other);
	}

	datum_index::operator unsigned long() const
	{
		return value;
	}

	datum_index::operator bool() const
	{
		return *this != none;
	}
}