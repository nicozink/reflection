/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/class_info.h>

ObjectInstance ClassInfo::create_new(FunctionParameters params)
{
	return value_constructor(params);
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
