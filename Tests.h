#pragma once

#include "BigInt.h";
using namespace std;

class Tests
{

public: 
	Tests();

	void Test_all();
	void Test_units();
	void Test_stress();

private:
	void test_compare_operators();
	
	void test_add_operators_unit();
	void test_add_operators_stress();

	void test_minus_operators_unit();
	void test_minus_operators_stress();

	void test_mult_operators_unit();
	void test_mult_operators_stress();

	void test_div_operators_unit();
	void test_div_operators_stress();

	void test_mod_operators_unit();
	void test_mod_operators_stress();

	void test_math_functions_unit();
	void test_math_functions_stress();

	void test_get_functions();
};

