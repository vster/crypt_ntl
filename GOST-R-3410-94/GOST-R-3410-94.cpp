// ���������� ��������������� ���� � 34.10-94

#include <NTL/ZZ.h>
#include <ctime>

using namespace std;
using namespace NTL;


const long N = 256;			// q
const long L = 1024;		// p


void genparams( ZZ &p, ZZ &q, ZZ &a)
{

	long err = 80;	
	// Prime number p with n bits long
	GenPrime(q, N, err);

	ZZ m;
	RandomLen(m, L-N);
	// cout << "\nm = " << m << endl;

	cout << "\nGenerating p, q and a...\n";
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

	ZZ d, f;
//	ZZ f1 = ((p-1) * InvMod(q, p)) % p;
	ZZ f1 = m;
	for( d = 2; a == 0; d++ )
	{
		f = PowerMod(d%p, f1%p, p);
		if ( f >  1 )
		{	
			a = f;
			// cout << a << " ";
			break;
		}
	}
}



int main()
{
	ZZ p;	// ������
	ZZ h;	// ������������ ����� 1 < h < p-1
	ZZ q;	// ������� �����, �������� (p-1)
	ZZ a;

	time_t now = time(0);

	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	genparams( p, q, a );
	
	cout << "\np = \n" << p << endl;
	cout << "\nq = \n" << q << endl;
	cout << "\na = \n" << a << endl;

	ZZ x, y;
	RandomBnd(x, q-1);			// ��������� ���� 
//	x = 38;
	PowerMod(y, a%p, x%p, p);

	cout << "\nSecret key x = \n" << x << endl;
	cout << "\nPublic key y = \n" << y << endl;

	ZZ H;
	RandomBnd(H, q-1);
	// cout << "\nEnter hash < q: ";
	// cin >> H;
	//	H = 120;
	cout << "\nHash H = \n" << H << endl;

	// ��������� ���
	ZZ k, r, s;					

	while ( s == 0 )
	{
		RandomBnd(k, q);			// ��������� ����� k
		r = PowerMod(a%p, k%p, p) % q;
		if ( r == 0 )
			continue;
		s = (x * r + k * H ) % q;
		if ( s == 0 )
			continue;
	}

	cout << "\nSession key k = \n" << k << endl;
	
	cout << "\nGenerate sign\n";
	cout << "\nr =  \n" << r << endl;
	cout << "s =  \n" << s << endl;


	// �������� ���
	ZZ v, z1, z2, u;
	v = PowerMod(H, (q-2), q);
	z1 = (s * v) % q;
	z2 = (SubMod(q, r%q, q) * v) % q;
	u = ((PowerMod(a, z1, p) * PowerMod(y, z2, p)) % p) % q;

	cout << "\nCheck sign\n";
	cout << "\nv =  \n" << v << endl;
	cout << "z1 = \n" << z1 << endl;
	cout << "z2 = \n" << z2 << endl;
	cout << "u =  \n" << u << endl;

	cout << endl;
	if ( u == r )
		cout << "u = r Sign is OK" << endl;
	else
		cout << "Sign is FAILED" << endl;

	return 0;
}