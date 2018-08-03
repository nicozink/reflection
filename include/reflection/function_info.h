/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_function_info_h
#define reflection_function_info_h

// Local Includes
#include "function_parameters.h"
#include "object_instance.h"

// System Includes
#include <functional>
#include <map>
#include <string>

class FunctionInfo
{
public:

	// Type defs

	typedef std::function<ObjectInstance(ObjectInstance, FunctionParameters)> Function;

	// Constructors

	FunctionInfo();

	// Public functions

	ObjectInstance call(ObjectInstance inst, FunctionParameters params);

	Function get_function();
	void set_function(Function function);
	
	std::string get_function_name();
	void set_function_name(std::string function_name);
	
	bool get_has_return();
	void set_has_return(bool has_return);
	
	int get_parameter_count();
	void set_parameter_count(int parameter_count);

private:

	Function function;

	std::string function_name;

	bool has_return;
	
	int parameter_count;
};

#endif
