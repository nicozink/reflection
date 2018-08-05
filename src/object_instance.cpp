/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/object_instance.h>

// Local Includes
#include <reflection/class_info.h>

ObjectInstance::ObjectInstance() :
	class_info{ nullptr },
	type{ ObjectInstance::ObjectType::Empty },
	value{ VariantType::Null }
{

}

template <>
void ObjectInstance::set_value<float>(float& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<float>();

	set_value<float>(class_info, value);

	type = ObjectType::Float;
}

template <>
void ObjectInstance::set_value<int>(int& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<int>();

	set_value<int>(class_info, value);

	type = ObjectType::Integer;
}

template <>
void ObjectInstance::set_value<std::string>(std::string& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<std::string>();

	set_value<std::string>(class_info, value);

	type = ObjectType::String;
}

template <>
void ObjectInstance::set_value<float>(float&& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<float>();

	set_value<float>(class_info, value);

	type = ObjectType::Float;
}

template <>
void ObjectInstance::set_value<int>(int&& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<int>();

	set_value<int>(class_info, value);

	type = ObjectType::Integer;
}

template <>
void ObjectInstance::set_value<std::string>(std::string&& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<std::string>();

	set_value<std::string>(class_info, value);

	type = ObjectType::String;
}

ObjectInstance::ObjectType ObjectInstance::get_type()
{
	return type;
}

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
