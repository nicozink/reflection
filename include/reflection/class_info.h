/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef cpp_util_reflection_class_info_h
#define cpp_util_reflection_class_info_h

// Local Includes
#include "function_parameters.h"
#include "object_instance.h"

// System Includes
#include <functional>
#include <map>
#include <string>

class ClassInfo
{
public:

	ClassInfo& operator=(ClassInfo& other);

	void add_member_function(std::string function_name, std::function<ObjectInstance(ObjectInstance, FunctionParameters)> function);

	void add_static_function(std::string function_name, std::function<ObjectInstance(FunctionParameters)> function);

	void add_set_property(std::string property_name, std::function<void(ObjectInstance, ObjectInstance)> property_function);
	void add_get_property(std::string property_name, std::function<ObjectInstance(ObjectInstance)> property_function);

	void add_value(std::string value_name, ObjectInstance value);
	
	ObjectInstance call_member_function(ObjectInstance instance, std::string function_name);

	ObjectInstance call_member_function(ObjectInstance instance, std::string function_name, FunctionParameters params);

	ObjectInstance call_static_function(std::string function_name);

	ObjectInstance call_static_function(std::string function_name, FunctionParameters params);

	ObjectInstance create_new();

	ObjectInstance create_new(FunctionParameters params);

	ObjectInstance create_new_ptr();

	ObjectInstance create_new_ptr(FunctionParameters params);

	ObjectInstance create_null();

	ObjectInstance get_property(ObjectInstance instance, std::string property_name);
	void set_property(ObjectInstance instance, std::string property_name, ObjectInstance value);

	ObjectInstance get_value(std::string value_name);

	void set_value_constructor(std::function<ObjectInstance(FunctionParameters)> function);
	void set_pointer_constructor(std::function<ObjectInstance(FunctionParameters)> function);
	void set_null_constructor(std::function<ObjectInstance()> function);

private:

	// Stores constructors used to create the object.
	std::function<ObjectInstance(FunctionParameters)> value_constructor;
	std::function<ObjectInstance(FunctionParameters)> pointer_constructor;
	std::function<ObjectInstance()> null_constructor;

	// Stores getter or setters of class properties.
	std::map<std::string, std::function<void(ObjectInstance, ObjectInstance)>> property_setters;
	std::map<std::string, std::function<ObjectInstance(ObjectInstance)>> property_getters;
	std::vector<std::string> property_names;

	// Stores static values assigned to the class.
	std::map<std::string, ObjectInstance> values;
	std::vector<std::string> value_names;

	// Stores member functions of the class.
	std::map<std::string, std::function<ObjectInstance(ObjectInstance, FunctionParameters)>> member_functions;
	std::vector<std::string> member_function_names;

	// Stores static functions of the class.
	std::map<std::string, std::function<ObjectInstance(FunctionParameters)>> static_functions;
	std::vector<std::string> static_function_names;
};

#endif
