// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef lua_bindings_lua_static_cpp_function_h
#define lua_bindings_lua_static_cpp_function_h

// Local Includes
#include "lua_cpp_parameters.h"
#include "lua_state.h"

// Project Includes

// External Includes
#include <tuple>

// Lua Includes
extern "C"
{
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

// A class which is used to call a Lua function.
template<class TFunc>
class LuaStaticCppFunction
{
public:

	// Calls the method using the provided Lua state.
	static int Call(lua_State* luaState);
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename... Args>
class LuaStaticCppFunction<void (*)(Args...)>
{
	typedef void (*TFunc)(Args...);

public:

	// Calls the method using the provided Lua state.
	static int Call(lua_State* luaState)
	{
		// The function which we need to call is contained on the stack
		// as user data. We fetch it first.

		void* userData = lua_touserdata(luaState, lua_upvalueindex(1));

		TFunc const& function = *static_cast<TFunc const*>(userData);

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto callFn = [function, luaState](Args... args)
		{
			function(args...);
		};

		// we reconstruct the parameters and call the function.
		LuaCppParameters<sizeof...(Args), Args...>::Call(std::function<void(Args...)>(callFn), luaState);

		return 0;
	}
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename TReturn, typename... Args>
class LuaStaticCppFunction<TReturn(*)(Args...)>
{
	typedef TReturn(*TFunc)(Args...);

public:

	// Calls the method using the provided Lua state.
	static int Call(lua_State* luaState)
	{
		// The function which we need to call is contained on the stack
		// as user data. We fetch it first.

		void* userData = lua_touserdata(luaState, lua_upvalueindex(1));

		TFunc const& function = *static_cast<TFunc const*>(userData);

		// We construct a Lambda expression which will call
		// the function once we have reconstructed the list
		// of parameters.
		auto callFn = [function, luaState](Args... args)
		{
			TReturn result = function(args...);

			LuaState<TReturn>::Push(luaState, result);
		};

		// we reconstruct the parameters and call the function.
		LuaCppParameters<sizeof...(Args), Args...>::Call(std::function<void(Args...)>(callFn), luaState);

		return 1;
	}
};

#endif
