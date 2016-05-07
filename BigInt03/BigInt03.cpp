#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;

int main()
{

	ZZ p;
	p = 29;

	ZZ_p::init(p);

	ZZ_p a, b, c;

	random(a);
	random(b);


	cout << "\na = " << a;
	cout << "\nb = " << b;


	ZZ_p J;

	J = 1728 * ( 4 * power (a, 3) ) * ( 4 * power (a, 3) + 27 * power(b, 3));

	cout << "\nJ = " << J;


	c = a + b;
	cout << "\na+b = " << c;
	c = a - b;
	cout << "\na-b = " << c;
	c = a * b;
	cout << "\na*b = " << c;
	c = a / b;
	cout << "\na/b = " << c;



/*
	long l;

	cout << "l = ";
	cin >> l;

	long NumTrials=10;

	RandomPrime(p, l, NumTrials);

	ZZ_p::init(p);

	cout << "\np = " << p;

	ZZ_p a, b, c, x;

	cout << "\na = ";
	cin >> a;
	cout << "b = ";
	cin >> b;

	cout << "\na = " << a;
	cout << "\nb = " << b;


	random (x);
	cout << "\nx = " << x;
	x = random_ZZ_p();

/*
void random(ZZ_p& x);
ZZ_p random_ZZ_p();
// x = random element in ZZ_p.

	ZZ e;
	cout << "\ne = ";
	cin >> e;

	power (x, a, e);
	cout << "\nx = " << x;
	x = power (a, e);
	cout << "\nx = " << x;

/*
void power(ZZ_p& x, const ZZ_p& a, const ZZ& e); // x = a^e (e may be negative)
ZZ_p power(const ZZ_p& a, const ZZ& e); // functional variants

void power(ZZ_p& x, const ZZ_p& a, long e);
ZZ_p power(ZZ_p& x, const ZZ_p& a, long e);


	c = a / b;
	cout << "\n\nc = " << c;
	div (x, a, b);
	cout << "\nx = " << x;

	c = 1 / b;
	cout << "\n\nc = " << c;
	inv (x, b);
	cout << "\nx = " << x;


/*

// operator notation:

ZZ_p operator/(const ZZ_p& a, const ZZ_p& b);

ZZ_p& operator/=(ZZ_p& x, const ZZ_p& b);
ZZ_p& operator/=(ZZ_p& x, long b);


// procedural versions:


void div(ZZ_p& x, const ZZ_p& a, const ZZ_p& b);
// x = a/b.

// By default, if b is not invertible, an error is raised.  However,
// one can override this default behavior by defining an error handler
// void H(const ZZ_p& b), and setting ZZ_p::DivHandler = H.  Then if b
// != 0 and b is not invertible, the function H is invoked with b as
// its argument.  When this happens, p is of course not prime, and
// GCD(p, rep(b)) is a nontrivial factor.

void inv(ZZ_p& x, const ZZ_p& a); // x = 1/a
ZZ_p inv(const ZZ_p& a);

// Error handling is the same as above.

// PROMOTIONS: operator / and procedure div provide promotions
// from long to ZZ_p on (a, b)


	c = a * b;
	cout << "\n\nc = " << c;
	mul (x, a, b);
	cout << "\nx = " << x;

//	c = a - b;
//	cout << "\n\nc = " << c;
	sqr (x, a);
	cout << "\nx = " << x;

/*
	c = -a;
	cout << "\n\nc = " << c;
	negate (x, a);
	cout << "\nx = " << x;


/*

// operator notation:

ZZ_p operator*(const ZZ_p& a, const ZZ_p& b);

ZZ_p& operator*=(ZZ_p& x, const ZZ_p& b);
ZZ_p& operator*=(ZZ_p& x, long b);

// procedural versions:


void mul(ZZ_p& x, const ZZ_p& a, const ZZ_p& b); // x = a * b

void sqr(ZZ_p& x, const ZZ_p& a); // x = a^2
ZZ_p sqr(const ZZ_p& a); // x = a^2

// PROMOTIONS: operator * and procedure mul provide promotions
// from long to ZZ_p on (a, b)

	c = a + b;
	cout << "\nc = " << c;
	add (x, a, b);
	cout << "\nx = " << x;

	c = a - b;
	cout << "\nc = " << c;
	sub (x, a, b);
	cout << "\nx = " << x;

	c = -a;
	cout << "\nc = " << c;
	negate (x, a);
	cout << "\nx = " << x;

/*
// operator notation:

ZZ_p operator+(const ZZ_p& a, const ZZ_p& b);
ZZ_p operator-(const ZZ_p& a, const ZZ_p& b);
ZZ_p operator-(const ZZ_p& a); // unary -

ZZ_p& operator+=(ZZ_p& x, const ZZ_p& b);
ZZ_p& operator+=(ZZ_p& x, long b);

ZZ_p& operator-=(ZZ_p& x, const ZZ_p& b);
ZZ_p& operator-=(ZZ_p& x, long b);

ZZ_p& operator++(ZZ_p& x);  // prefix
void operator++(ZZ_p& x, int);  // postfix

ZZ_p& operator--(ZZ_p& x);  // prefix
void operator--(ZZ_p& x, int);  // postfix

// procedural versions:


void add(ZZ_p& x, const ZZ_p& a, const ZZ_p& b); // x = a + b
void sub(ZZ_p& x, const ZZ_p& a, const ZZ_p& b); // x = a - b
void negate(ZZ_p& x, const ZZ_p& a); // x = -a

// PROMOTIONS: binary +, - and procedures add, sub provide promotions
// from long to ZZ_p on (a, b)
*/



}
