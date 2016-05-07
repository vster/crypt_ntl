#include <NTL/ZZ.h>
#include "convhex.h"
#include <ctime>
#include "dsa.h"

using namespace std;
using namespace NTL;

long N = 256;
long L = 1024;

int main()
{
	ZZ p;	// Модуль
	ZZ q;	// Простое число, делитель (p-1)
	ZZ g;
	time_t begin, end;
	double seconds;

	// Инициализация ДСЧ
	time_t now = time(0);
	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	// Генерация параметров DSA
	begin = time(NULL);	
	genparams( p, q, g );
	end = time(NULL);

	seconds = difftime(end, begin);
	cout << "\nGeneration time = " << seconds << " sec" << endl;

	// Генерация секретного и открытого ключа
	ZZ x, y;
	genkeys ( x, y, p, q, g );

	// Генерация хеша (для примера случайное число)
	ZZ H;
	RandomBnd(H, q-1);
	cout << "\nHash H = \n"; show_dec_in_hex (H, N);	cout << endl;

	// Генерация ЭЦП
	ZZ r, s;					
	gensign (r, s, x, H, p, q, g );

	// Проверка ЭЦП
	ZZ w;
	verifysign ( w, r, s, y, H, p, q, g );

	return 0;
}