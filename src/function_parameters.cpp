/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/function_parameters.h>

FunctionParameters::FunctionParameters()
{

}

ObjectInstance FunctionParameters::operator[](int i)
{
	return values[i];
}

void FunctionParameters::add(ObjectInstance value)
{
	values.push_back(value);
}

size_t FunctionParameters::size()
{
	return values.size();
}
