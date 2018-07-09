// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef reflection_cpp_function_h
#define reflection_cpp_function_h

// Local Includes
#include "cpp_extrtact_parameters.h"

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
class LuaCppFunction<void (T::*)(Args...)>
{
  typedef void (T::*TFunc)(Args...);
  
  public:
  
    // Calls the method using the provided function parameters.
    static ObjectInstance Call(FunctionParameters params)
    {
      // The function which we need to call is contained on the stack
      // as user data. We fetch it first.
      
      void* userData = lua_touserdata(luaState, lua_upvalueindex(1));
      
      TFunc const& function = *static_cast<TFunc const*>(userData);
      
      // We get the object of which the method is a member.
      
      T* obj = LuaState<T*>::Get(luaState, 1);
      
      // We construct a Lambda expression which will call
      // the function once we have reconstructed the list
      // of parameters.
      auto callFn = [obj, function, luaState](Args... args)
      {
        (obj->*function)(args...);
      };
      
      // we reconstruct the parameters and call the function.
      LuaCppParameters<sizeof...(Args), Args...>::Call(std::function<void (Args...)>(callFn), luaState);
      
      return 0;
    }
};

// Stores a function which is called from within Lua code.
// @type T The class type to be constructed.
// @type Args... The arguments passed to the constructor.
template <typename T, typename TReturn, typename... Args>
class LuaCppFunction<TReturn (T::*)(Args...)>
{
  typedef TReturn (T::*TFunc)(Args...);
  
  public:
  
    // Calls the method using the provided function parameters.
    static int Call(lua_State* luaState)
    {
      // The function which we need to call is contained on the stack
      // as user data. We fetch it first.
      
      void* userData = lua_touserdata(luaState, lua_upvalueindex(1));
      
      TFunc const& function = *static_cast<TFunc const*>(userData);
      
      // We get the object of which the method is a member.
      
      T* obj = LuaState<T*>::Get(luaState, 1);
      
      // We construct a Lambda expression which will call
      // the function once we have reconstructed the list
      // of parameters.
      auto callFn = [obj, function, luaState](Args... args)
      {
        TReturn result = (obj->*function)(args...);
        
        LuaState<TReturn>::Push(luaState, result);
      };
      
      // we reconstruct the parameters and call the function.
      LuaCppParameters<sizeof...(Args), Args...>::Call(std::function<void (Args...)>(callFn), luaState);
      
      return 1;
    }
};

#endif
