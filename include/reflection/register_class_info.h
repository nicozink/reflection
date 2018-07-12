/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef cpp_util_reflection_register_class_info_h
#define cpp_util_reflection_register_class_info_h

// Local Includes
#include "class_info.h"
#include "cpp_function.h"
#include "cpp_static_function.h"
#include "function_parameters.h"
#include "object_constructor.h"
#include "object_instance.h"

// System Includes
#include <functional>
#include <map>
#include <string>

template <typename TType>
class RegisterClassInfo
{
public:

	RegisterClassInfo();

	// Registers a base class for this object.
	// @type TBase The base class type.
	template <typename TBase>
	RegisterClassInfo& register_base();

	// Registers a base class for this object.
	// @returns The information describing the class.
	ClassInfo register_class();

	// Registers the constructor for this class.
	// @param name The function name.
	// @param function The function.
	template <typename... Args>
	RegisterClassInfo& register_constructor();
	
	// Registers a static method against the class.
	// @param name The function name.
	// @param function The function.
	template <class TFunc>
	RegisterClassInfo&  register_method(const std::string name, TFunc function);

	// Registers a static method against the class.
	// @param name The function name.
	// @param function The function.
	template <class TFunc>
	RegisterClassInfo&  register_static_method(const std::string name, TFunc function);

	// Registers a property which belongs to this class.
	// @param name The property name.
	// @param property The property.
	template <class TProp>
	RegisterClassInfo&  register_property(const std::string name, TProp property);

private:

	ClassInfo class_info;
};

template <typename T>
RegisterClassInfo<T>::RegisterClassInfo()
{

}

template <typename T>
ClassInfo RegisterClassInfo<T>::register_class()
{
	return class_info;
}

template <typename TType>
template <typename... Args>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_constructor()
{
	class_info.set_value_constructor(&ObjectConstructor<TType, Args...>::New);
	class_info.set_pointer_constructor(&ObjectConstructor<TType, Args...>::NewPtr);
	class_info.set_null_constructor(&ObjectConstructor<TType>::Null);

	return *this;
}

// Registers a static method against the class.
// @param name The function name.
// @param function The function.
template <typename TType>
template <class TFunc>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_method(const std::string name, TFunc function)
{
	auto call_function = [function](ObjectInstance& inst, FunctionParameters params)->ObjectInstance {
		ObjectInstance to_return = CppFunction<TFunc>::Call(inst, function, params);
		return to_return;
	};

	class_info.add_member_function(name, call_function);

	return *this;
}

// Registers a static method against the class.
// @param name The function name.
// @param function The function.
template <typename TType>
template <class TFunc>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_static_method(const std::string name, TFunc function)
{
	auto call_function = [function](FunctionParameters params)->ObjectInstance {
		ObjectInstance to_return = CppStaticFunction<TFunc>::Call(function, params);
		return to_return;
	};

	class_info.add_static_function(name, call_function);

	return *this;
}

#endif
