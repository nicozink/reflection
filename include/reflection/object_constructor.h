/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef cpp_util_reflection_object_constructor_h
#define cpp_util_reflection_object_constructor_h

// Local Includes
#include "cpp_parameters.h"
#include "function_parameters.h"
#include "object_instance.h"

// Stores a variety of methods which are used to create new objects.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename TType, typename... Args>
class ObjectConstructor
{
public:

	// Pushes a value onto the stack of the Lua state.
	// @param luaState The Lua state object.
	static ObjectInstance New(FunctionParameters parameters)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return](Args... args)
		{
			TType value(args...);
			to_return.set_value<TType>(value);
		};

		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(call_function, parameters);

		return to_return;
	}

	// Pushes a value onto the stack of the Lua state.
	// @param luaState The Lua state object.
	static ObjectInstance NewPtr(FunctionParameters parameters)
	{
		ObjectInstance to_return;

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto call_function = [&to_return](Args... args)
		{
			TType* value = new TType(args...);
			to_return.set_value<TType*>(value);
		};

		// we reconstruct the parameters and call the function.
		CppParameters<sizeof...(Args), Args...>::Call(call_function, parameters);

		return to_return;
	}

	// Pushes a null value onto the stack of the Lua state.
	// @param luaState The Lua state object.
	static ObjectInstance Null()
	{
		ObjectInstance to_return;
		to_return.set_value<TType*>(nullptr);

		return to_return;
	}

private:

	// Calls the constructor of the object.
	// @param atgs The arguments passed to the function.
	static TType* CreateNew(Args... args)
	{
		return new TType(args...);
	}
};

#endif
