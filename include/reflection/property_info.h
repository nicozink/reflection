/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_property_info_h
#define reflection_property_info_h

// Local Includes
#include "object_instance.h"

// System Includes
#include <functional>
#include <string>

class PropertyInfo
{
public:

	// Type defs

	typedef std::function<ObjectInstance(ObjectInstance)> GetProperty;
	typedef std::function<void(ObjectInstance, ObjectInstance)> SetProperty;

	// Constructors

	PropertyInfo();

	// Public functions

	ObjectInstance get(ObjectInstance inst);
	void set(ObjectInstance inst, ObjectInstance value);

	GetProperty get_function_get();
	void set_function_get(GetProperty function_get);
	
	SetProperty get_function_set();
	void set_function_set(SetProperty function_set);

	std::string get_parameter_name();
	void set_parameter_name(std::string parameter_name);

private:

	GetProperty m_function_get;
	
	SetProperty m_function_set;

	std::string m_parameter_name;
};

#endif
