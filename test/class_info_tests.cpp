/*
 * Copyright (c) Nico Zink
 * https://github.com/nicozink/cpp_util.git
 * Licensed under GNU General Public License 3.0 or later. 
 */

// Project Includes
#include <reflection/register_class_info.h>

// Library Includes
#include <unittest/test.h>

// External Includes
#include <cstdlib>

//
// Helper Classes
//

// A class used to test Lua functionality.
class TestClass
{
public:

	//
	// Constructors
	//

	TestClass()
	{
		test_variable = 2;
	}

	TestClass(int value)
	{
		test_variable = value;
	}

	~TestClass()
	{

	}

	// Gets the variable.
	int get_variable()
	{
		return test_variable;
	}

	// Sets the variable to the specified value.
	void set_variable(int value)
	{
		test_variable = value;
	}

	// Stores a variable used to test V8 functionality.
	int test_variable;
};

//
// Test Methods
//

// Tests creating a new null value.
TEST(ClassInfo, TestNullConstructor)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
	.register_constructor()
	.register_class();

	ObjectInstance inst = class_info.create_null();

	ASSERT_EQ(inst.get_value<TestClass*>(), nullptr);
}

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestSimpleConstructor)
{
	ClassInfo class_info = RegisterClassInfo<int>()
		.register_constructor<int>()
		.register_class();

	FunctionParameters params;
	params.add(100);

	ObjectInstance inst = class_info.create_new(params);

	ASSERT_EQ(inst.get_value<int>(), 100);
}

// Tests passing a simple script to the V8 engine and
// checking the return value.
/*TEST(ClassInfo, TestSimpleConstructor)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor()
		.register_method("get_variable", &TestClass::get_variable)
		.register_method("set_variable", &TestClass::set_variable)
		.register_class();

	ObjectInstance inst = class_info.create_new();

	FunctionParams params;
	params.add(3);

	inst.call("set_variable", params);

	ASSERT_EQ(inst.call("get_variable").as<int>(), 3);
}*/
