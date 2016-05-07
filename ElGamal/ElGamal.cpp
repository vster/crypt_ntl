#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

void primdiv ( ZZ a )
{
	ZZ q, m;
	
	long NumTrials=10;
	cout << "\nPrime dividers: ";
	for ( long m = 2, i = 0; (a > 1) && (i < 5) ; )
	{
		if ( (a%m) == 0)		//проверка делиться ли число без остатка
		{
			cout << m << " ";	//вывод множителя если делится
			a /= m;				// деление числа на множитель
			i++;
		} 
		else
		{
			m = NextPrime( ++m, NumTrials);
		}
	}
}

int main()
{
	ZZ p, g, q;
	
	long n = 256;				// Длина модуля поля
	long err = 80;	
	// Prime number p with n bits long
	GenPrime(p, n, err);
	cout << "p = " << p << endl;
	
	long NumTrials = 10;
	if ( ProbPrime(p, NumTrials) )
		cout << "Number p is prime" << endl;
	else
		cout << "Number p is not prime" << endl;
	
//	primdiv( p-1 );
//	cout << "\ng = ";
//	cin >> g;
//	g = 2;			// Первообразный корень
	GenPrime(g, n, err);

	ZZ x, y;
	RandomBnd(x, p-1);
	PowerMod(y, g, x, p);
	
	cout << endl;
	cout << "Secret key x = " << x << endl;
	cout << "Public key y = " << "(" << p << "," 
		 << g << "," << y << ")" << endl;

	
	for (long m = 8; m < 256; m++)			// Длина исходных данных (бит)
	{
		ZZ M;
		GenPrime(M, m, err);
		cout << "\nInitial data M = " << M << endl;

		ZZ k;
		RandomBnd(k, p-1);		// Генерим сессионый ключ k
		cout << "\nSession key k = " << k << endl;
	
		ZZ a, b;
		PowerMod( a, g%p, k%p, p );
		b = (PowerMod(y%p, k%p, p) * M) % p; 
		cout << "\nEncrypting\n";
		cout << "(a,b) = " << "(" << a << "," << b << ")" << endl;

		ZZ M1;
		M1 = (b * PowerMod( a%p, (p-1-x)%p, p)) % p;
		cout << "\nDecrypting\n";
		cout << "M1 = " << M1 << endl;

		if ( M == M1 )
			cout << "\nEncryptig-Decrypting is OK\n";
		else
			cout << "\nEncryptig-Decrypting is FAILD\n";
	}

	return 0;
}