#pragma once

namespace blam
{
	struct tag;
	struct string_id;

	struct tag_group
	{
		tag group_tag;
		tag parent_group_tag;
		tag grandparent_group_tag;
		string_id group_name;

		static const tag_group none;

		tag_group();
		tag_group(const tag &group_tag, const string_id &group_name);
		tag_group(const tag &group_tag, const tag &parent_group_tag, const string_id &group_name);
		tag_group(const tag &group_tag, const tag &parent_group_tag, const tag &grandparent_group_tag, const string_id &group_name);
		tag_group(const tag_group &other);

		bool contains(const tag &tag) const;

		bool operator==(const tag_group &other) const;
		bool operator!=(const tag_group &other) const;

		operator bool() const;
	};
}