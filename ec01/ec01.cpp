#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "convhex.h"

using namespace std;
using namespace NTL;

const long L = 32;
ZZ p = conv<ZZ>(17); 
ZZ a = conv<ZZ>(5);
ZZ b = conv<ZZ>(7);	

class Qxy
{
private:
	ZZ_p x, y;
public:
	Qxy ( )
	{ };
	Qxy( ZZ_p xx, ZZ_p yy )
	{ x = xx; y = yy; }
	void getQxy ( ZZ_p xx, ZZ_p yy )
	{ x  = xx; y = yy; }
	void getQxy ( int xx, int yy )
	{ x  = conv<ZZ_p>(xx); y = y = conv<ZZ_p>(yy); }
	void getQxy ( long xx, long yy )
	{ x  = conv<ZZ_p>(xx); y = y = conv<ZZ_p>(yy); }
	void getQxy ( ZZ xx, ZZ yy )
	{ x  = conv<ZZ_p>(xx); y = conv<ZZ_p>(yy); }
	void putQxy ( )
	{	cout << "(" << x << "," << y << ")"; } 
	bool operator == ( Qxy q2 )
	{
		if ( (x == q2.x) & (y == q2.y) )
			return true;
		else
			return false;
	}
	
	Qxy operator + ( Qxy q2 )
	{
		Qxy tq, tq0;
		tq0.getQxy(conv<ZZ_p>(0),conv<ZZ_p>(0));
		ZZ_p dx, dy, lmb;
		tq.x = x; tq.y = y;
		if ( q2 == tq0 )
			return tq;
		if ( tq == tq0 )
			return q2;
		if ((x == q2.x) & ( y != q2.y)) 
		{
			return tq0;
		}
		if ((x == q2.x ) & (y == q2.y))
		{
			tq = q2.double_p();
			return tq;
		}	
		dy = q2.y - y;
		dx = q2.x - x;
		lmb = dy / dx;
		tq.x = lmb * lmb - x - q2.x;
		tq.y = lmb * ( x - tq.x) - y;
		return tq;
	}
	Qxy double_p ( )
	{
		Qxy tq2;
		ZZ_p lmb;
		lmb = ( 3*x*x + conv<ZZ_p>(a)) / (2*y);
		tq2.x = lmb * lmb - 2 * x;
		tq2.y = lmb * ( x - tq2.x ) - y;
		return tq2;
	}

	Qxy operator * ( ZZ k )
	{
		Qxy tq, tq2, tq0;
		tq0.getQxy(conv<ZZ_p>(0),conv<ZZ_p>(0));
		tq.x = x; tq.y = y;
		
		Qxy sum;
		Qxy dtq;
		long len = NumBits(k);
		
		dtq = tq;
		sum = tq0;
		for ( long i = 0; i < len; i++ )
		{
			if (bit(k,i)) 
				sum = sum + dtq;
			dtq = dtq.double_p();
		}
		return sum;	
	}	
};

	ZZ muln (ZZ &a, ZZ &k )
	{
		ZZ sum;
		ZZ da;
		long len = NumBits(k);
		
		da = a;
		sum = 0;
		for ( long i = 0; i < len; i++ )
		{
			if (bit(k,i)) 
				sum += da;
			da = 2 * da;
			cout << i << " " << da << " " << sum << endl;

		}
		return sum;
	}

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


int main()
{
	ZZ_p::init(p);

	// Генерация начальных параметров
	Qxy P, P1, P2, P3, P4;
	ZZ q;
	ZZ bpn;
	
	genparam_q ( P, q );
/*
	bpn	= 0;
	genparam_P ( P1, q, bpn );
	P1.putQxy();
*/
	bpn = 1;
	genparam_P ( P1, q, bpn );	
	cout << "\nP1 = ";
	P1.putQxy();
	cout << endl;

	ZZ k;

	Qxy P0;
	P0.getQxy(conv<ZZ_p>(0),conv<ZZ_p>(0));

	P4 = P0 + P1;
	P4.putQxy();



	k = 0;
	P4 = P1 * k;
	cout << "\nk  = " << k << " P1 = ";
	P4.putQxy();
	cout << endl;

	
	k = 1;
	P4 = P1 * k;
	cout << "\nk  = " << k << " P1 = ";
	P4.putQxy();
	cout << endl;

	k = 13;
	P4 = P1 * k;
	cout << "\nk  = " << k << " P1 = ";
	P4.putQxy();
	cout << endl;

	k = 23;
	P4 = P1 * k;
	cout << "\nk  = " << k << " P1 = ";
	P4.putQxy();
	cout << endl;



	return 0;
}