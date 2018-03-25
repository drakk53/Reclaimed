#include <text\string_id.hpp>

namespace blam
{
	const string_id string_id::invalid = 0;

	string_id::string_id() :
		string_id(invalid)
	{
	}

	string_id::string_id(const unsigned long value) :
		value(value)
	{
	}

	string_id::string_id(const string_id &other) :
		string_id(other.value)
	{
	}

	bool string_id::operator==(const string_id &other) const
	{
		return value == other.value;
	}

	bool string_id::operator!=(const string_id &other) const
	{
		return !(*this == other);
	}

	string_id::operator unsigned long() const
	{
		return value;
	}

	string_id::operator bool() const
	{
		return *this != invalid;
	}
}