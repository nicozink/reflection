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
template<class TType, class TFunc>
class CppFunction
{
public:

	// Creates the function info for the provided method.
	static FunctionInfo Create(std::string name, TFunc function);

	// Calls the method using the provided function parameters.
	static ObjectInstance Call(ObjectInstance& inst, TFunc function, FunctionParameters params);
};

// Stores a function which is called from within Lua code.
// @type TType The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename TType, typename... Args>
class CppFunction<TType, void (TType::*)(Args...)>
{
	typedef void (TType::*TFunc)(Args...);
  
public:

	// Creates the function info for the provided method.
	static FunctionInfo Create(std::string name, TFunc function)
	{
		auto call_function = [function](ObjectInstance inst, FunctionParameters params)->ObjectInstance {
			ObjectInstance to_return = Call(inst, function, params);
			return to_return;
		};

		FunctionInfo function_info;
		function_info.set_function_name(name);
		function_info.set_has_return(false);
		function_info.set_parameter_count(sizeof...(Args));
		function_info.set_function(call_function);

		return function_info;
	}

	// Calls the method using the provided function parameters.
	static ObjectInstance Call(ObjectInstance& inst, TFunc function, FunctionParameters params)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&inst, function](Args... args)
		{
			TType& object_instance = inst.get_value<TType&>();
			(object_instance.*function)(args...);
		};
      
		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(std::function<void (Args...)>(call_function), params);
      
		return to_return;
	}
};

// Stores a function which is called from within Lua code.
// @type TType The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename TType, typename TReturn, typename... Args>
class CppFunction<TType, TReturn (TType::*)(Args...)>
{
	typedef TReturn (TType::*TFunc)(Args...);
  
public:

	// Creates the function info for the provided method.
	static FunctionInfo Create(std::string name, TFunc function)
	{
		auto call_function = [function](ObjectInstance inst, FunctionParameters params)->ObjectInstance {
			ObjectInstance to_return = Call(inst, function, params);
			return to_return;
		};

		FunctionInfo function_info;
		function_info.set_function_name(name);
		function_info.set_has_return(true);
		function_info.set_parameter_count(sizeof...(Args));
		function_info.set_function(call_function);

		return function_info;
	}

	// Calls the method using the provided function parameters.
	static ObjectInstance Call(ObjectInstance inst, TFunc function, FunctionParameters params)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return, inst, function](Args... args)
		{
			TType& object_instance = inst.get_value<TType&>();
			to_return.set_value<TReturn>((object_instance.*function)(args...));
		};

		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(std::function<void(Args...)>(call_function), params);

		return to_return;
	}
};

#endif
