/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef cpp_util_reflection_register_class_h
#define cpp_util_reflection_register_class_h

// Local Includes
#include "class_info.h"

#define REGISTER_CLASS_AS(TType, TName) \
	class ScriptableClassInfo; \
	class Bind##TName : ScriptableClass<TType> { \
	public: \
		void register_class(); \
	private:
		static ScriptableObject* scriptable_object_info; \
	}; \
	ScriptableObject* Bind##TName::scriptable_object_info = Scriptable::RegisterObject(#TName, new Bind##TName()); \
	void Bind##TName::register_class()

#define REGISTER_CLASS(TType) REGISTER_CLASS_AS(TType, TType)

#endif
