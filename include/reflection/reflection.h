/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_reflection_h
#define reflection_reflection_h

// Local Includes
#include "class_info.h"

// Library Includes
#include <cpp_util/types/automatic_singleton.h>

// System Includes
#include <string>

template <typename TType>
class Reflection : public AutomaticSingleton<Reflection<TType>>
{
public:

	std::shared_ptr<ClassInfo> get_class_info();

	bool register_class(std::string name, ClassInfo class_info);

private:

	std::shared_ptr<ClassInfo> class_info;
};

template <typename TType>
std::shared_ptr<ClassInfo> Reflection<TType>::get_class_info()
{
	return class_info;
}

template <typename TType>
bool Reflection<TType>::register_class(std::string name, ClassInfo info)
{
	class_info = std::shared_ptr<ClassInfo>(new ClassInfo(info));
	return true;
}

#endif
