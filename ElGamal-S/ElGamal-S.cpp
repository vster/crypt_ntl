#include <NTL/ZZ.h>
#include <ctime>

using namespace std;
using namespace NTL;

long n = 1024; // Длина модуля поля

// Generation of params
void genparams(ZZ &p, ZZ &g)
{
	// ZZ p1;

	cout << "\nGeneration of params...\n";

	long err = 80;	
	// Prime number p with n bits long
	GenPrime(p, n, err);
	//	p = 29;
	// p1 = p-1;

	GenPrime(g, n, err);	// Первообразный корень
//	g = 5;

	cout << "\nDomain params\n";
	cout << "\np = \n" << p << endl;
	cout << "\ng = \n" << g << endl;
}

// Generation of keys
void genkeys (ZZ &x, ZZ &y, ZZ &p, ZZ &g)
{
	RandomBnd(x, p-1);
	//	x = 7;
	PowerMod(y, g%p, x%p, p);
	
	cout << endl;
	cout << "Secret key x = \n" << x << endl;
	cout << "\nPublic key y = \n" << "(" << p << ",\n" 
		 << g << ",\n" << y << ")" << endl;
}

// Generate sign
void gensign (ZZ &r, ZZ &s, ZZ &m, ZZ &x, ZZ &p, ZZ &g)
{
	ZZ k;		// Session key
	ZZ p1;

	p1 = p-1;

	while ( s == 0 )
	{
		RandomBnd(k,p-1);
		// Sign data
		PowerMod(r, g%p, k%p, p);
//		cout << "\nr = \n" << r << endl;
		if ( r == 0 )
			continue;

		ZZ s1, s2;	// Generate sign
		s1 = SubMod(m%p1, (x*r)%p1, p1);
//		cout << "\ns1 = \n" << s1 << endl;	
		if (InvModStatus(s2, k, p1))
			continue;

		s2 = InvMod(k%p1, p1);
//		cout << "\ns2 = \n" << s2 << endl;
		s = ( s1 * s2 )%p1;
//		cout << "\ns = \n" << s << endl;
	}

	cout << "\nSign\n";
	cout << "\nr =\n" << r << endl;
	cout << "\ns = \n" << s << endl;
}

// Verify sign
void verifysign ( ZZ &r, ZZ &s, ZZ &m, ZZ &y, ZZ &p, ZZ &g )
{
	ZZ ts1, ts2;
	ts1 = (PowerMod(y%p, r%p, p) * PowerMod(r%p, s%p, p)) % p;
	ts2 = PowerMod(g%p, m%p, p);
	
	cout << "\nCheck sign\n";
	cout << "\nts1 = \n" << ts1 << endl;
	cout << "\nts2 = \n" << ts2 << endl;
	cout << endl;
	if (ts1 == ts2)
		 cout << "ts1 = ts2\n" << "Sign is OK";
	 else
		 cout << "Sign is BAD";
	 cout << endl;
}

int main()
{
	ZZ p1, q;

	time_t now = time(0);
	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	ZZ p, g;	// Domain params
	genparams( p, g );
	p1 = p-1;
	
	// Generate keys
	ZZ x, y;
	genkeys ( x, y, p, g );	

	// Gen data - hash
	ZZ m;
//	m = 3;
	RandomBnd(m, p-1);
//	GenPrime(M, n, err);
	cout << "\nInitial data m = \n" << m << endl;

	// Generate sign	
	ZZ r, s;
	gensign ( r, s, m, x, p, g);

	// Verify sign
	verifysign ( r, s, m, y, p, g );

	return 0;
}