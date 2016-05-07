#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
	ZZ p, g;


	for (long n = 16; n < 128; n++)
	{					// Длина модуля поля

		long err = 80;	
		// Prime number p with n bits long
		GenPrime(p, n, err);
		g = 2;						// Первообразный корень

		ZZ ka, kb;
		RandomBnd(ka, p-1);			// Секретный ключ A
		RandomBnd(kb, p-1);			// Секретный ключ B

		cout << "Secret key ka : " << ka << endl;
		cout << "Secret key kb : " << kb << endl;

		ZZ Ka, Kb;
	
		PowerMod( Ka, g, ka, p );
		PowerMod( Kb, g, kb, p );

		cout << "Public key Ka : " << Ka << endl;
		cout << "Public key Kb : " << Kb << endl;

		ZZ K, K1;
		PowerMod( K, Kb, ka, p );
		PowerMod( K1, Ka, kb, p );

		cout << "Common key K  : " << K << endl;
		cout << "Common key K1 : " << K1 << endl;

		if (K == K1)
			cout << "DH is OK";
		else
			cout << "DH is FAILED";
		cout << endl;
	}
}
