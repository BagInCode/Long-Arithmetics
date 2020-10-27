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

	for (long long i = number.size(); i > long long(negative); i--)
	{
		digit.push_back(number[i - 1] - '0');
	}

	normalize();

	return;
}
BigInt::BigInt(int number)
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
BigInt::BigInt(vector < long long > _digit, bool _negative)
{
	digit = _digit;
	negative = _negative;

	normalize();

	return;
}

vector < long long > BigInt::getDigit()
{
	normalize();

	return digit;
}
long long BigInt::getNegative()
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
	BigInt l = 0;
	BigInt r = *this;
	BigInt mid;
	
	for (; l + 1 < r; )
	{

		mid = (l + r);
		mid = divBy2(mid);

		if (mid * mid > *this)
		{
			r = mid;
		}
		else
		{
			l = mid;
		}
	}

	if (r * r > * this)
	{
		return l;
	}
	else
	{
		return r;
	}
}
long long BigInt::sign()
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

	if (digit.size() == 0)
	{
		negative = 0;
	}

	return;
}

vector < complex < double > > fft(const vector < long long >& input)
{
	vector < complex < double > > temp;

	for (long long i = 0; i < input.size(); i++)
	{
		temp.push_back(complex<double>(input[i], 0));
	}

	for (long long i = input.size(); (i & (i - 1)) != 0; i++)
	{
		temp.push_back(complex < double >(0, 0));
	}

	long long cnt = temp.size();

	for (long long i = 0; i < cnt; i++)
	{
		temp.push_back(complex < double >(0, 0));
	}

	return fft(temp);
}
vector < complex < double > > fft(const vector < complex < double > >& input)
{
	const double PI = acos(-1);

	long long n = input.size();
	long long bitLen = 0; 
	
	for (; (1ll << bitLen) < n; bitLen++) {}
	
	vector<long long> rev(n);
	rev[0] = 0;
	
	long long high1 = -1;
	
	for (long long i = 1; i < n; i++) 
	{
		if ((i & (i - 1)) == 0)
		{
			high1++;
		}

		rev[i] = rev[i ^ (1 << high1)];
		rev[i] |= (1 << (bitLen - high1 - 1));
	}

	vector < complex < double > > roots(n);
	for (long long i = 0; i < n; i++) 
	{
		double alpha = 2 * PI * i / n;
		roots[i] = complex < double >(cos(alpha), sin(alpha));
	}

	vector < complex < double > > cur(n);
	for (long long i = 0; i < n; i++)
	{
		cur[i] = input[rev[i]];
	}

	for (long long len = 1; len < n; len <<= 1) 
	{
		vector < complex < double > > ncur(n);
		long long rstep = roots.size() / (len * 2);
		
		for (long long pdest = 0; pdest < n;) 
		{
			long long p1 = pdest;
			
			for (long long i = 0; i < len; i++) 
			{
				complex < double >  val = roots[i * rstep] * cur[p1 + len];
				ncur[pdest] = cur[p1] + val;
				ncur[pdest + len] = cur[p1] - val;
				pdest++, p1++;
			}

			pdest += len;
		}

		cur.swap(ncur);
	}

	return cur;
}
vector < complex < double > > fft_rev(const vector < complex < double > >& input)
{
	vector < complex < double > > result = fft(input);

	for (long long i = 0; i < (long long)result.size(); i++)
	{
		result[i] /= input.size();
	}
	
	reverse(result.begin() + 1, result.end());
	
	return result;
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
	long long sign = number.sign();

	if (sign == 0)
	{
		out << 0;
		return out;
	}

	if (sign < 0)
	{
		out << '-';
	}

	vector < long long > digit = number.getDigit();

	for (long long i = digit.size(); i; i--)
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

	vector < long long > digit1 = number1.getDigit();
	vector < long long > digit2 = number2.getDigit();
	long long sign = number1.sign();

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

	for (long long i = digit1.size(); i; i--)
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
bool operator > (BigInt number1, long long number2)
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

	vector < long long > digit1 = number1.getDigit();
	vector < long long > digit2 = number2.getDigit();
	long long sign = number1.sign();

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

	for (long long i = digit1.size(); i; i--)
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
bool operator < (BigInt number1, long long number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 < number2_BI;
}

bool operator >= (BigInt number1, BigInt number2)
{
	return !(number1 < number2);
}
bool operator >= (BigInt number1, long long number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 >= number2_BI;
}

bool operator <= (BigInt number1, BigInt number2)
{
	return !(number1 > number2);
}
bool operator <= (BigInt number1, long long number2)
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

	vector < long long > digit1 = number1.getDigit();
	vector < long long > digit2 = number2.getDigit();

	if (digit1.size() != digit2.size())
	{
		return 0;
	}

	for (long long i = 0; i < digit1.size(); i++)
	{
		if (digit1[i] != digit2[i])
		{
			return 0;
		}
	}

	return 1;
}
bool operator == (BigInt number1, long long number2)
{
	BigInt number2_BI = BigInt(number2);
	return number1 == number2_BI;
}

bool operator != (BigInt number1, BigInt number2)
{
	return !(number1 == number2);
}
bool operator != (BigInt number1, long long number2)
{
	return !(number1 == number2);
}

