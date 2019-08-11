/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/static_function_info.h>

//
// Constructors
//

StaticFunctionInfo::StaticFunctionInfo() :
	m_function{ [](FunctionParameters) { return ObjectInstance(); } },
	m_function_name{ "" },
	m_has_return{ false },
	m_parameter_count{ 0 }
{

}

//
// Public methods
//

ObjectInstance StaticFunctionInfo::call(FunctionParameters params)
{
	return m_function(params);
}

StaticFunctionInfo::Function StaticFunctionInfo::get_function()
{
	return m_function;
}

void StaticFunctionInfo::set_function(StaticFunctionInfo::Function function)
{
	m_function = function;
}
	
std::string StaticFunctionInfo::get_function_name()
{
	return m_function_name;
}

void StaticFunctionInfo::set_function_name(std::string function_name)
{
	m_function_name = function_name;
}
	
bool StaticFunctionInfo::get_has_return()
{
	return m_has_return;
}

void StaticFunctionInfo::set_has_return(bool has_return)
{
	m_has_return = has_return;
}
	
int StaticFunctionInfo::get_parameter_count()
{
	return m_parameter_count;
}

void StaticFunctionInfo::set_parameter_count(int parameter_count)
{
	m_parameter_count = parameter_count;
}