/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef cpp_util_reflection_object_instance_h
#define cpp_util_reflection_object_instance_h

// Library Includes
#include <cpp_util/types/variant_type.h>

// Project Includes
#include <reflection/reflection.h>

// System Includes
#include <memory>
#include <string>

class ClassInfo;

class ObjectInstance
{
public:

	ObjectInstance();

	template <typename T>
	T& get_value() const;

	template <typename T>
	void set_value(T& value);

	template <typename T>
	void set_value(T&& value);

	template <typename T>
	void set_value(std::shared_ptr<ClassInfo> class_info, T& value);

	template <typename T>
	void set_value(std::shared_ptr<ClassInfo> class_info, T&& value);

	std::string get_type_name();

private:

	std::shared_ptr<ClassInfo> class_info;

	VariantType value;
};

template <typename T>
T& ObjectInstance::get_value() const
{
	return value.get<T&>();
}

template <typename T>
void ObjectInstance::set_value(T& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<T>();

	set_value<T>(class_info, value);
}

template <typename T>
void ObjectInstance::set_value(T&& value)
{
	auto& reflection = Reflection::GetInstance();
	std::shared_ptr<ClassInfo> class_info = reflection.get_class_info<T>();

	set_value<T>(class_info, std::move(value));
}

template <typename T>
void ObjectInstance::set_value(std::shared_ptr<ClassInfo> class_info, T& value)
{
	this->class_info = class_info;
	this->value.set<T>(value);
}

template <typename T>
void ObjectInstance::set_value(std::shared_ptr<ClassInfo> class_info, T&& value)
{
	this->class_info = class_info;
	this->value.set<T&&>(std::move(value));
}

#endif
