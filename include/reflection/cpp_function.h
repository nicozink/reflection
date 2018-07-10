// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef reflection_cpp_function_h
#define reflection_cpp_function_h

// Local Includes
#include "cpp_parameters.h"

// Project Includes

// External Includes
#include <tuple>

// A class which is used to call a cpp function.
template<class TFunc>
class CppFunction
{
public:
  
	// Calls the method using the provided function parameters.
	static ObjectInstance Call(FunctionParameters params);
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename T, typename... Args>
class CppFunction<void (T::*)(Args...)>
{
	typedef void (T::*TFunc)(Args...);
  
public:
  
	// Calls the method using the provided function parameters.
	static ObjectInstance Call(ObjectInstance& inst, TFunc function, FunctionParameters params)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return, &inst, function](Args... args)
		{
			T& object_instance = inst.get_value<T>();
			(object_instance.*function)(args...);
		};
      
		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(std::function<void (Args...)>(call_function), params);
      
		return to_return;
	}
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename T, typename TReturn, typename... Args>
class CppFunction<TReturn (T::*)(Args...)>
{
	typedef TReturn (T::*TFunc)(Args...);
  
public:
  
	// Calls the method using the provided function parameters.
	static int Call(ObjectInstance inst, TFunc function, FunctionParameters params)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return, inst, function](Args... args)
		{
			T object_instance = inst.get_value<T>();
			to_return.set_value<TReturn>((object_instance.*function)(args...));
		};

		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(std::function<void(Args...)>(call_function), params);

		return to_return;
	}
};

#endif
