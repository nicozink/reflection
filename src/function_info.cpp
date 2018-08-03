/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/function_info.h>

//
// Constructors
//

FunctionInfo::FunctionInfo()
{

}

//
// Public methods
//

ObjectInstance FunctionInfo::call(ObjectInstance inst, FunctionParameters params)
{
	return function(inst, params);
}

FunctionInfo::Function FunctionInfo::get_function()
{
	return function;
}

void FunctionInfo::set_function(FunctionInfo::Function function)
{
	this->function = function;
}
	
std::string FunctionInfo::get_function_name()
{
	return function_name;
}

void FunctionInfo::set_function_name(std::string function_name)
{
	this->function_name = function_name;
}
	
bool FunctionInfo::get_has_return()
{
	return has_return;
}

void FunctionInfo::set_has_return(bool has_return)
{
	this->has_return = has_return;
}
	
int FunctionInfo::get_parameter_count()
{
	return parameter_count;
}

void FunctionInfo::set_parameter_count(int parameter_count)
{
	this->parameter_count = parameter_count;
}