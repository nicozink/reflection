/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/class_info.h>

//
// Constructors
//

void ClassInfo::set_value_constructor(std::function<ObjectInstance(FunctionParameters)> function)
{
	value_constructor = function;
}

void ClassInfo::set_pointer_constructor(std::function<ObjectInstance(FunctionParameters)> function)
{
	pointer_constructor = function;
}

void ClassInfo::set_null_constructor(std::function<ObjectInstance()> function)
{
	null_constructor = function;
}

ObjectInstance ClassInfo::create_new()
{
	return create_new(FunctionParameters());
}

ObjectInstance ClassInfo::create_new(FunctionParameters params)
{
	return value_constructor(params);
}

ObjectInstance ClassInfo::create_new_ptr()
{
	return create_new_ptr(FunctionParameters());
}

ObjectInstance ClassInfo::create_new_ptr(FunctionParameters params)
{
	return pointer_constructor(params);
}

ObjectInstance ClassInfo::create_null()
{
	return null_constructor();
}

bool ClassInfo::get_has_constructor()
{
	return has_constructor;
}

//
// Member functions
//

void ClassInfo::add_member_function(std::string function_name, std::function<ObjectInstance(ObjectInstance, FunctionParameters)> function)
{
	member_functions.insert({ function_name, function });
}

ObjectInstance ClassInfo::call_member_function(ObjectInstance instance, std::string function_name)
{
	FunctionParameters params;

	return call_member_function(instance, function_name, params);
}

ObjectInstance ClassInfo::call_member_function(ObjectInstance instance, std::string function_name, FunctionParameters params)
{
	auto& function = member_functions[function_name];

	return function(instance, params);
}

std::vector<std::string>& ClassInfo::get_member_function_names()
{
	return member_function_names;
}

//
// Static Functions
//

void ClassInfo::add_static_function(std::string function_name, std::function<ObjectInstance(FunctionParameters)> function)
{
	static_functions.insert({ function_name, function });
}

ObjectInstance ClassInfo::call_static_function(std::string function_name)
{
	FunctionParameters params;

	return call_static_function(function_name, params);
}

ObjectInstance ClassInfo::call_static_function(std::string function_name, FunctionParameters params)
{
	auto& function = static_functions[function_name];

	return function(params);
}

std::vector<std::string>& ClassInfo::get_static_function_names()
{
	return static_function_names;
}

//
// Properties
//

void ClassInfo::add_set_property(std::string property_name, std::function<void(ObjectInstance, ObjectInstance)> property_function)
{
	property_setters.insert({ property_name, property_function });
}

void ClassInfo::add_get_property(std::string property_name, std::function<ObjectInstance(ObjectInstance)> property_function)
{
	property_getters.insert({ property_name, property_function });
}

ObjectInstance ClassInfo::get_property(ObjectInstance instance, std::string property_name)
{
	auto& property_function = property_getters[property_name];

	return property_function(instance);
}

void ClassInfo::set_property(ObjectInstance instance, std::string property_name, ObjectInstance value)
{
	auto& property_function = property_setters[property_name];

	property_function(instance, value);
}

std::vector<std::string>& ClassInfo::get_property_names()
{
	return property_names;
}

//
// Values
//

void ClassInfo::add_value(std::string value_name, ObjectInstance value)
{
	values.insert({ value_name, value });
}

ObjectInstance ClassInfo::get_value(std::string value_name)
{
	return values[value_name];
}

std::vector<std::string>& ClassInfo::get_value_names()
{
	return value_names;
}
