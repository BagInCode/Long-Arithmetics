#include "BigInt.h"

BigInt::BigInt()
{
	negative = 0;
	digit.clear();

	return;
}
BigInt::BigInt(string number)
{
	negative = 0;
	digit.clear();

	if (number[0] == '-')
	{
		negative = 1;
	}

	for (int i = number.size(); i > int(negative); i--)
	{
		digit.push_back(number[i - 1] - '0');
	}

	return;
}
BigInt::BigInt(long long number)
{
	negative = 0;
	digit.clear();

	if (number < 0)
	{
		negative = 1;
		number *= -1;
	}

	for (; number; number /= 10)
	{
		digit.push_back(number % 10);
	}

	return;
}
BigInt::BigInt(vector < int > _digit, bool _negative)
{
	digit = _digit;
	negative = _negative;

	return;
}

vector < int > BigInt::getDigit()
{
	normalize();

	return digit;
}
int BigInt::getNegative()
{
	normalize();

	return negative;
}

BigInt BigInt::abs()
{
	return BigInt(digit, 0);
}
BigInt BigInt::sqrt()
{
	return *this;
}
int BigInt::sign()
{
	if (digit.size() == 0)
	{
		return 0;
	}
	else if (negative)
	{
		return -1;
	}else
	{
		return 1;
	}
}

void BigInt::normalize()
{
	for (; digit.size() && digit.back() == 0; digit.pop_back()) {}

	return;
}

istream& operator >> (istream& in, BigInt& number)
{
	string _number;
	in >> _number;

	number = BigInt(_number);
	
	return in;
}
ostream& operator << (ostream& out, BigInt number)
{
	int sign = number.sign();

	if (sign == 0)
	{
		out << 0;
		return out;
	}

	if (sign < 0)
	{
		out << '-';
	}

	vector < int > digit = number.getDigit();

	for (int i = digit.size(); i; i--)
	{
		out << digit[i - 1];
	}

	return out;
}

bool operator > (BigInt number1, BigInt number2)
{
	if (number1.sign() > number2.sign())
	{
		return 1;
	}

	if (number1.sign() < number2.sign())
	{
		return 0;
	}

	vector < int > digit1 = number1.getDigit();
	vector < int > digit2 = number2.getDigit();
	int sign = number1.sign();

	if ((digit1.size() > digit2.size() && sign > 0) ||
		(digit1.size() < digit2.size() && sign < 0))
	{
		return 1;
	}

	if ((digit1.size() > digit2.size() && sign < 0) ||
		(digit1.size() < digit2.size() && sign > 0))
	{
		return 0;
	}

	for (int i = digit1.size(); i; i--)
	{
		if ((digit1[i - 1] > digit2[i - 1] && sign > 0) ||
			(digit1[i - 1] < digit2[i - 1] && sign < 0))

		{
			return 1;
		}

		if ((digit1[i - 1] < digit2[i - 1] && sign > 0) ||
			(digit1[i - 1] > digit2[i - 1] && sign < 0))
		{
			return 0;
		}
	}

	return 0;
}
bool operator > (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 > number2_BI;
}

bool operator < (BigInt number1, BigInt number2)
{
	if (number1.sign() > number2.sign())
	{
		return 0;
	}

	if (number1.sign() < number2.sign())
	{
		return 1;
	}

	vector < int > digit1 = number1.getDigit();
	vector < int > digit2 = number2.getDigit();
	int sign = number1.sign();

	if ((digit1.size() > digit2.size() && sign > 0) ||
		(digit1.size() < digit2.size() && sign < 0))
	{
		return 0;
	}

	if ((digit1.size() > digit2.size() && sign < 0) ||
		(digit1.size() < digit2.size() && sign > 0))
	{
		return 1;
	}

	for (int i = digit1.size(); i; i--)
	{
		if ((digit1[i - 1] > digit2[i - 1] && sign > 0) ||
			(digit1[i - 1] < digit2[i - 1] && sign < 0))

		{
			return 0;
		}

		if ((digit1[i - 1] < digit2[i - 1] && sign > 0) ||
			(digit1[i - 1] > digit2[i - 1] && sign < 0))
		{
			return 1;
		}
	}

	return 0;
}
bool operator < (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 < number2_BI;
}

bool operator >= (BigInt number1, BigInt number2)
{
	return !(number1 < number2);
}
bool operator >= (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 >= number2_BI;
}

