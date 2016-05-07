#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
	ZZ x, a, b, n;
	
	a = 7; b = 14; n = 15;
	x = AddMod(a, b, n);
	cout << "x = " << x << endl;

	a = 7; b = 11; n = 13;
	x = SubMod(a, b, n);
	cout << "x = " << x << endl;

	a = 7; b = 11; n = 20;
	x = MulMod(a, b, n);
	cout << "x = " << x << endl;

	a = 17; b = 27; n = 15;
	AddMod(x, a%n, b%n, n);
	cout << x << endl;

	a = 43; b = 12; n = 13;
	SubMod(x, a%n, b%n, n);
	cout << x << endl;

	a = 17; b = 27; n = 19;
	MulMod(x, a%n, b%n, n);
	cout << x << endl;

}