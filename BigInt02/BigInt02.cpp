#include <NTL/ZZ.h>
#include <iomanip>
#include <sstream>

typedef unsigned char byte;

using namespace std;
using namespace NTL;

int main()
{
	ZZ a, b, c, x, n;
	stringstream ss;
	byte *p;

	// cout << "a = ";
	// cin >> a;

	long l = 256;

	RandomBits( a, l );

	cout << a << endl;

	long num = NumBytes(a);

	cout  << num << endl;

	p = new byte [num];

	BytesFromZZ(p,  a, num);

	for (long i = num-1; i >= 0; i--)
		ss << hex << setw(2) << setfill('0')
			 << (int)p[i];

	string result;

	result = ss.str();

	cout << result << endl;

	for (int i = 0; i < result.size(); i++)
		cout << result[i];
	cout << endl;

	ZZFromBytes(b, p, num);

	cout << b << endl;


// 	cout << "p= " << p;
/*
	cout << "b = ";
	cin >> b;
	cout << "n = ";
	cin >> n;

	cout << "\na = " << a;
	cout << "\nb = " << b;
	cout << "\nn = " << n;

	AddMod(x, a%n, b%n, n);
	cout << "\nx = " << x;
	x = AddMod(a%n, b%n, n);
	cout << "\nx = " << x;

	SubMod(x, a%n, b%n, n);
	cout << "\nx = " << x;
	x = SubMod(a%n, b%n, n);
	cout << "\nx = " << x;

	MulMod(x, a%n, b%n, n);
	cout << "\nx = " << x;
	x = MulMod(a%n, b%n, n);
	cout << "\nx = " << x;

	InvMod(x, a%n, n);
	cout << "\nx = " << x;
	x = InvMod(a%n, n);
	cout << "\nx = " << x;

	PowerMod(x, a%n, b%n, n);
	cout << "\nx = " << x;
	x = PowerMod(a%n, b%n, n);
	cout << "\nx = " << x;



/*
	ZZ d;
	GCD (d, a, b);
	cout << "\nd = " << d;
	d = GCD (a, b);
	cout << "\nd = " << d;

/*

void AddMod(ZZ& x, const ZZ& a, const ZZ& b, const ZZ& n); // x = (a+b)%n
ZZ AddMod(const ZZ& a, const ZZ& b, const ZZ& n);

void SubMod(ZZ& x, const ZZ& a, const ZZ& b, const ZZ& n); // x = (a-b)%n
ZZ SubMod(const ZZ& a, const ZZ& b, const ZZ& n);

void NegateMod(ZZ& x, const ZZ& a, const ZZ& n); // x = -a % n
ZZ NegateMod(const ZZ& a, const ZZ& n);

void MulMod(ZZ& x, const ZZ& a, const ZZ& b, const ZZ& n); // x = (a*b)%n
ZZ MulMod(const ZZ& a, const ZZ& b, const ZZ& n);

void SqrMod(ZZ& x, const ZZ& a, const ZZ& n); // x = a^2 % n
ZZ SqrMod(const ZZ& a, const ZZ& n);

void InvMod(ZZ& x, const ZZ& a, const ZZ& n);
ZZ InvMod(const ZZ& a, const ZZ& n);
// x = a^{-1} mod n (0 <= x < n); error is raised occurs if inverse
// not defined

long InvModStatus(ZZ& x, const ZZ& a, const ZZ& n);
// if gcd(a,b) = 1, then return-value = 0, x = a^{-1} mod n;
// otherwise, return-value = 1, x = gcd(a, n)

void PowerMod(ZZ& x, const ZZ& a, const ZZ& e, const ZZ& n);
ZZ PowerMod(const ZZ& a, const ZZ& e, const ZZ& n);

void PowerMod(ZZ& x, const ZZ& a, long e, const ZZ& n);
ZZ PowerMod(const ZZ& a, long e, const ZZ& n);

// x = a^e % n (e may be negative)




/*

void GCD(ZZ& d, const ZZ& a, const ZZ& b);
ZZ GCD(const ZZ& a, const ZZ& b);

// d = gcd(a, b) (which is always non-negative).  Uses a binary GCD
// algorithm.



void XGCD(ZZ& d, ZZ& s, ZZ& t, const ZZ& a, const ZZ& b);

//  d = gcd(a, b) = a*s + b*t.

// The coefficients s and t are defined according to the standard
// Euclidean algorithm applied to |a| and |b|, with the signs then
// adjusted according to the signs of a and b.

// The implementation may or may not Euclid's algorithm,
// but the coefficients a and t are always computed as if
// it did.


// special-purpose single-precision variants:

long GCD(long a, long b);
// return value is gcd(a, b) (which is always non-negative)

void XGCD(long& d, long& s, long& t, long a, long b);
//  d = gcd(a, b) = a*s + b*t.

//  The coefficients s and t are defined according to the standard
//  Euclidean algorithm applied to |a| and |b|, with the signs then
//  adjusted according to the signs of a and b.


*/

	c = a / b;
	cout << "\nc = " << c;
	div(x, a, b);
	cout << "\nx = " << x;

	c = a % b;
	cout << "\nc = " << c;
	rem(x, a, b);
	cout << "\nx = " << x;

	ZZ q, r;
	DivRem(q, r, a, b);
	cout << "\nq = " << q;
	cout << "\nr = " << r;



/*
// operator notation:

ZZ operator/(const ZZ& a, const ZZ& b);
ZZ operator/(const ZZ& a, long  b);

ZZ operator%(const ZZ& a, const ZZ& b);
long operator%(const ZZ& a, long b);

ZZ& operator/=(ZZ& x, const ZZ& b);
ZZ& operator/=(ZZ& x, long b);

ZZ& operator%=(ZZ& x, const ZZ& b);


// procedural versions:

void DivRem(ZZ& q, ZZ& r, const ZZ& a, const ZZ& b);
// q = floor(a/b), r = a - b*q.
// This implies that:
//    |r| < |b|, and if r != 0, sign(r) = sign(b)

void div(ZZ& q, const ZZ& a, const ZZ& b);
// q = floor(a/b)

void rem(ZZ& r, const ZZ& a, const ZZ& b);
// q = floor(a/b), r = a - b*q


// single-precision variants:

long DivRem(ZZ& q, const ZZ& a, long b);
// q = floor(a/b), r = a - b*q, return value is r.

long rem(const ZZ& a, long b);
// q = floor(a/b), r = a - b*q, return value is r.


// divisibility testing:

long divide(ZZ& q, const ZZ& a, const ZZ& b);
long divide(ZZ& q, const ZZ& a, long b);
// if b | a, sets q = a/b and returns 1; otherwise returns 0.

long divide(const ZZ& a, const ZZ& b);
long divide(const ZZ& a, long b);
// if b | a, returns 1; otherwise returns 0.





/*

// operator notation:

ZZ operator*(const ZZ& a, const ZZ& b);

ZZ& operator*=(ZZ& x, const ZZ& a);
ZZ& operator*=(ZZ& x, long a);

// procedural versions:

void mul(ZZ& x, const ZZ& a, const ZZ& b); // x = a * b

void sqr(ZZ& x, const ZZ& a); // x = a*a
ZZ sqr(const ZZ& a);

// PROMOTIONS: operator * and procedure mul support promotion
// from long to ZZ on (a, b).




	c = a + b;
	cout << "\nc = " << c;
	add(x, a, b);
	cout << "\nx = " << x;

	c = a - b;
	cout << "\nc = " << c;
	sub(x, a, b);
	cout << "\nx = " << x;


/*


// operator notation:

ZZ operator+(const ZZ& a, const ZZ& b);
ZZ operator-(const ZZ& a, const ZZ& b);
ZZ operator-(const ZZ& a); // unary -

ZZ& operator+=(ZZ& x, const ZZ& a);
ZZ& operator+=(ZZ& x, long a);

ZZ& operator-=(ZZ& x, const ZZ& a);
ZZ& operator-=(ZZ& x, long a);

ZZ& operator++(ZZ& x);  // prefix
void operator++(ZZ& x, int);  // postfix

ZZ& operator--(ZZ& x);  // prefix
void operator--(ZZ& x, int);  // postfix


// procedural versions:

void add(ZZ& x, const ZZ& a, const ZZ& b); // x = a + b
void sub(ZZ& x, const ZZ& a, const ZZ& b); // x = a - b
void SubPos(ZZ& x, const ZZ& a, const ZZ& b); // x = a-b; assumes a >= b >= 0.
void negate(ZZ& x, const ZZ& a); // x = -a

void abs(ZZ& x, const ZZ& a); // x = |a|
ZZ abs(const ZZ& a);

// PROMOTIONS: binary +, -, as well as the procedural versions add, sub
// support promotions from long to ZZ on (a, b).




/*   c = (a+1)*(b+1);
   cout << c << "\n";
*/

}