bool operator <= (BigInt number1, BigInt number2)
{
	return !(number1 > number2);
}
bool operator <= (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 <= number2_BI;
}

bool operator == (BigInt number1, BigInt number2)
{
	if (number1.sign() != number2.sign())
	{
		return 0;
	}

	vector < int > digit1 = number1.getDigit();
	vector < int > digit2 = number2.getDigit();

	if (digit1.size() != digit2.size())
	{
		return 0;
	}

	for (int i = 0; i < digit1.size(); i++)
	{
		if (digit1[i] != digit2[i])
		{
			return 0;
		}
	}

	return 1;
}
bool operator == (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);
	return number1 == number2_BI;
}

bool operator != (BigInt number1, BigInt number2)
{
	return !(number1 == number2);
}
bool operator != (BigInt number1, int number2)
{
	return !(number1 == number2);
}

BigInt operator + (BigInt number1, BigInt number2)
{
	if (number1.getNegative() != number2.getNegative())
	{
		bool resultNegative;
		vector < int > resultDigit;

		if (number1.abs() > number2.abs())
		{
			resultNegative = (number1.sign() < 0);

			BigInt temp = number1.abs() - number2.abs();
			
			resultDigit = temp.getDigit();
		}
		else
		{
			resultNegative = (number2.sign() < 0);

			BigInt temp = number2.abs() - number1.abs();

			resultDigit = temp.getDigit();
		}

		return BigInt(resultDigit, resultNegative);
	}

	bool resultNegative = number1.getNegative();
	vector < int > resultDigit;

	vector < int > digit1 = number1.getDigit();
	vector < int > digit2 = number2.getDigit();

	int maxLen = max(digit1.size(), digit2.size());
	int fromLast = 0;

	for (int i = 0; i < maxLen; i++)
	{
		resultDigit.push_back(fromLast);
		fromLast = 0;

		if (i < digit1.size()) resultDigit[i] += digit1[i];
		if (i < digit2.size()) resultDigit[i] += digit2[i];

		if (resultDigit[i] >= 10)
		{
			fromLast = 1;
			resultDigit[i] -= 10;
		}
	}

	if (fromLast)
	{
		resultDigit.push_back(fromLast);
	}

	BigInt result = BigInt(resultDigit, resultNegative);
	result.normalize();

	return result;
}
BigInt operator + (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);
	return number1 + number2_BI;
}

BigInt operator ++(BigInt& number)
{
	number = number + 1;
	return number;
}

void operator += (BigInt& number1, BigInt number2)
{
	number1 = number1 + number2;
	return;
}
void operator += (BigInt& number1, int number2)
{	
	number1 = number1 + number2; 
	return;
}

BigInt operator - (BigInt number1, BigInt number2)
{
	if (number1.getNegative() != number2.getNegative())
	{
		bool resultNegative = number1.getNegative();
		vector < int > resultDigit;

		BigInt temp = number1.abs() + number2.abs();
		resultDigit = temp.getDigit();

		return BigInt(resultDigit, resultNegative);
	}

	bool resultNegative;
	vector < int > resultDigit;
	vector < int > digit1;
	vector < int > digit2;

	if (number1.abs() > number2.abs())
	{
		resultNegative = number1.getNegative();

		digit1 = number1.getDigit();
		digit2 = number2.getDigit();
	}
	else
	{
		resultNegative = !(number1.getNegative());

		digit1 = number2.getDigit();
		digit2 = number1.getDigit();
	}

	for (int i = 0; i < digit2.size(); i++)
	{
		resultDigit.push_back(digit1[i] - digit2[i]);

		if (resultDigit[i] < 0)
		{
			resultDigit[i] += 10;
			digit1[i + 1] --;
		}
	}

	for (int i = digit2.size(); i < digit1.size(); i++)
	{
		resultDigit.push_back(digit1[i]);

		if (resultDigit[i] < 0)
		{
			resultDigit[i] += 10;
			digit1[i + 1] --;
		}
	}

	BigInt result = BigInt(resultDigit, resultNegative);
	result.normalize();

	return result;
}
BigInt operator - (BigInt number1, int number2)
{
	BigInt number2_BI = BigInt(number2);
	return number1 - number2_BI;
}

BigInt operator --(BigInt& number)
{
	number = number - 1;
	return number;
}

void operator -= (BigInt& number1, BigInt number2)
{
	number1 = number1 - number2;
	return;
}
void operator -= (BigInt& number1, int number2)
{	
	number1 = number1 - number2;
	return;
}