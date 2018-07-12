/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/class_info.h>

void ClassInfo::add_member_function(std::string function_name, std::function<ObjectInstance(ObjectInstance, FunctionParameters)> function)
{
	member_functions.insert({ function_name, function });
}

void ClassInfo::add_static_function(std::string function_name, std::function<ObjectInstance(FunctionParameters)> function)
{
	static_functions.insert({ function_name, function });
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
