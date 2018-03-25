#include <tags\tag.hpp>

namespace blam
{
	const tag tag::none = 0xFFFFFFFF;

	tag::tag() :
		tag(none)
	{
	}

	tag::tag(const unsigned long value) :
		value(value)
	{
	}

	tag::tag(const tag &other) :
		tag(other.value)
	{
	}

	bool tag::operator==(const tag &other) const
	{
		return value == other.value;
	}

	bool tag::operator!=(const tag &other) const
	{
		return !(*this == other);
	}

	tag::operator unsigned long() const
	{
		return value;
	}

	tag::operator bool() const
	{
		return *this != none;
	}
}