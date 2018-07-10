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

// System Includes
#include <string>

class ObjectInstance
{
public:

	ObjectInstance call(std::string function_name);

	template <typename T>
	T& get_value() const;

	template <typename T>
	void set_value(T value);

private:

	VariantType value;
};

template <typename T>
T& ObjectInstance::get_value() const
{
	return value.get<T>();
}

template <typename T>
void ObjectInstance::set_value(T value)
{
	this->value.set<T>(value);
}

#endif
