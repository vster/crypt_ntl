#include <NTL/ZZ.h>
#include "convhex.h"
#include <ctime>

using namespace std;
using namespace NTL;

const long L = 512;
const long N = 160;


char h_hex = 2;
char p_hex_be[] = "d411a4a0e393f6aab0f08b14d18458665b3e4dbdce2544543fe365cf71c8622412db6e7dd02bbe13d88c58d7263e90236af17ac8a9fe5f249cc81f427fc543f7";
char q_hex_be[] = "b20db0b101df0c6624fc1392ba55f77d577481e5";
char g_hex_be[] = "b3085510021f999049a9e7cd3872ce9958186b5007e7adaf25248b58a3dc4f71781d21f2df89b71747bd54b323bbecc443ec1d3e020dadabbf7822578255c104";
char x_hex_be[] = "6b2cd935d0192d54e2c942b574c80102c8f8ef67";
char k_hex_be[] = "79577ddcaafddc038b865b19f8eb1ada8a2838c6";
char kinv_hex_be[] = "2784e3d672d972a74e22c67f4f4f726ecc751efa";
char m_hex_be[] = "0164b8a914cd2a5e74c4f7ff082c4d97f1edf880";

void genparams( ZZ &p, ZZ &q)
{

	time_t now = time(0);

	long err = 80;	
	// Prime number p with n bits long
	GenPrime(q, N, err);

	ZZ m;
	RandomLen(m, L-N);

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
	// cout << "\nm = \n" << m << endl;
	cout << "\nm = \n";
	show_dec_in_hex (m, L-N);
	cout << endl;

	// Проверка 
	ZZ r;
	r = (p-1)%q;

	cout << "\np = \n";
	show_dec_in_hex (p, L);
	long pb = NumBits( p );
	cout << "\nNumber of bits in p = " << pb << endl;
	cout << "\nq = \n";
	show_dec_in_hex (q, N);

	long qb = NumBits( q );
	cout << "\nNumber of bits in q = " << qb << endl;
}

int main()
{
	ZZ p;	// Модуль
	ZZ h;	// Произвольное число 1 < h < p-1
	ZZ q;	// Простое число, делитель (p-1)

/*
	//	time_t now = time(0);

	//	long seconds = (long)difftime(now,0);

	//	ZZ seed = conv<ZZ>(difftime(now,0));
	//	SetSeed( seed ); 
	//	genparams( p, q );
	//	RandomBnd(h, p-1);
*/
	get_dec_from_hex (p, p_hex_be, L);
	get_dec_from_hex (q, q_hex_be, N);
	h = h_hex;

	ZZ g, e;
	e = (p-1)/q;
	PowerMod(g, h%p, e%p, p);

	cout << "\np = \n"; show_dec_in_hex (p, L);	cout << endl;
	cout << "\nq = \n"; show_dec_in_hex (q, N); cout << endl;
	cout << "\nh = \n"; show_dec_in_hex (h, L); cout << endl;
	cout << "\ne = \n"; show_dec_in_hex (e, L-N); cout << endl;
	cout << "\ng = \n"; show_dec_in_hex (g, L); cout << endl;

	
	ZZ x, y;
	//	RandomBnd(x, p-1);			// Секретный ключ 
	get_dec_from_hex (x, x_hex_be, N);	
	PowerMod(y, g%p, x%p, p);	// Открытый ключ

	cout << "\nSecret key x = \n"; show_dec_in_hex (x, N);	cout << endl;
	cout << "\nPublic key y = \n"; show_dec_in_hex (y, L);	cout << endl;

	ZZ H;
	// RandomBnd(H, q-1);
	get_dec_from_hex (H, m_hex_be, N);		
	cout << "\nHash H = \n"; show_dec_in_hex (H, N);	cout << endl;

	// Генерация ЭЦП
	ZZ k, r, s;					
	while ( s == 0 )
	{
		// RandomBnd(k, q);			// Случайное число k
		get_dec_from_hex (k, k_hex_be, N);
		r = PowerMod(g%p, k%p, p) % q;
		if ( r == 0 )
			continue;
		s = (InvMod(k%q, q) * ((H + x * r )%q)) % q;
		if ( s == 0 )
			continue;
	}
	cout << "\nSession key k = \n"; show_dec_in_hex (k, N);	cout << endl;
	
	
	cout << "\nGenerate sign\n";
	cout << "\nr =  \n"; show_dec_in_hex (r, N);	cout << endl;
	cout << "s =  \n"; show_dec_in_hex (s, N);	cout << endl;


	// Проверка ЭЦП
	ZZ w, u1, u2, v;
	w = InvMod(s%q, q);
	u1 = (H * w) % q;
	u2 = (r * w) % q;
	v = ((PowerMod(g%p,u1%p,p)*PowerMod(y%p,u2%p,p))%p)%q;

	cout << "\nCheck sign\n";
	cout << "\nw =  \n"; show_dec_in_hex (w, N);	cout << endl;
	cout << "u1 = \n";	show_dec_in_hex (u1, N);	cout << endl;
	cout << "u2 = \n"; show_dec_in_hex (u2, N);		cout << endl;
	cout << "v =  \n"; show_dec_in_hex (v, N);	cout << endl;

	cout << endl;
	if ( v == r )
		cout << "v = r Sign is OK" << endl;
	else
		cout << "Sign is FAILED" << endl;

}