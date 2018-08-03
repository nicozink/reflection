/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/static_function_info.h>

//
// Constructors
//

StaticFunctionInfo::StaticFunctionInfo()
{

}

//
// Public methods
//

ObjectInstance StaticFunctionInfo::call(FunctionParameters params)
{
	return function(params);
}

StaticFunctionInfo::Function StaticFunctionInfo::get_function()
{
	return function;
}

void StaticFunctionInfo::set_function(StaticFunctionInfo::Function function)
{
	this->function = function;
}
	
std::string StaticFunctionInfo::get_function_name()
{
	return function_name;
}

void StaticFunctionInfo::set_function_name(std::string function_name)
{
	this->function_name = function_name;
}
	
bool StaticFunctionInfo::get_has_return()
{
	return has_return;
}

void StaticFunctionInfo::set_has_return(bool has_return)
{
	this->has_return = has_return;
}
	
int StaticFunctionInfo::get_parameter_count()
{
	return parameter_count;
}

void StaticFunctionInfo::set_parameter_count(int parameter_count)
{
	this->parameter_count = parameter_count;
}