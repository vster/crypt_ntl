#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <ctime>
#include "convhex.h"
#include "QxyNTL.h"

using namespace std;
using namespace NTL;

extern ZZ p; 
extern ZZ a;
extern ZZ b;

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
	long NumTrials = 10;
	if ( !ProbPrime( q, NumTrials) )
	cout << "\nq is not prime! Please, change params (p, a or b)." << endl;
	cout << "Parameters of elliptic curve" << endl;
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
	cout << "\nPrivate key d = \n" << d << endl;
	cout << "\nPublic key Q = \n";
	Q.putQxy();
	cout << endl;
}

// Генерация ЭЦП
void gensign (ZZ &r, ZZ &s, ZZ &H, ZZ &d, Qxy &P, ZZ &q)
{
	ZZ k;
	Qxy Q;

	// srand (time(NULL));
	while ( true )
	{
		RandomBnd(k, q-1);
		if ( GCD(k,q) > 1 )
			continue;
		// k = 5;
		Q = P*k;
		r = (conv<ZZ>(Q.putx()))%q;
		if ( r == 0)
			continue;
		
		ZZ k1;
		if (InvModStatus( k1, k, q ))
			continue;
		k1 = InvMod(k,q);
		s = (k1*((H+r*d)%q))%q;
		if ( s > 0)
			break;
	}
	
	cout << "\nk = \n" << k << endl;
	cout << "\nr = \n" << r << endl;
	cout << "\ns = \n" << s << endl;
}

// Проверка ЭЦП
void verifysign (ZZ &v, ZZ &r, ZZ &s, ZZ &H, Qxy &Q, Qxy &P, ZZ &q  )
{
	ZZ u1, u2;
	Qxy Q2;
	ZZ s1;
	if (InvModStatus( s1, s, q ))
	{
		cout << "\nError in sign\n";
		goto end;
	}	
	s1 = InvMod(s,q);
	u1 = (s1*H)%q;
	u2 = (s1*r)%q;
	Q2 = P*u1 + Q*u2; 
	v = (conv<ZZ>(Q2.putx()))%q;

	cout << "\nu1 = \n" << u1 << endl
	<< "\nu2 = \n" << u2 << endl	
	<< "\nPoint Q2 = \n";
	Q2.putQxy();
	// cout << endl;
	cout << "\nv = \n" << v << endl;
end:
	if ( r == v )
		cout << "\nr = v\nSign is OK";
	else
		cout << "Sign is FAILD";
	cout << endl;

}

