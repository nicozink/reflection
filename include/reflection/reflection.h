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

// System Includes
#include <string>

class Reflection
{
public:

	static ClassInfo RegisterClass(std::string name, ClassInfo class_info);
};

#endif
