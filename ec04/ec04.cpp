// ГОСТ Р 34.10-2001

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <ctime>
#include "convhex.h"
#include "QxyNTL.h"


using namespace std;
using namespace NTL;

const long L = 8;
ZZ p = conv<ZZ>(37); 
ZZ a = conv<ZZ>(3);
ZZ b = conv<ZZ>(7);	


// Генерация начальных параметров
void genparams ( Qxy &P, ZZ &q, ZZ &bpn )
{
	ZZ i;
	ZZ x, y;
	ZZ f1, f2;

	for ( x = 0, i = 0; x < p; x++)
		for ( y = 0; y < p; y++)
		{
			f1 = PowerMod(y, 2, p);
			f2 = (PowerMod(x, 3, p) + a * x + b)%p;
			if ( f1 == f2 )
			{
				if ( i == bpn )
					P.getQxy(x,y);
				i++;
			}
		}
	q = i+1;
	cout << "Parameters of elliptic curve" << endl;
	cout << "\np = " << p;
	cout << "\na = " << a;
	cout << "\nb = " << b;
	cout << "\nbpn = " << bpn << endl;
	cout << "\nq = " << q << endl;
	cout << "\nP = "; P.putQxy(); cout << endl;
}

void genparam_q ( Qxy &P, ZZ &q )
{
	ZZ i;
	ZZ x, y;
	ZZ f1, f2;

	for ( x = 0, i = 0; x < p; x++)
		for ( y = 0; y < p; y++)
		{
			f1 = PowerMod(y, 2, p);
			f2 = (PowerMod(x, 3, p) + a * x + b)%p;
			if ( f1 == f2 ) i++;	
		}
	q = i+1;
	// simpdiv( q );
	long NumTrials = 10;
	if ( !ProbPrime( q, NumTrials) )
		cout << "\nq is not prime! Please, change params (p,a,b)." << endl;
	
	cout << "\np = " << p;
	cout << "\na = " << a;
	cout << "\nb = " << b;
	cout << "\nq = " << q << endl;
}



void genparam_P ( Qxy &P, ZZ &q, ZZ &bpn )
{
	ZZ i;
	ZZ x, y;
	ZZ f1, f2;

	for ( x = 0, i = 0; x < p; x++)
		for ( y = 0; y < p; y++)
		{
			f1 = PowerMod(y, 2, p);
			f2 = (PowerMod(x, 3, p) + a * x + b)%p;
			if ( f1 == f2)
			{
				if (i == bpn)
				{ 
					P.getQxy(x,y);	
					goto out;
				}
				i++;
			}
		}
out:	{}

}
// Тест параметров ЭК
void testparams ( Qxy &P, ZZ &q)
{
	Qxy Q0;
	Q0.getQxy(conv<ZZ_p>(0),conv<ZZ_p>(0));
	// Тест: некая точка * порядок кривой = нулевая точка
	Qxy TQ = P*q;		
	cout << "\nTest Q = ";
	TQ.putQxy();
	cout << "\nMust be (0,0)\n" << endl;
	if ( TQ == Q0 )
		cout << "Test of EC is OK\n";
	else
		cout << "Test of EC is FAILD\n";
}
// Генерация ключей 
void genkeys ( ZZ &d, Qxy &Q, Qxy &P, ZZ &q ) 
{
	RandomBnd(d, q-1);				// Закрытый ключ	1 < d < q-1
	// d = 15;
	Q = P*d;			// Открытый ключ
	cout << "\nPrivate key d = " << d << endl;
	cout << "Public key Q = ";
	Q.putQxy();
	cout << endl;
}

// Генерация ЭЦП
void gensign (ZZ &r, ZZ &s, ZZ &e, ZZ &d, Qxy &P, ZZ &q)
{
	ZZ k;
	Qxy C;

	// srand (time(NULL));
	while ( true )
	{
		RandomBnd(k, q-1);
		if ( GCD(k,q) > 1 )
			continue;
		// k = 5;
		C = P*k; 
		r = (conv<ZZ>(C.putx()))%q;
		if ( r == 0)
			continue;
		
		// ZZ k1;
		// if (InvModStatus( k1, k, q ))
		// 	continue;
		// k1 = InvMod(k,q);
		// s = (k1*((H+r*d)%q))%q;
		s = (r*d + k*e)%q;
		if ((r>0)&(s>0))
			break;
	}
	
	cout << "k = " << k << endl
		 << "(r,s) = (" 
		 << r << "," << s << ")" << endl;
}

// Проверка ЭЦП
void verifysign (ZZ &R, ZZ &r, ZZ &s, ZZ &e, Qxy &Q, Qxy &P, ZZ &q  )
{
	ZZ v, z1, z2;
	Qxy C2;
	// ZZ s1;
	ZZ e1;
	if (InvModStatus( v, e, q ))
	{
		cout << "\nError in sign\n";
		goto end;
	}	
	v = InvMod(e,q);
	z1 = (s*v)%q;
	z2 = (-r*v)%q;
	C2 = P*z1 + Q*z2; 
	R = (conv<ZZ>(C2.putx()))%q;

	cout << "\nv = " << v << endl
	<< "z1 = " << z1 << endl
	<< "z2 = " << z2 << endl	
	<< "C2 = ";
	C2.putQxy();
	cout << endl;
	cout << "R = " << R << endl;
end:
	if ( r == R )
		cout << "\nr = R\nSign is OK";
	else
		cout << "Sign is FAILD";
	cout << endl;

}

int main()
{
	time_t begin, end;
	double seconds;
	ZZ_p::init(p);

	// Инициализация ДСЧ
	// srand (time(NULL));
	time_t now = time(0);
	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	// ZZ pt;
	// long err = 80;
	// GenPrime(pt, L, err);
	// cout << pt << endl;

	// Генерация начальных параметров
	Qxy P;
	ZZ q;
	ZZ bpn;
	
	cout << "Generation of parameters...\n";
	begin = time(NULL);
	genparam_q ( P, q );
	end = time(NULL);
	
	// seconds = difftime(end, begin);


	// bpn	= 1;		// base point number
	RandomBnd(bpn, q-1);	
	genparam_P ( P, q, bpn );
	cout << "\nbpn = " << bpn << endl; 
	cout << "\nP = ";
	P.putQxy();
	cout << endl;

	seconds = difftime(end, begin);
	cout << "\nGeneration = " << seconds << " sec" << endl;
	
	// Тест параметров ЭК
	testparams ( P, q );

	// Генерация ключей
	ZZ d;				// Закрытый ключ	1 < d < q-1
	Qxy Q;				// Открытый ключ
	genkeys ( d, Q, P, q );

	ZZ e;
	// e = 20;
	RandomBnd(e, q-1);		// Хэш
	if ( e == 0 )
		e = 1;
	cout << "\nHash e = " << e << endl << endl;	


	// Генерация ЭЦП
	cout << "\nGeneration of sign\n";
	ZZ r, s;
	gensign ( r, s, e, d, P, q );

	// Проверка ЭЦП
	cout << "\nVerification of sign\n";	
	ZZ R;
	verifysign ( R, r, s, e, Q, P, q  );

	return 0;
}