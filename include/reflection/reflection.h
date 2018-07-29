/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_reflection_h
#define reflection_reflection_h

// Library Includes
#include <cpp_util/types/automatic_singleton.h>
#include <cpp_util/types/type_to_id.h>

// System Includes
#include <map>
#include <memory>
#include <string>
#include <vector>

class ClassInfo;

class Reflection : public AutomaticSingleton<Reflection>
{
public:

	std::shared_ptr<ClassInfo> get_class_info(std::string name);

	std::shared_ptr<ClassInfo> get_class_info(TypeToId::type_id type_id);

	template <typename T>
	std::shared_ptr<ClassInfo> get_class_info();

	std::vector<std::string> get_class_names();

	ClassInfo* register_class(std::shared_ptr<ClassInfo> class_info);

private:

	std::map<std::string, std::shared_ptr<ClassInfo>> name_class_info;
	std::map<TypeToId::type_id, std::shared_ptr<ClassInfo>> type_id_class_info;
	std::vector<std::string> class_names;
};

template <typename T>
std::shared_ptr<ClassInfo> Reflection::get_class_info()
{
	TypeToId::type_id type_id = TypeToId::get_id<T>();

	return get_class_info(type_id);
}

#endif
