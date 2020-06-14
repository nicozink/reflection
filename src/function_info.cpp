/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/function_info.h>

//
// Constructors
//

FunctionInfo::FunctionInfo() :
	m_function{ [](ObjectInstance, FunctionParameters) { return ObjectInstance(); } },
	m_function_name{ "" },
	m_has_return{ false },
	m_parameter_count{ 0 }
{

}

//
// Public methods
//

ObjectInstance FunctionInfo::call(ObjectInstance inst, FunctionParameters params)
{
	return m_function(inst, params);
}

FunctionInfo::Function FunctionInfo::get_function()
{
	return m_function;
}

void FunctionInfo::set_function(FunctionInfo::Function function)
{
	m_function = function;
}
	
std::string FunctionInfo::get_function_name()
{
	return m_function_name;
}

void FunctionInfo::set_function_name(std::string function_name)
{
	m_function_name = function_name;
}
	
bool FunctionInfo::get_has_return()
{
	return m_has_return;
}

void FunctionInfo::set_has_return(bool has_return)
{
	m_has_return = has_return;
}
	
int FunctionInfo::get_parameter_count()
{
	return m_parameter_count;
}

void FunctionInfo::set_parameter_count(int parameter_count)
{
	m_parameter_count = parameter_count;
}