// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef reflection_cpp_property_h
#define reflection_cpp_property_h

// A class which is used to access a C++ class member variable.
template<class TProp>
class CppProperty
{
public:
	static PropertyInfo Create(std::string name, TProp prop);

	// Gets the property from the variable instance.
	static ObjectInstance Get(ObjectInstance& inst, TProp prop);

	// Sets the property of the variable instance.
	static void Set(ObjectInstance& inst, TProp prop, ObjectInstance& value);
};

// Stores a property which is used to access a C++ class member from lua.
// @type T The class type.
// @type TType The member type.
template <typename T, typename TType>
class CppProperty<TType T::*>
{
	typedef TType T::*TProp;
  
public:
	static PropertyInfo Create(std::string name, TProp prop)
	{
		auto property_setter = [prop](ObjectInstance inst, ObjectInstance value) {
			CppProperty<TProp>::Set(inst, prop, value);
		};

		auto property_getter = [prop](ObjectInstance inst)->ObjectInstance {
			ObjectInstance to_return = CppProperty<TProp>::Get(inst, prop);
			return to_return;
		};

		PropertyInfo property_info;
		property_info.set_parameter_name(name);
		property_info.set_function_set(property_setter);
		property_info.set_function_get(property_getter);

		return property_info;
	}

	// Gets the property and places it onto the stack.
	static ObjectInstance Get(ObjectInstance& inst, TProp prop)
	{
		T& object_instance = inst.get_value<T>();
		
		ObjectInstance to_return;
		to_return.set_value<TType>(object_instance.*prop);

		return to_return;
	}

	// Gets the property from the stack and copies it to the object.
	static void Set(ObjectInstance& inst, TProp prop, ObjectInstance& value)
	{
		T& object_instance = inst.get_value<T&>();
		TType& property_value = value.get_value<TType&>();
		
		(object_instance.*prop) = property_value;
	}
};

#endif
