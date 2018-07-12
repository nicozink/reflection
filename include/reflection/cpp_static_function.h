// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef lua_bindings_lua_static_cpp_function_h
#define lua_bindings_lua_static_cpp_function_h

// Local Includes
#include "cpp_parameters.h"

// External Includes
#include <tuple>

// A class which is used to call a Lua function.
template<class TFunc>
class CppStaticFunction
{
public:

	// Calls the method using the provided Lua state.
	static ObjectInstance Call(TFunc function, FunctionParameters params);
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename... Args>
class CppStaticFunction<void (*)(Args...)>
{
	typedef void (*TFunc)(Args...);

public:

	// Calls the method using the provided Lua state.
	static ObjectInstance Call(TFunc function, FunctionParameters params)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return, function](Args... args)
		{
			function(args...);
		};

		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(std::function<void(Args...)>(call_function), params);

		return to_return;
	}
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename TReturn, typename... Args>
class CppStaticFunction<TReturn(*)(Args...)>
{
	typedef TReturn(*TFunc)(Args...);

public:

	// Calls the method using the provided Lua state.
	static ObjectInstance Call(TFunc function, FunctionParameters params)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return, function](Args... args)
		{
			to_return.set_value<TReturn>(function(args...));
		};

		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(std::function<void(Args...)>(call_function), params);

		return to_return;
	}
};

#endif
