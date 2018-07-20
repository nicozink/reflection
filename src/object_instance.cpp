/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/object_instance.h>

// Local Includes
#include <reflection/class_info.h>

std::string ObjectInstance::get_type_name()
{
	if (class_info != nullptr)
	{
		return class_info->get_type_name();
	}
	else
	{
		return "unknown_type";
	}
}