BigInt operator + (BigInt number1, BigInt number2)
{
	if (number1.getNegative() != number2.getNegative())
	{
		bool resultNegative;
		vector < long long > resultDigit;

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
	vector < long long > resultDigit;

	vector < long long > digit1 = number1.getDigit();
	vector < long long > digit2 = number2.getDigit();

	long long maxLen = max(digit1.size(), digit2.size());
	long long fromLast = 0;

	for (long long i = 0; i < maxLen; i++)
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
BigInt operator + (BigInt number1, long long number2)
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
void operator += (BigInt& number1, long long number2)
{	
	number1 = number1 + number2; 
	return;
}

BigInt operator - (BigInt number1, BigInt number2)
{
	if (number1.getNegative() != number2.getNegative())
	{
		bool resultNegative = number1.getNegative();
		vector < long long > resultDigit;

		BigInt temp = number1.abs() + number2.abs();
		resultDigit = temp.getDigit();

		return BigInt(resultDigit, resultNegative);
	}

	bool resultNegative;
	vector < long long > resultDigit;
	vector < long long > digit1;
	vector < long long > digit2;

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

	for (long long i = 0; i < digit2.size(); i++)
	{
		resultDigit.push_back(digit1[i] - digit2[i]);

		if (resultDigit[i] < 0)
		{
			resultDigit[i] += 10;
			digit1[i + 1] --;
		}
	}

	for (long long i = digit2.size(); i < digit1.size(); i++)
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
BigInt operator - (BigInt number1, long long number2)
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
void operator -= (BigInt& number1, long long number2)
{	
	number1 = number1 - number2;
	return;
}

BigInt operator * (BigInt number1, BigInt number2) 
{
	bool resultNegative = (number1.getNegative() ^ number2.getNegative());

	vector < long long > digit1 = number1.getDigit();
	vector < long long > digit2 = number2.getDigit();

	for (; digit1.size() < digit2.size();) { digit1.push_back(0); };
	for (; digit2.size() < digit1.size();) { digit2.push_back(0); };

	vector < complex < double > > number1_complex = fft(digit1);
	vector < complex < double > > number2_complex = fft(digit2);

	vector < complex < double > > complex_result;

	for (long long i = 0; i < number1_complex.size(); i++)
	{
		complex_result.push_back(number1_complex[i] * number2_complex[i]);
	}

	vector < complex < double > > complex_result2 = fft_rev(complex_result);

	vector < long long > int_result;
	long long fromLast = 0;

	for (long long i = 0; i < complex_result2.size(); i++)
	{
		int_result.push_back(round(complex_result2[i].real()) + fromLast);

		fromLast = int_result.back() / 10;
		int_result.back() = int_result.back() % 10;
	}

	for (; fromLast; fromLast /= 10)
	{
		int_result.push_back(fromLast % 10);
	}

	BigInt result = BigInt(int_result, resultNegative);
	result.normalize();

	return result;
}
BigInt operator * (BigInt number1, long long number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 * number2_BI;
}

void operator *= (BigInt& number1, BigInt number2)
{
	number1 = number1 * number2;
	return;
}
void operator *= (BigInt& number1, long long number2)
{
	number1 = number1 * number2;
	return;
}

BigInt divBy2 (BigInt number1)
{
	bool resultNegative = number1.getNegative();
	vector < long long > result;

	vector < long long > digits = number1.getDigit();
	long long fromLast = 0;

	for (long long i = digits.size(); i; i--)
	{
		long long res = (digits[i - 1] + 10 * fromLast) / 2;
		fromLast = (digits[i - 1] + 10 * fromLast) % 2;

		result.push_back(res);
	}

	reverse(result.begin(), result.end());

	return BigInt(result, resultNegative);
}

BigInt operator / (BigInt number1, BigInt number2) 
{
	if (number1.abs() < number2.abs())
	{
		return BigInt(0);
	}

	if (number2.sign() == 0)
	{
		exit(0);
	}

	bool resultNegative = (number1.getNegative() ^ number2.getNegative());

	number1 = number1.abs();
	number2 = number2.abs();

	BigInt l = BigInt(0);
	BigInt r = number1;
	BigInt mid;
	
	for (; l + 1 < r; )
	{
		mid = (l + r);
		mid = divBy2(mid);

		if (mid * number2 > number1)
		{
			r = mid;
		}
		else
		{
			l = mid;
		}
	}

	if (r * number2 > number1)
	{
		return BigInt(l.getDigit(), resultNegative);
	}
	else
	{
		return BigInt(r.getDigit(), resultNegative);
	}
}
BigInt operator / (BigInt number1, long long number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 / number2_BI;
}

void operator /= (BigInt& number1, BigInt number2)
{
	number1 = number1 / number2;
	return;
}
void operator /= (BigInt& number1, long long number2)
{
	number1 = number1 / number2;
	return;
}

BigInt operator % (BigInt number1, BigInt number2) 
{
	number2 = number2.abs();

	number1 = number1 - (number1 / number2) * number2;

	return number1;
}
BigInt operator % (BigInt number1, long long number2)
{
	BigInt number2_BI = BigInt(number2);

	return number1 % number2_BI;
}

void operator %= (BigInt& number1, BigInt number2)
{
	number1 = number1 % number2;
	return;
}
void operator %= (BigInt& number1, long long number2)
{
	number1 = number1 % number2;
	return;
}