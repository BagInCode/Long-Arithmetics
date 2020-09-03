#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class BigInt
{
	vector < int > digit;
	bool negative = 0;

public:

	/* constructors */
	BigInt();
	BigInt(string number);
	BigInt(long long number);
	BigInt(vector < int > _digit, bool _negative);

	/* get function */
	vector < int > getDigit();
	int getNegative();

	/* math */
	BigInt abs();
	BigInt sqrt();
	int sign();
	
	/* other functions */
	void normalize();
};

/* input/output */
istream& operator >> (istream& in,  BigInt& number);
ostream& operator << (ostream& out, BigInt number);

/* greather/equal/less */
bool operator > (BigInt number1, BigInt number2);
bool operator > (BigInt number1, int number2);

bool operator < (BigInt number1, BigInt number2);
bool operator < (BigInt number1, int number2);

bool operator >= (BigInt number1, BigInt number2);
bool operator >= (BigInt number1, int number2);

bool operator <= (BigInt number1, BigInt number2);
bool operator <= (BigInt number1, int number2);

bool operator == (BigInt number1, BigInt number2);
bool operator == (BigInt number1, int number2);

bool operator != (BigInt number1, BigInt number2);
bool operator != (BigInt number1, int number2);

/* add */
BigInt operator + (BigInt number1, BigInt number2);
BigInt operator + (BigInt number1, int number2);

BigInt operator ++(BigInt& number);

void operator += (BigInt& number1, BigInt number2);
void operator += (BigInt& number1, int number2);

/* minus */
BigInt operator - (BigInt number1, BigInt number2);
BigInt operator - (BigInt number1, int number2);

BigInt operator --(BigInt& number);

void operator -= (BigInt& number1, BigInt number2);
void operator -= (BigInt& number1, int number2);


