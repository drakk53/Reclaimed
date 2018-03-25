#pragma once

namespace blam
{
	struct tag
	{
		unsigned long value;

		static const tag none;

		tag();
		tag(const unsigned long value);
		tag(const tag &other);

		bool operator==(const tag &other) const;
		bool operator!=(const tag &other) const;

		operator unsigned long() const;
		operator bool() const;
	};
	static_assert(sizeof(tag) == 0x4);
}