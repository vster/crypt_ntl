#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
	ZZ p, q;
	ZZ n, phi;
	ZZ e, d;
	
	long l = 256;
	long err = 80;	
	// Prime number p with l bits long
	GenPrime(p, l, err);
	// Prime number q with l bits long
	GenPrime(q, l, err);

	n = p * q;			// ��������� ������
	phi = (p-1)*(q-1);	// ������� ������

	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "N = p * q = " << n << endl;
	cout << "Eiler Function" << endl;
	cout << "Phi = (p - 1)(q - 1) = " << phi << endl << endl;

	e = 65537;			// �������� ���������� - �������� ����
	InvMod ( d, e, phi);	// �������� ����

	ZZ control;
	MulMod(control, d, e, phi);
	cout << "Control = " << control << endl;

	cout << "Public key {e,n} = {" << e << "," << n << "}" << endl << endl;
	cout << "Secret key {d,n} = {" << d << "," << n << "}" << endl << endl;

	for (long m = 1; m < 512; m++)
	{
		ZZ M;			// �������� �����
		RandomBits(M, m);
		cout << "     Open data: " << M << endl;
		ZZ C;
		PowerMod(C, M%n, e%n, n);		// ������������� ���������
		cout << "Encrypted data: " << C << endl;
		ZZ M1;
		PowerMod(M1, C%n, d%n, n);		// ���������� ��� ��������
		cout << "Decrypted data: " << M1 << endl;
		if ( M == M1 )
			cout << "OK" << endl;
		else
			cout << ":(" << endl;
		cout << endl;
	}
	
	return 0;
}