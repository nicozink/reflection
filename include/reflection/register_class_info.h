/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_register_class_info_h
#define reflection_register_class_info_h

// Local Includes
#include "class_info.h"
#include "cpp_function.h"
#include "cpp_property.h"
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

	RegisterClassInfo(std::string name);

	// Registers a base class for this object.
	// @type TBase The base class type.
	template <typename TBase>
	RegisterClassInfo& register_base();

	// Registers a base class for this object.
	// @returns The information describing the class.
	virtual std::shared_ptr<ClassInfo> register_class();

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

	// Registers a value which belongs to this class.
	// @param name The property name.
	// @param value The value.
	template <class TType>
	RegisterClassInfo& register_value(const std::string name, TType value);

private:

	std::shared_ptr<ClassInfo> class_info;
};

template <typename T>
RegisterClassInfo<T>::RegisterClassInfo(std::string name)
	: class_info{ std::make_shared<ClassInfo>(name, TypeToId::get_id<T>()) }
{

}

template <typename T>
std::shared_ptr<ClassInfo> RegisterClassInfo<T>::register_class()
{
	return class_info;
}

template <typename TType>
template <typename... Args>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_constructor()
{
	StaticFunctionInfo create_new;
	create_new.set_function_name("Create");
	create_new.set_has_return(true);
	create_new.set_parameter_count(sizeof...(Args));
	create_new.set_function(&ObjectConstructor<TType, Args...>::New);

	StaticFunctionInfo create_ptr;
	create_ptr.set_function_name("CreatePtr");
	create_ptr.set_has_return(true);
	create_ptr.set_parameter_count(sizeof...(Args));
	create_ptr.set_function(&ObjectConstructor<TType, Args...>::NewPtr);

	StaticFunctionInfo create_null;
	create_null.set_function_name("CreateNull");
	create_null.set_has_return(true);
	create_null.set_parameter_count(0);
	create_null.set_function(&ObjectConstructor<TType>::Null);

	class_info->set_constructors(create_new, create_ptr, create_null);

	return *this;
}

// Registers a static method against the class.
// @param name The function name.
// @param function The function.
template <typename TType>
template <class TFunc>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_method(const std::string name, TFunc function)
{
	class_info->add_member_function(name, CppFunction<TType, TFunc>::Create(name, function));

	return *this;
}

template <typename TType>
template <class TProp>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_property(const std::string name, TProp property)
{
	class_info->add_property(name, CppProperty<TProp>::Create(name, property));

	return *this;
}

// Registers a static method against the class.
// @param name The function name.
// @param function The function.
template <typename TType>
template <class TFunc>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_static_method(const std::string name, TFunc function)
{
	class_info->add_static_function(name, CppStaticFunction<TFunc>::Create(name, function));

	return *this;
}

// Registers a value which belongs to this class.
// @param name The property name.
// @param value The value.
template <class TType>
template <class TValueType>
RegisterClassInfo<TType>& RegisterClassInfo<TType>::register_value(const std::string name, TValueType value)
{
	ObjectInstance object_value;
	object_value.set_value<TValueType>(value);

	class_info->add_value(name, object_value);

	return *this;
}

#endif
