#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <complex>

using namespace std;

class BigInt
{
	vector < long long > digit;
	bool negative = 0;

public:

	/* constructors */
	BigInt();
	BigInt(string number);
	BigInt(int number);
	BigInt(long long number);
	BigInt(vector < long long > _digit, bool _negative);

	/* get function */
	vector < long long > getDigit();
	long long getNegative();

	/* math */
	BigInt abs();
	BigInt sqrt();
	long long sign();
	
	/* other functions */
	void normalize();
};

vector < complex < double > > fft(const vector < long long >& input);
vector < complex < double > > fft(const vector < complex < double > >& input);
vector < complex < double > > fft_rev(const vector < complex < double > >& input);

/* input/output */
istream& operator >> (istream& in,  BigInt& number);
ostream& operator << (ostream& out, BigInt number);

/* greather/equal/less */
bool operator > (BigInt number1, BigInt number2);
bool operator > (BigInt number1, long long number2);

bool operator < (BigInt number1, BigInt number2);
bool operator < (BigInt number1, long long number2);

bool operator >= (BigInt number1, BigInt number2);
bool operator >= (BigInt number1, long long number2);

bool operator <= (BigInt number1, BigInt number2);
bool operator <= (BigInt number1, long long number2);

bool operator == (BigInt number1, BigInt number2);
bool operator == (BigInt number1, long long number2);

bool operator != (BigInt number1, BigInt number2);
bool operator != (BigInt number1, long long number2);

/* add */
BigInt operator + (BigInt number1, BigInt number2);
BigInt operator + (BigInt number1, long long number2);

BigInt operator ++(BigInt& number);

void operator += (BigInt& number1, BigInt number2);
void operator += (BigInt& number1, long long number2);

/* minus */
BigInt operator - (BigInt number1, BigInt number2);
BigInt operator - (BigInt number1, long long number2);

BigInt operator --(BigInt& number);

void operator -= (BigInt& number1, BigInt number2);
void operator -= (BigInt& number1, long long number2);

/* mult */
BigInt operator * (BigInt number1, BigInt number2);
BigInt operator * (BigInt number1, long long number2);

void operator *= (BigInt& number1, BigInt number2);
void operator *= (BigInt& number1, long long number2);

/* div */
BigInt divBy2(BigInt number1);

BigInt operator / (BigInt number1, BigInt number2);
BigInt operator / (BigInt number1, long long number2);

void operator /= (BigInt& number1, BigInt number2);
void operator /= (BigInt& number1, long long number2);

/* mod */
BigInt operator % (BigInt number1, BigInt number2);
BigInt operator % (BigInt number1, long long number2);

void operator %= (BigInt& number1, BigInt number2);
void operator %= (BigInt& number1, long long number2);