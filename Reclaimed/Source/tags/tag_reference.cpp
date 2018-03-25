#include <memory\datum_index.hpp>
#include <tags\tag.hpp>

#include <tags\tag_reference.hpp>

namespace blam
{
	const tag_reference tag_reference::none = { tag::none, datum_index::none };

	tag_reference::tag_reference() :
		tag_reference(none)
	{
	}

	tag_reference::tag_reference(const tag &group_tag, const datum_index &tag_index) :
		group_tag(group_tag), tag_index(tag_index)
	{
	}

	tag_reference::tag_reference(const tag_reference &other) :
		tag_reference(other.group_tag, other.tag_index)
	{
	}

	bool tag_reference::operator==(const tag_reference &other) const
	{
		return (group_tag == other.group_tag)
			&& (tag_index == other.tag_index);
	}

	bool tag_reference::operator!=(const tag_reference &other) const
	{
		return !(*this == other);
	}

	tag_reference::operator tag() const
	{
		return group_tag;
	}

	tag_reference::operator datum_index() const
	{
		return tag_index;
	}

	tag_reference::operator bool() const
	{
		return *this != none;
	}
}