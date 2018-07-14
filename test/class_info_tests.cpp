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
	// Static Methods
	//

	static int get_static_number()
	{
		return static_number;
	}

	static void set_static_number(int value)
	{
		static_number = value;
	}

	static int subtract_numbers(int v1, int v2)
	{
		return v1 - v2;
	}

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

	TestClass(int value1, double value2)
	{
		test_variable = value1 + (int)value2;
	}

	~TestClass()
	{

	}

	void add_numbers(int value1, double value2)
	{
		test_variable = value1 + (int)value2;
	}

	// Gets the variable.
	int get_variable()
	{
		return test_variable;
	}

	// Gets the variable.
	void test_method()
	{
		test_variable = 125;
	}

	// Sets the variable to the specified value.
	void set_variable(int value)
	{
		test_variable = value;
	}

	// Stores a variable used to test V8 functionality.
	int test_variable;

	static int static_number;
};

int TestClass::static_number = 0;

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

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestDefaultConstructor)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor()
		.register_class();

	ObjectInstance inst = class_info.create_new();

	ASSERT_EQ(inst.get_value<TestClass>().get_variable(), 2);
}

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestConstructorOneArg)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor<int>()
		.register_class();

	FunctionParameters params;
	params.add(200);

	ObjectInstance inst = class_info.create_new(params);

	ASSERT_EQ(inst.get_value<TestClass>().get_variable(), 200);
}

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestConstructorTwoArgs)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor<int, double>()
		.register_class();

	FunctionParameters params;
	params.add(200);
	params.add(50.0);

	ObjectInstance inst = class_info.create_new(params);

	ASSERT_EQ(inst.get_value<TestClass>().get_variable(), 250);
}

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestMethodCallMethodNoArgs)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor()
		.register_method("test_method", &TestClass::test_method)
		.register_class();

	ObjectInstance inst = class_info.create_new();

	class_info.call_member_function(inst, "test_method");

	ASSERT_EQ(inst.get_value<TestClass>().get_variable(), 125);
}

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestMethodCallMethodOneArg)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor()
		.register_method("set_variable", &TestClass::set_variable)
		.register_class();

	ObjectInstance inst = class_info.create_new();

	FunctionParameters params;
	params.add(200);

	class_info.call_member_function(inst, "set_variable", params);

	ASSERT_EQ(inst.get_value<TestClass>().get_variable(), 200);
}

// Tests creating a value, and retrieving a value.
TEST(ClassInfo, TestMethodCallMethodTwoArgs)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor()
		.register_method("add_numbers", &TestClass::add_numbers)
		.register_class();

	ObjectInstance inst = class_info.create_new();

	FunctionParameters params;
	params.add(200);
	params.add(50.0);

	class_info.call_member_function(inst, "add_numbers", params);

	ASSERT_EQ(inst.get_value<TestClass>().get_variable(), 250);
}

// Tests getting a value.
TEST(ClassInfo, TestMethodGetter)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor<int>()
		.register_method("get_variable", &TestClass::get_variable)
		.register_class();

	FunctionParameters constructor_params;
	constructor_params.add(200);

	ObjectInstance inst = class_info.create_new(constructor_params);

	ObjectInstance return_value = class_info.call_member_function(inst, "get_variable");

	ASSERT_EQ(return_value.get_value<TestClass>().get_variable(), 200);
}

// Tests calling a static method.
TEST(ClassInfo, TestStaticMethod)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_static_method("subtract_numbers", &TestClass::subtract_numbers)
		.register_class();

	FunctionParameters params;
	params.add(200);
	params.add(50);

	ObjectInstance return_value = class_info.call_static_function("subtract_numbers", params);

	ASSERT_EQ(return_value.get_value<int>(), 150);
}

// Tests calling a static method.
TEST(ClassInfo, TestStaticSetterGetter)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_static_method("get_static_number", &TestClass::get_static_number)
		.register_static_method("set_static_number", &TestClass::set_static_number)
		.register_class();

	FunctionParameters params;
	params.add(225);

	class_info.call_static_function("set_static_number", params);

	ObjectInstance return_value = class_info.call_static_function("get_static_number");

	ASSERT_EQ(return_value.get_value<int>(), 225);
}

// Tests setting and getting a variable.
TEST(ClassInfo, TestPropertySetterGetter)
{
	ClassInfo class_info = RegisterClassInfo<TestClass>()
		.register_constructor()
		.register_property("test_variable", &TestClass::test_variable)
		.register_class();

	ObjectInstance inst = class_info.create_new();

	ObjectInstance input_value;
	input_value.set_value(225);

	class_info.set_property(inst, "test_variable", input_value);

	ObjectInstance return_value = class_info.get_property(inst, "test_variable");

	ASSERT_EQ(return_value.get_value<int>(), 225);
}
