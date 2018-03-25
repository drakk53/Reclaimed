#include <tags\tag_data.hpp>

namespace blam
{
	tag_data_base::tag_data_base() :
		tag_data_base(0, nullptr)
	{
	}

	tag_data_base::tag_data_base(const long size, void *const address) :
		size(size), address(address)
	{
	}

	tag_data_base::tag_data_base(const tag_data_base &other) :
		tag_data_base(other.size, other.address)
	{
	}

	bool tag_data_base::operator==(const tag_data_base &other) const
	{
		return (size == other.size)
			&& (address == other.address);
	}

	bool tag_data_base::operator!=(const tag_data_base &other) const
	{
		return !(*this == other);
	}

	tag_data_base::operator void *() const
	{
		return address;
	}
}