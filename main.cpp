#include "BigInt.h";
#include "Tests.h";
using namespace std;

bool Testing = false;

const int N = 2 * 1e5 + 1;

int n;
BigInt a[N], b[N], p[N];

BigInt pow(BigInt step, BigInt base, BigInt mod)
{
	if (step == 0)
	{
		return BigInt(1);
	}

	if (step % 2 == 0)
	{
		BigInt temp = pow(divBy2(step), base, mod);

		return (temp * temp) % mod;
	}
	else
	{
		BigInt temp = pow(step - 1, base, mod);

		return (temp * base) % mod;
	}
}

void read()
{
	cout << "Input count of uravneniy:";
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		cout << "\na_" << i << " = ";
		cin >> a[i];

		cout << "b_" << i << " = ";
		cin >> b[i];

		cout << "p_" << i << " = ";
		cin >> p[i];
	}
}

void metamorphosis()
{
	for (int i = 1; i <= n; i++)
	{
		a[i] = b[i] * pow(p[i] - 2, a[i], p[i]);
	}

	return;
}

void solve()
{
	read();
	metamorphosis();

	pair < BigInt, BigInt > x = { a[1], p[1] };

	for (int j = 2; j <= n; j++)
	{
		BigInt ai = x.first;
		BigInt pi = x.second;

		BigInt aiaj = (a[j] - ai) % p[j];

		if (aiaj < 0) aiaj += p[j];

		BigInt piaiaj = (aiaj * pow(p[j] - 2, pi, p[j])) % p[j];

		BigInt newAi = ai + pi * piaiaj;
		BigInt newPi = pi * p[j];

		newAi %= newPi;

		x = { newAi, newPi };
	}

	cout << "\n\nAnswer is " << x.first % x.second << " + " << x.second << "k\n";

	return;
}

int main()
{
	if (Testing)
	{
		Tests tests = Tests();

		tests.Test_all();
	}
	else
	{
		solve();
	}
}