#pragma once

namespace blam
{
	struct string_id
	{
		unsigned long value;

		static const string_id invalid;

		string_id();
		string_id(const unsigned long value);
		string_id(const string_id &other);

		bool operator==(const string_id &other) const;
		bool operator!=(const string_id &other) const;

		operator unsigned long() const;
		operator bool() const;
	};
	static_assert(sizeof(string_id) == 0x4);
}