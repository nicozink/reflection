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
	namespace \
	{ \
		class Bind##TName : public RegisterClassInfo<TType> { \
		public: \
			Bind##TName() : RegisterClassInfo<TType>(#TName) { } \
			std::shared_ptr<ClassInfo> register_class() override { \
				register_class_details(); \
				return RegisterClassInfo<TType>::register_class(); \
			} \
			void register_class_details(); \
		}; \
	} \
	void RegisterReflection##TName() \
	{ \
		Reflection::GetInstance().register_class(Bind##TName().register_class()); \
	} \
	void Bind##TName::register_class_details()

#define REGISTER_CLASS(TType) REGISTER_CLASS_AS(TType, TType)

#define REGISTER_NS_CLASS(TNamespace, TType) REGISTER_CLASS_AS(TNamespace::TType, TType)

#define MANUAL_REGISTER_CLASS_AS(TType, TName) REGISTER_CLASS_AS(TType, TName)

#define MANUAL_REGISTER_CLASS(TType) MANUAL_REGISTER_CLASS_AS(TType, TType)

#endif
