#include <tags\tag_block.hpp>

namespace blam
{
	tag_block_base::tag_block_base() :
		tag_block_base(0, nullptr)
	{
	}

	tag_block_base::tag_block_base(const long count, void *const address) :
		count(count), address(address)
	{
	}

	tag_block_base::tag_block_base(const tag_block_base &other) :
		tag_block_base(other.count, other.address)
	{
	}

	bool tag_block_base::operator==(const tag_block_base &other) const
	{
		return (count == other.count)
			&& (address == other.address);
	}

	bool tag_block_base::operator!=(const tag_block_base &other) const
	{
		return !(*this == other);
	}

	tag_block_base::operator void *() const
	{
		return address;
	}
}