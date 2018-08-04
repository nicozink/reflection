/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/class_info.h>

//
// Static Variables
//

std::shared_ptr<ClassInfo> ClassInfo::Undefined = std::make_shared<ClassInfo>("Undefined", -1);

//
// Constructor
//

ClassInfo::ClassInfo(std::string type_name, TypeToId::type_id type_id)
: type_name{ type_name }, type_id{ type_id }
{

}

//
// Type Info
//

std::string ClassInfo::get_type_name()
{
	return type_name;
}

TypeToId::type_id ClassInfo::get_type_id()
{
	return type_id;
}

//
// Constructors
//

void ClassInfo::set_constructors(
	StaticFunctionInfo value_function,
	StaticFunctionInfo pointer_function,
	StaticFunctionInfo null_function)
{
	value_constructor = value_function;
	pointer_constructor = pointer_function;
	null_constructor = null_function;

	has_constructor = true;
}

ObjectInstance ClassInfo::create_new()
{
	return create_new(FunctionParameters());
}

ObjectInstance ClassInfo::create_new(FunctionParameters params)
{
	return value_constructor.call(params);
}

ObjectInstance ClassInfo::create_new_ptr()
{
	return create_new_ptr(FunctionParameters());
}

ObjectInstance ClassInfo::create_new_ptr(FunctionParameters params)
{
	return pointer_constructor.call(params);
}

ObjectInstance ClassInfo::create_null()
{
	return null_constructor.call(FunctionParameters());
}

bool ClassInfo::get_has_constructor()
{
	return has_constructor;
}

StaticFunctionInfo ClassInfo::get_create_new()
{
	return value_constructor;
}

StaticFunctionInfo ClassInfo::get_create_new_ptr()
{
	return pointer_constructor;
}

StaticFunctionInfo ClassInfo::get_create_null()
{
	return null_constructor;
}

//
// Member functions
//

void ClassInfo::add_member_function(std::string function_name, FunctionInfo function)
{
	member_functions.insert({ function_name, function });
	member_function_names.push_back(function_name);
}

ObjectInstance ClassInfo::call_member_function(ObjectInstance instance, std::string function_name)
{
	FunctionParameters params;

	return call_member_function(instance, function_name, params);
}

ObjectInstance ClassInfo::call_member_function(ObjectInstance instance, std::string function_name, FunctionParameters params)
{
	auto& function = member_functions[function_name];

	return function.call(instance, params);
}

std::vector<std::string>& ClassInfo::get_member_function_names()
{
	return member_function_names;
}

//
// Static Functions
//

void ClassInfo::add_static_function(std::string function_name, StaticFunctionInfo function)
{
	static_functions.insert({ function_name, function });
	static_function_names.push_back(function_name);
}

ObjectInstance ClassInfo::call_static_function(std::string function_name)
{
	FunctionParameters params;

	return call_static_function(function_name, params);
}

ObjectInstance ClassInfo::call_static_function(std::string function_name, FunctionParameters params)
{
	auto& function = static_functions[function_name];

	return function.call(params);
}

std::vector<std::string>& ClassInfo::get_static_function_names()
{
	return static_function_names;
}

//
// Properties
//

void ClassInfo::add_property(std::string property_name, PropertyInfo property_info)
{
	properties.insert({ property_name, property_info });
	property_names.push_back(property_name);
}

ObjectInstance ClassInfo::get_property(ObjectInstance instance, std::string property_name)
{
	auto& property_function = properties[property_name];

	return property_function.get(instance);
}

void ClassInfo::set_property(ObjectInstance instance, std::string property_name, ObjectInstance value)
{
	auto& property_function = properties[property_name];

	property_function.set(instance, value);
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
	value_names.push_back(value_name);
}

ObjectInstance ClassInfo::get_value(std::string value_name)
{
	return values[value_name];
}

std::vector<std::string>& ClassInfo::get_value_names()
{
	return value_names;
}
