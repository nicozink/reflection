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
float ObjectInstance::get_value<float>() const
{
	if (type == ObjectType::Integer)
	{
		return (float)value.get<int>();
	}
	else
	{
		return value.get<float>();
	}
}

template <>
int ObjectInstance::get_value<int>() const
{
	if (type == ObjectType::Float)
	{
		return (int)value.get<float>();
	}
	else
	{
		return value.get<int>();
	}
}

template <>
void ObjectInstance::set_value<bool>(bool& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<bool>::Get();

	set_value<bool>(class_info, value);

	type = ObjectType::Boolean;
}

template <>
void ObjectInstance::set_value<float>(float& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<float>::Get();

	set_value<float>(class_info, value);

	type = ObjectType::Float;
}

template <>
void ObjectInstance::set_value<int>(int& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<int>::Get();

	set_value<int>(class_info, value);

	type = ObjectType::Integer;
}

template <>
void ObjectInstance::set_value<std::string>(std::string& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<std::string>::Get();

	set_value<std::string>(class_info, value);

	type = ObjectType::String;
}

template <>
void ObjectInstance::set_value<bool>(bool&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<bool>::Get();

	set_value<bool>(class_info, value);

	type = ObjectType::Boolean;
}

template <>
void ObjectInstance::set_value<float>(float&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<float>::Get();

	set_value<float>(class_info, value);

	type = ObjectType::Float;
}

template <>
void ObjectInstance::set_value<int>(int&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<int>::Get();

	set_value<int>(class_info, value);

	type = ObjectType::Integer;
}

template <>
void ObjectInstance::set_value<std::string>(std::string&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<std::string>::Get();

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
