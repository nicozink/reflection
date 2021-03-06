/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

// Project Includes
#include <reflection/register_class.h>

// Library Includes
#include <unittest/test.h>

//
// Helper Classes
//

// A class used to test Lua functionality.
class TestClass
{
public:

	// Gets the variable.
	int get_test_value()
	{
		return 3;
	}
};

MANUAL_REGISTER_CLASS(TestClass)
{
	register_constructor();
	register_method("get_test_value", &TestClass::get_test_value);
}

//
// Test Methods
//

// Tests creating a new null value.
TEST(Reflection, TestRegisterClass)
{
	RegisterReflectionTestClass();

	std::shared_ptr<ClassInfo> class_info = Reflection::GetInstance().get_class_info("TestClass");
	
	ObjectInstance inst = class_info->create_null();

	ASSERT_EQ(inst.get_value<TestClass*>(), nullptr);
}
