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

class Reflection : public AutomaticSingleton<Reflection>
{
public:

	std::shared_ptr<ClassInfo> get_class_info(std::string name);

	std::vector<std::string> get_class_names();

	bool register_class(std::string name, ClassInfo class_info);

private:

	std::map<std::string, std::shared_ptr<ClassInfo>> class_info;
	std::vector<std::string> class_names;
};

std::shared_ptr<ClassInfo> Reflection::get_class_info(std::string name)
{
	return class_info[name];
}

std::vector<std::string> Reflection::get_class_names()
{
	return class_names;
}

bool Reflection::register_class(std::string name, ClassInfo info)
{
	class_info[name] = std::shared_ptr<ClassInfo>(new ClassInfo(info));
	class_names.push_back(name);

	return true;
}

#endif
