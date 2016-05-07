#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <ctime>
#include "convhex.h"
#include "QxyNTL.h"
#include "ecdsa.h"

using namespace std;
using namespace NTL;

const long L = 8;
ZZ p = conv<ZZ>(409); 
ZZ a = conv<ZZ>(3);
ZZ b = conv<ZZ>(41);

int main()
{
	time_t begin, end;
	double seconds;
	ZZ_p::init(p);

	// Инициализация ДСЧ
	time_t now = time(0);
	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	// Генерация начальных параметров
	Qxy P;
	ZZ q;
	ZZ bpn;
	
	cout << "Generation of parameters...\n";
	begin = time(NULL);
	genparam_q ( P, q );
	end = time(NULL);
	
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

	// Генерим хэш < q-1
	ZZ H;
	// H = 20;
	RandomBnd(H, q-1);		// Хэш
	cout << "\nHash H = " << H << endl << endl;	

	// Генерация ЭЦП
	cout << "\nGeneration of sign\n";
	ZZ r, s;
	gensign ( r, s, H, d, P, q );

	// Проверка ЭЦП
	cout << "\nVerification of sign\n";	
	ZZ v;
	verifysign ( v, r, s, H, Q, P, q  );

	return 0;
}