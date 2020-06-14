// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef lua_bindings_lua_cpp_parameters_h
#define lua_bindings_lua_cpp_parameters_h

// Local Includes
#include "function_parameters.h"

// External Includes
#include <functional>
#include <tuple>

// This is a class which recursively unpacks a parameter list from the
// input and calls the provided function using those parameters.
template <unsigned N, typename... Args>
struct CppParameters
{
  template <typename... ArgsCumul>
  static void Call(std::function<void(Args...)> function, FunctionParameters params, ArgsCumul... args)
  {
    typedef typename std::tuple_element<sizeof...(args), std::tuple<Args...>>::type TParamType;

	TParamType obj = params[sizeof...(args)].get_value<TParamType>();

    // We fetch the current object from the stack, and call this function again
    // recursively after appending the object to the list of parameters.
    CppParameters<N - 1, Args...>::template Call<ArgsCumul..., TParamType>(function, params, args..., obj);
  }
};

// This is the specialisation for the last level of recursion, where the parameters
// have been fetched, and the function is called.
template<typename... Args>
struct CppParameters<0, Args...>
{
  template <typename... ArgsCumul>
  static void Call(std::function<void(Args...)> function, [[maybe_unused]] FunctionParameters params, ArgsCumul... args)
  {
    function(args...);
  }
};

#endif
