/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_function_parameters_h
#define reflection_function_parameters_h

// Local Includes
#include "object_instance.h"

// System Includes
#include <string>
#include <vector>

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

	ObjectInstance operator[](size_t i);

	//
	// Public Methods
	//

	void add(ObjectInstance value);

	template <typename T>
	void add(T value);

	size_t size();

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
