/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_class_info_h
#define reflection_class_info_h

// Local Includes
#include "function_info.h"
#include "function_parameters.h"
#include "object_instance.h"
#include "property_info.h"
#include "static_function_info.h"

// System Includes
#include <functional>
#include <map>
#include <string>

class ClassInfo
{
public:

	// Static Variables
	static std::shared_ptr<ClassInfo> Undefined;

	ClassInfo(std::string type_name, TypeToId::type_id type_id);

	// Type Info

	std::string get_type_name();
	TypeToId::type_id get_type_id();

	// Constructors

	void set_constructors(
		StaticFunctionInfo value_function,
		StaticFunctionInfo pointer_function,
		StaticFunctionInfo null_function);

	ObjectInstance create_new();
	ObjectInstance create_new(FunctionParameters params);
	ObjectInstance create_new_ptr();
	ObjectInstance create_new_ptr(FunctionParameters params);
	ObjectInstance create_null();

	bool get_has_constructor();

	StaticFunctionInfo get_create_new();
	StaticFunctionInfo get_create_new_ptr();
	StaticFunctionInfo get_create_null();

	// Member functions

	void add_member_function(std::string function_name, FunctionInfo function);
	
	ObjectInstance call_member_function(ObjectInstance instance, std::string function_name);	
	ObjectInstance call_member_function(ObjectInstance instance, std::string function_name, FunctionParameters params);

	std::vector<std::string>& get_member_function_names();

	FunctionInfo get_member_function(std::string function_name);

	// Static Functions

	void add_static_function(std::string function_name, StaticFunctionInfo function);
	
	ObjectInstance call_static_function(std::string function_name);
	ObjectInstance call_static_function(std::string function_name, FunctionParameters params);

	std::vector<std::string>& get_static_function_names();

	StaticFunctionInfo get_static_function(std::string function_name);

	// Properties

	void add_property(std::string property_name, PropertyInfo property_function);
	
	ObjectInstance get_property(ObjectInstance instance, std::string property_name);
	void set_property(ObjectInstance instance, std::string property_name, ObjectInstance value);

	std::vector<std::string>& get_property_names();

	// Values

	void add_value(std::string value_name, ObjectInstance value);

	ObjectInstance get_value(std::string value_name);

	std::vector<std::string>& get_value_names();

private:

	// Type info
	std::string type_name;
	TypeToId::type_id type_id;

	// Stores constructors used to create the object.
	StaticFunctionInfo value_constructor;
	StaticFunctionInfo pointer_constructor;
	StaticFunctionInfo null_constructor;
	bool has_constructor;

	// Stores getter or setters of class properties.
	std::map<std::string, PropertyInfo> properties;
	std::vector<std::string> property_names;

	// Stores static values assigned to the class.
	std::map<std::string, ObjectInstance> values;
	std::vector<std::string> value_names;

	// Stores member functions of the class.
	std::map<std::string, FunctionInfo> member_functions;
	std::vector<std::string> member_function_names;

	// Stores static functions of the class.
	std::map<std::string, StaticFunctionInfo> static_functions;
	std::vector<std::string> static_function_names;
};

#endif
