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

	ObjectInstance create_new(FunctionParameters params);

	ObjectInstance create_new_ptr(FunctionParameters params);

	ObjectInstance create_null();

	void set_value_constructor(std::function<ObjectInstance(FunctionParameters)> function);
	void set_pointer_constructor(std::function<ObjectInstance(FunctionParameters)> function);
	void set_null_constructor(std::function<ObjectInstance()> function);

private:

	// Stores constructors used to create the object.
	std::function<ObjectInstance(FunctionParameters)> value_constructor;
	std::function<ObjectInstance(FunctionParameters)> pointer_constructor;
	std::function<ObjectInstance()> null_constructor;

	// Stores member functions of the class.
	std::map<std::string, std::function<ObjectInstance(ObjectInstance, FunctionParameters)>> member_functions;

	// Stores static functions of the class.
	std::map<std::string, std::function<ObjectInstance(FunctionParameters)>> static_functions;
};

#endif
