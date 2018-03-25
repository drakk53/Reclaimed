#include <tags\tag.hpp>
#include <text\string_id.hpp>

#include <tags\tag_group.hpp>

namespace blam
{
	const tag_group tag_group::none = { tag::none, string_id::invalid };

	tag_group::tag_group() :
		tag_group(none)
	{
	}

	tag_group::tag_group(const tag &group_tag, const string_id &group_name) :
		tag_group(group_tag, tag::none, group_name)
	{
	}

	tag_group::tag_group(const tag &group_tag, const tag &parent_group_tag, const string_id &group_name) :
		tag_group(group_tag, parent_group_tag, tag::none, group_name)
	{
	}

	tag_group::tag_group(const tag &group_tag, const tag &parent_group_tag, const tag &grandparent_group_tag, const string_id &group_name) :
		group_tag(group_tag), parent_group_tag(parent_group_tag), grandparent_group_tag(grandparent_group_tag), group_name(group_name)
	{
	}

	tag_group::tag_group(const tag_group &other) :
		tag_group(other.group_tag, other.parent_group_tag, other.grandparent_group_tag, other.group_name)
	{
	}

	bool tag_group::contains(const tag &tag) const
	{
		return (tag == group_tag)
			|| (tag == parent_group_tag)
			|| (tag == grandparent_group_tag);
	}

	bool tag_group::operator==(const tag_group &other) const
	{
		return (group_tag == other.group_tag)
			&& (parent_group_tag == other.parent_group_tag)
			&& (grandparent_group_tag == other.grandparent_group_tag)
			&& (group_name == other.group_name);
	}

	bool tag_group::operator!=(const tag_group &other) const
	{
		return !(*this == other);
	}

	tag_group::operator bool() const
	{
		return *this != none;
	}
}