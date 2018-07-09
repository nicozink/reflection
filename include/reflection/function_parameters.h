/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef cpp_util_reflection_function_parameters_h
#define cpp_util_reflection_function_parameters_h

// Local Includes
#include "object_instance.h"

// System Includes
#include <string>

class FunctionParameters
{
public:

	//
	// Constructors
	//

	FunctionParameters();

	//
	// Operators
	//

	ObjectInstance operator[](int i);

	//
	// Public Methods
	//

	void add(ObjectInstance value);

	template <typename T>
	void add(T value);

private:

	std::vector<ObjectInstance> values;
};

template <typename T>
void FunctionParameters::add(T value)
{
	ObjectInstance parameter_value;
	parameter_value.set_value<T>(value);

	add(parameter_value);
}

#endif
