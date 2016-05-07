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
	ZZ p;	// ������
	ZZ q;	// ������� �����, �������� (p-1)
	ZZ g;
	time_t begin, end;
	double seconds;

	// ������������� ���
	time_t now = time(0);
	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	// ��������� ���������� DSA
	begin = time(NULL);	
	genparams( p, q, g );
	end = time(NULL);

	seconds = difftime(end, begin);
	cout << "\nGeneration time = " << seconds << " sec" << endl;

	// ��������� ���������� � ��������� �����
	ZZ x, y;
	genkeys ( x, y, p, q, g );

	// ��������� ���� (��� ������� ��������� �����)
	ZZ H;
	RandomBnd(H, q-1);
	cout << "\nHash H = \n"; show_dec_in_hex (H, N);	cout << endl;

	// ��������� ���
	ZZ r, s;					
	gensign (r, s, x, H, p, q, g );

	// �������� ���
	ZZ w;
	verifysign ( w, r, s, y, H, p, q, g );

	return 0;
}