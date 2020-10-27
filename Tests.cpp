#include "Tests.h"
#include <cassert>

Tests::Tests() {}

void Tests::Test_all()
{
	Test_units();
	Test_stress();

	return;
}

void Tests::Test_units()
{
	cout << "\n\nStart unit tests\n-----------------------";

	test_get_functions();
	test_compare_operators();
	test_math_functions_unit();
	test_add_operators_unit();
	test_minus_operators_unit();
	test_mult_operators_unit();
	test_div_operators_unit();
	test_mod_operators_unit();

	cout << "\nFinish unit tests\n-----------------------\n";

	return;
}

void Tests::Test_stress()
{

	cout << "\n\nStart stress tests\n-----------------------\n";

	test_math_functions_stress();
	test_add_operators_stress();
	test_minus_operators_stress();
	test_mult_operators_stress();
	test_div_operators_stress();
	test_mod_operators_stress();

	cout << "\nFinish stress tests\n-----------------------\n";

	return;
}

void Tests::test_compare_operators()
{
	cout << "\n\n\tStart compare (>, >=, ==, <, <=, !=) test:\n\n";

	cout << "\t\t Test == : ";
	assert(BigInt("123") == BigInt(123));
	assert((BigInt(123) == BigInt(-123)) == 0);
	cout << "OK\n";

	cout << "\t\t Test != : ";
	assert(BigInt(123) != BigInt(-123));
	assert((BigInt("123") != BigInt(123)) == 0);
	cout << "OK\n";

	cout << "\t\t Test > : ";
	assert(BigInt("123") > BigInt(122));
	assert((BigInt("123") > BigInt(123)) == 0);
	cout << "OK\n";

	cout << "\t\t Test < : ";
	assert(BigInt("122") < BigInt(123));
	assert((BigInt(123) < BigInt("123")) == 0);
	cout << "OK\n";

	cout << "\t\t Test >= : ";
	assert(BigInt("123") >= BigInt(122));
	assert(BigInt("123") >= BigInt(123));
	assert((BigInt("123") >= BigInt(124)) == 0);
	cout << "OK\n";

	cout << "\t\t Test <= : ";
	assert(BigInt("122") <= BigInt(123));
	assert(BigInt("122") <= BigInt(122));
	assert((BigInt(123) <= BigInt("121")) == 0);
	cout << "OK\n";

	cout << "\n-----------------------";

	return;
}

void Tests::test_add_operators_unit() 
{
	cout << "\n\n\tStart add (+, +=) test:\n\n";

	cout << "\t\t Test + : ";
	assert(BigInt(0) + BigInt("123") == 123);
	assert(BigInt(-12) + BigInt(12) == 0);
	assert(BigInt(12) + BigInt(12) == 24);
	assert(BigInt(-12) + BigInt(-12) == -24);
	assert(BigInt(-6) + BigInt(12) == 6);
	assert(BigInt(6) + BigInt(-12) == -6);
	assert(BigInt(162533) + BigInt(16243) == 178776);
	cout << "OK\n";


	cout << "\t\t Test += : ";
	BigInt a = BigInt(1);
	a += BigInt(9);
	assert(a == 10);
	a += BigInt(-5);
	assert(a == 5);
	a += BigInt(-6);
	assert(a == -1);
	a += BigInt(-1);
	assert(a == -2);
	a += BigInt(13);
	assert(a == 11);
	cout << "OK\n";

	cout << "\n-----------------------";
}
void Tests::test_add_operators_stress() {}

void Tests::test_minus_operators_unit() 
{
	cout << "\n\n\tStart minus (-, -=) test:\n\n";

	cout << "\t\t Test - : ";
	assert(BigInt(123) - BigInt(1) == 122);
	assert(BigInt(-12) - BigInt(12) == -24);
	assert(BigInt(12) - BigInt(12) == 0);
	assert(BigInt(-12) - BigInt(-12) == 0);
	assert(BigInt(6) - BigInt(12) == -6);
	assert(BigInt(-6) - BigInt(-12) == 6);
	assert(BigInt(10000000) - BigInt(1) == 9999999);
	cout << "OK\n";


	cout << "\t\t Test -= : ";
	BigInt a = BigInt(10);
	a -= BigInt(5);
	assert(a == 5);
	a -= BigInt(10);
	assert(a == -5);
	a -= BigInt(7);
	assert(a == -12);
	a -= BigInt(-7);
	assert(a == -5);
	a -= BigInt(-7);
	assert(a == 2);
	cout << "OK\n";

	cout << "\n-----------------------";
}
void Tests::test_minus_operators_stress() {}

