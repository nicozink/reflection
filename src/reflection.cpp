/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/reflection.h>

// Library Includes
#include <reflection/class_info.h>

std::shared_ptr<ClassInfo> Reflection::get_class_info(std::string name)
{
	if (name_class_info.find(name) != name_class_info.end())
	{
		return name_class_info[name];
	}

	return ClassInfo::Undefined;
}

std::shared_ptr<ClassInfo> Reflection::get_class_info(TypeToId::type_id type_id)
{
	if (type_id_class_info.find(type_id) != type_id_class_info.end())
	{
		return type_id_class_info[type_id];
	}

	return ClassInfo::Undefined;
}

std::vector<std::string> Reflection::get_class_names()
{
	return class_names;
}

bool Reflection::register_class(std::shared_ptr<ClassInfo> info)
{
	std::string type_name = info->get_type_name();
	TypeToId::type_id type_id = info->get_type_id();

	name_class_info[type_name] = info;
	type_id_class_info[type_id] = info;
	class_names.push_back(type_name);

	return true;
}
