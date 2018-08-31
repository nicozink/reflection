// Copyright (c) Nico Zink
// https://github.com/nicozink/darkentity.git
// Licensed under GNU General Public License 3.0 or later.

#pragma once

#ifndef reflection_reflection_class_info_h
#define reflection_reflection_class_info_h

// Local Includes
#include "reflection.h"

// System Includes
#include <memory>

class ClassInfo;

template <typename T>
class ReflectionClassInfo
{
public:

    static std::shared_ptr<ClassInfo> Get()
    {
	    auto& reflection = Reflection::GetInstance();
		return reflection.get_class_info<T>();
    }
};

template <typename T>
class ReflectionClassInfo<T&>
{
public:

	static std::shared_ptr<ClassInfo> Get()
    {
	    auto& reflection = Reflection::GetInstance();
		return reflection.get_class_info<T>();
    }
};

template <typename T>
class ReflectionClassInfo<T*>
{
public:

	static std::shared_ptr<ClassInfo> Get()
    {
		auto& reflection = Reflection::GetInstance();
		return reflection.get_class_info<T>();
    }
};

#endif
