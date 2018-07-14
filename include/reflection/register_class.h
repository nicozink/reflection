/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

#pragma once

#ifndef reflection_register_class_h
#define reflection_register_class_h

// Local Includes
#include "reflection.h"
#include "register_class_info.h"

#define REGISTER_CLASS_AS(TType, TName) \
	class Bind##TName : RegisterClassInfo<TType> { \
	public: \
		ClassInfo get_class_info() { \
			register_class_details(); \
			return register_class(); \
		} \
		void register_class_details(); \
	private: \
		static bool has_class_info; \
	}; \
	bool Bind##TName::has_class_info = Reflection<TType>::GetInstance().register_class(#TName, Bind##TName().get_class_info()); \
	void Bind##TName::register_class_details()

#define REGISTER_CLASS(TType) REGISTER_CLASS_AS(TType, TType)

#endif
