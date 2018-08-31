/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_object_instance_h
#define reflection_object_instance_h

// Library Includes
#include <cpp_util/types/variant_type_helper.h>

// Project Includes
#include <reflection/reflection_class_info.h>

// System Includes
#include <memory>
#include <string>

class ClassInfo;

class ObjectInstance
{
public:

	enum class ObjectType
	{
		Empty,
		Boolean,
		Float,
		Integer,
		Object,
		String
	};

	ObjectInstance();

	template <typename T>
	T get_value() const;

	template <typename T>
	void set_value(T& value);

	template <typename T>
	void set_value(T&& value);

	template <typename T>
	void set_value(std::shared_ptr<ClassInfo> class_info, T& value);

	template <typename T>
	void set_value(std::shared_ptr<ClassInfo> class_info, T&& value);

	ObjectType get_type();

	std::string get_type_name();

private:

	std::shared_ptr<ClassInfo> class_info;

	ObjectType type;

	VariantType value;
};

template <>
float ObjectInstance::get_value<float>() const;

template <>
int ObjectInstance::get_value<int>() const;

template <typename T>
T ObjectInstance::get_value() const
{
	return value.get<T>();
}

template <>
void ObjectInstance::set_value<bool>(bool& value);

template <>
void ObjectInstance::set_value<float>(float& value);

template <>
void ObjectInstance::set_value<int>(int& value);

template <>
void ObjectInstance::set_value<std::string>(std::string& value);

template <typename T>
void ObjectInstance::set_value(T& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<T>::Get();

	this->class_info = class_info;
	this->value = VariantTypeHelper<T>::Create(value);

	type = ObjectType::Object;
}

template <>
void ObjectInstance::set_value<bool>(bool&& value);

template <>
void ObjectInstance::set_value<float>(float&& value);

template <>
void ObjectInstance::set_value<int>(int&& value);

template <>
void ObjectInstance::set_value<std::string>(std::string&& value);

template <typename T>
void ObjectInstance::set_value(T&& value)
{
	std::shared_ptr<ClassInfo> class_info = ReflectionClassInfo<T>::Get();

	this->class_info = class_info;
	this->value = VariantTypeHelper<T>::Create(std::move(value));

	type = ObjectType::Object;
}

template <typename T>
void ObjectInstance::set_value(std::shared_ptr<ClassInfo> class_info, T& value)
{
	this->class_info = class_info;
	this->value = VariantTypeHelper<T>::Create(value);
}

template <typename T>
void ObjectInstance::set_value(std::shared_ptr<ClassInfo> class_info, T&& value)
{
	this->class_info = class_info;
	this->value = VariantTypeHelper<T&&>::Create(std::move(value));
}

#endif
