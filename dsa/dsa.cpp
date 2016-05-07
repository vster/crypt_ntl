#include <NTL/ZZ.h>
#include <ctime>

using namespace std;
using namespace NTL;


void genparams( ZZ &p, ZZ &q)
{
//	ZZ p;	// Модуль
//	ZZ q;	// простое число, делитель (p-1)

	time_t now = time(0);

	//	long seconds = (long)difftime(now,0);

	// ZZ seed = conv<ZZ>(difftime(now,0));
	// SetSeed( seed ); 
	long N = 256;
	long L = 2048;
	long err = 80;	
	// Prime number p with n bits long
	GenPrime(q, N, err);

	ZZ m;
	RandomLen(m, L-N);
	// cout << "\nm = " << m << endl;

	cout << "\nGenerating p and q...\n";
	long NumTrials = 20;
	for (long i = 0; i < 10000; i++, m++)
	{
		p = q * m + 1;
		
		if (ProbPrime(p, NumTrials))
		{
			cout << "\ni = " << i << endl;
			cout << "OK" << endl;
			break;
		}
	}
	cout << "\nm = \n" << m << endl;

	// Проверка 
	ZZ r;
	r = (p-1)%q;

	// cout << "\nr = " << r << endl;
	cout << "\np = \n" << p << endl;
/*
	if (ProbPrime(p, NumTrials))
		cout << "\np is Prime" << endl;
	else
		cout << "\np is not Prime" << endl;
*/
	long pb = NumBits( p );
	cout << "\nNumber of bits in p = " << pb << endl;
	cout << "\nq = \n" << q << endl;
	long qb = NumBits( q );
	cout << "\nNumber of bits in q = " << qb << endl;
}



int main()
{
	ZZ p;	// Модуль
	ZZ h;	// Произвольное число 1 < h < p-1
	ZZ q;	// Простое число, делитель (p-1)

	time_t now = time(0);

//	long seconds = (long)difftime(now,0);

	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 
	//long n = 32;
	// long err = 80;	
	// Prime number p with n bits long
	// GenPrime(p, n, err);
	//	p = 941;
	// cout << "p = " << p << endl;

	genparams( p, q );
	RandomBnd(h, p-1);
	
//	cout << "\nEnter q: ";
//	cin >> q;
//	q = 47;

	ZZ g, e;
	e = (p-1)/q;
	PowerMod(g, h%p, e%p, p);

	cout << "\np = \n" << p << endl;
	cout << "\nq = \n" << q << endl;
	cout << "\nh = \n" << h << endl;
	cout << "\ne = \n" << e << endl;
	cout << "\ng = \n" << g << endl;	

	ZZ x, y;
	RandomBnd(x, p-1);			// Секретный ключ 
//	x = 38;
	PowerMod(y, g%p, x%p, p);

	cout << "\nSecret key x = \n" << x << endl;
	cout << "\nPublic key y = \n" << y << endl;

	ZZ H;
	RandomBnd(H, q-1);
	// cout << "\nEnter hash < q: ";
	// cin >> H;
	//	H = 120;
	cout << "\nHash H = \n" << H << endl;

	// Генерация ЭЦП
	ZZ k, r, s;					
	while ( s == 0 )
	{
		RandomBnd(k, q);			// Случайное число k
		r = PowerMod(g%p, k%p, p) % q;
		if ( r == 0 )
			continue;
//	ZZ k1;
//	k1 = InvMod(k%q, q);
//	ZZ control = (k1 * k)%q;
		s = (InvMod(k%q, q) * ((H + x * r )%q)) % q;
		if ( s == 0 )
			continue;
	}
	cout << "\nSession key k = \n" << k << endl;
	
	
	cout << "\nGenerate sign\n";
	cout << "\nr =  \n" << r << endl;
//	cout << "k1 = " << k1 << endl;
//	cout << "control = " << control << endl;
	cout << "s =  \n" << s << endl;


	// Проверка ЭЦП
	ZZ w, u1, u2, v;
	w = InvMod(s%q, q);
	u1 = (H * w) % q;
	u2 = (r * w) % q;
	v = ((PowerMod(g%p,u1%p,p)*PowerMod(y%p,u2%p,p))%p)%q;

	cout << "\nCheck sign\n";
	cout << "\nw =  \n" << w << endl;
	cout << "u1 = \n" << u1 << endl;
	cout << "u2 = \n" << u2 << endl;
	cout << "v =  \n" << v << endl;

	cout << endl;
	if ( v == r )
		cout << "v = r Sign is OK" << endl;
	else
		cout << "Sign is FAILED" << endl;


}