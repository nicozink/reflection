/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/object_instance.h>

// Local Includes
#include <reflection/class_info.h>

ObjectInstance::ObjectInstance() :
	m_class_info{ nullptr },
	m_type{ ObjectInstance::ObjectType::Empty },
	m_value{ VariantType::Null }
{

}

template <>
float ObjectInstance::get_value<float>() const
{
	if (m_type == ObjectType::Integer)
	{
		return (float)m_value.get<int>();
	}
	else
	{
		return m_value.get<float>();
	}
}

template <>
int ObjectInstance::get_value<int>() const
{
	if (m_type == ObjectType::Float)
	{
		return (int)m_value.get<float>();
	}
	else
	{
		return m_value.get<int>();
	}
}

template <>
void ObjectInstance::set_value<bool>(bool& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<bool>::Get();

	set_value<bool>(class_info, value);

	m_type = ObjectType::Boolean;
}

template <>
void ObjectInstance::set_value<float>(float& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<float>::Get();

	set_value<float>(class_info, value);

	m_type = ObjectType::Float;
}

template <>
void ObjectInstance::set_value<int>(int& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<int>::Get();

	set_value<int>(class_info, value);

	m_type = ObjectType::Integer;
}

template <>
void ObjectInstance::set_value<std::string>(std::string& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<std::string>::Get();

	set_value<std::string>(class_info, value);

	m_type = ObjectType::String;
}

template <>
void ObjectInstance::set_value<bool>(bool&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<bool>::Get();

	set_value<bool>(class_info, value);

	m_type = ObjectType::Boolean;
}

template <>
void ObjectInstance::set_value<float>(float&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<float>::Get();

	set_value<float>(class_info, value);

	m_type = ObjectType::Float;
}

template <>
void ObjectInstance::set_value<int>(int&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<int>::Get();

	set_value<int>(class_info, value);

	m_type = ObjectType::Integer;
}

template <>
void ObjectInstance::set_value<std::string>(std::string&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<std::string>::Get();

	set_value<std::string>(class_info, value);

	m_type = ObjectType::String;
}

ObjectInstance::ObjectType ObjectInstance::get_type()
{
	return m_type;
}

std::string ObjectInstance::get_type_name()
{
	if (m_class_info != nullptr)
	{
		return m_class_info->get_type_name();
	}
	else
	{
		return "unknown_type";
	}
}
