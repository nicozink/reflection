/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#include <reflection/property_info.h>

//
// Constructors
//

PropertyInfo::PropertyInfo()
{

}

//
// Public methods
//

ObjectInstance PropertyInfo::get(ObjectInstance inst)
{
    return function_get(inst);
}

void PropertyInfo::set(ObjectInstance inst, ObjectInstance value)
{
    function_set(inst, value);
}

PropertyInfo::GetProperty PropertyInfo::get_function_get()
{
    return function_get;
}

void PropertyInfo::set_function_get(GetProperty function_get)
{
    this->function_get = function_get;
}

PropertyInfo::SetProperty PropertyInfo::get_function_set()
{
     return function_set;
}

void PropertyInfo::set_function_set(SetProperty function_set)
{
    this->function_set = function_set;
}

std::string PropertyInfo::get_parameter_name()
{
     return parameter_name;
}

void PropertyInfo::set_parameter_name(std::string parameter_name)
{
    this->parameter_name = parameter_name;
}