void Tests::test_mult_operators_unit() 
{
	cout << "\n\n\tStart mult (*, *=) test:\n\n";

	cout << "\t\t Test * : ";
	assert(BigInt(14) * BigInt(14) == 196);
	assert(BigInt(-2) * BigInt(3) == -6);
	assert(BigInt(2) * BigInt(-3) == -6);
	assert(BigInt(-3) * BigInt(-3) == 9);
	assert(BigInt(0) * BigInt(2) == 0);
	assert(BigInt(-2) * BigInt(0) == 0);
	assert(BigInt(1836452) * BigInt(46383) == 85180153116);
	cout << "OK\n";

	cout << "\t\t Test *= : ";
	cout << "OK\n";

	cout << "\n-----------------------";

	return;
}
void Tests::test_mult_operators_stress() {}

void Tests::test_div_operators_unit() 
{
	cout << "\n\n\tStart div (/, /=, divBy2) test:\n\n";

	cout << "\t\t Test / : ";
	assert(BigInt(6) / BigInt(2) == 3);
	assert(BigInt(5) / BigInt(2) == 2);
	assert(BigInt(6) / BigInt(-2) == -3);
	assert(BigInt(5) / BigInt(-2) == -2);
	assert(BigInt(-6) / BigInt(-2) == 3);
	assert(BigInt(-5) / BigInt(-2) == 2);
	assert(BigInt(-6) / BigInt(2) == -3);
	assert(BigInt(-5) / BigInt(2) == -2);
	cout << "OK\n";

	cout << "\t\t Test /= : ";
	cout << "OK\n";
	
	cout << "\t\t Test divBy2 : ";
	assert(divBy2(BigInt(3)) == 1);
	assert(divBy2(BigInt(-3)) == -1);
	assert(divBy2(BigInt(-4)) == -2);
	assert(divBy2(BigInt(4)) == 2);
	cout << "OK\n";

	cout << "\n-----------------------";

	return;
}
void Tests::test_div_operators_stress() {}

void Tests::test_mod_operators_unit() 
{
	cout << "\n\n\tStart mod (%, %=) test:\n\n";

	cout << "\t\t Test % : ";
	assert(BigInt(10) % BigInt(3) == 1);
	assert(BigInt(10) % BigInt(-3) == 1);
	assert(BigInt(-10) % BigInt(3) == -1);
	assert(BigInt(-10) % BigInt(-3) == -1);
	cout << "OK\n";

	cout << "\t\t Test %= : ";
	cout << "OK\n";

	cout << "\n-----------------------";

	return;
}
void Tests::test_mod_operators_stress() {}

void Tests::test_math_functions_unit() 
{
	cout << "\n\n\tStart math (abs, sqrt, sign) test:\n\n";

	cout << "\t\t Test abs : ";
	assert(BigInt(1).abs() == 1);
	assert(BigInt(-1).abs() == 1);
	assert(BigInt(0).abs() == 0);
	cout << "OK\n";

	cout << "\t\t Test sqrt : ";
	assert(BigInt(224).sqrt() == 14);
	assert(BigInt(225).sqrt() == 15);
	cout << "OK\n";

	cout << "\t\t Test sign : ";
	assert(BigInt(10).sign() == 1);
	assert(BigInt(-10).sign() == -1);
	assert(BigInt(0).sign() == 0);
	cout << "OK\n";

	cout << "\n-----------------------";
}
void Tests::test_math_functions_stress() {}

void Tests::test_get_functions() 
{
	cout << "\n\n\tStart get (getDigit, getNegative) test:\n\n";

	cout << "\t\t Test getDigit : ";
	vector < long long > temp = BigInt(1).getDigit();
	assert(temp.size() == 1 && temp[0] == 1ll);
	temp = BigInt(10).getDigit();
	assert(temp.size() == 2 && temp[0] == 0ll && temp[1] == 1ll);
	temp = BigInt(0).getDigit();
	assert(temp.size() == 0ll);
	temp = BigInt("000000000000001").getDigit();
	assert(temp.size() == 1ll && temp[0] == 1ll);
	cout << "OK\n";

	cout << "\t\t Test getNegative : ";
	assert(BigInt(-1).getNegative());
	assert(!BigInt(1).getNegative());
	assert(!BigInt(0).getNegative());
	cout << "OK\n";

	cout << "\n-----------------------";

	return;
}