#include <NTL/ZZ.h>
#include "convhex.h"
#include <ctime>
#include "dsa.h"

using namespace std;
using namespace NTL;

extern long N;
extern long L;

void genparams( ZZ &p, ZZ &q, ZZ &g )
{
	ZZ m, h;
	time_t now = time(0);

	long err = 80;	
	GenPrime(q, N, err);

	RandomLen(m, L-N);

	cout << "\nGenerating dsa params: p, q and g...\n";
	long NumTrials = 20;
	for (long i = 0; i < 10000; i++, m++)
	{
		p = q * m + 1;
		
		if (ProbPrime(p, NumTrials))
		{
			// cout << "\ni = " << i << endl;
			// cout << "OK" << endl;
			break;
		}
	}

	RandomBnd(h, p-1);
	
	ZZ e = (p-1)/q;
	PowerMod(g, h%p, e%p, p);

	cout << "\np = \n"; show_dec_in_hex (p, L);	cout << endl;
	cout << "\nq = \n"; show_dec_in_hex (q, N); cout << endl;
	cout << "\nh = \n"; show_dec_in_hex (h, L); cout << endl;
	cout << "\ng = \n"; show_dec_in_hex (g, L); cout << endl;
}

// Генерация секретного и открытого ключа
void genkeys ( ZZ &x, ZZ &y, ZZ &p, ZZ &q, ZZ &g )
{
	RandomBnd(x, p-1);			// Секретный ключ 
	PowerMod(y, g%p, x%p, p);	// Открытый ключ

	cout << "\nSecret key x = \n"; show_dec_in_hex (x, L);	cout << endl;
	cout << "\nPublic key y = \n"; show_dec_in_hex (y, L);	cout << endl;
}

// Генерация ЭЦП
void gensign (ZZ &r, ZZ &s, ZZ &x, ZZ &H, ZZ &p, ZZ &q, ZZ &g )
{
	ZZ k;
	while ( s == 0 )
	{
		RandomBnd(k, q);			// Случайное число k
		r = PowerMod(g%p, k%p, p) % q;
		if ( r == 0 )
			continue;
		s = (InvMod(k%q, q) * ((H + x * r )%q)) % q;
		if ( s == 0 )
			continue;
	}
	cout << "\nGenerate sign\n";
	cout << "\nSession key k = \n"; show_dec_in_hex (k, N);	cout << endl;
	cout << "\nr =  \n"; show_dec_in_hex (r, N);	cout << endl;
	cout << "s =  \n"; show_dec_in_hex (s, N);	cout << endl;
}
// Проверка ЭЦП
void verifysign ( ZZ &w, ZZ &r, ZZ &s, ZZ &y, ZZ &H, ZZ &p, ZZ &q, ZZ &g )
{
	ZZ u1, u2, v;
	w = InvMod(s%q, q);
	u1 = (H * w) % q;
	u2 = (r * w) % q;
	v = ((PowerMod(g%p,u1%p,p)*PowerMod(y%p,u2%p,p))%p)%q;

	cout << "\nCheck sign\n";
	cout << "\nw =  \n"; show_dec_in_hex (w, N);	cout << endl;
	cout << "\nu1 = \n"; show_dec_in_hex (u1, N);	cout << endl;
	cout << "\nu2 = \n"; show_dec_in_hex (u2, N);	cout << endl;
	cout << "\nv =  \n"; show_dec_in_hex (v, N);	cout << endl;

	cout << endl;
	if ( v == r )
		cout << "v = r \nSign is OK" << endl;
	else
		cout << "Sign is FAILED" << endl;
}