#include <iostream>
#include <iomanip>
#include "util.h"
#include <NTL/GF2E.h>
#include <NTL/GF2EX.h>
#include <NTL/vector.h>

using namespace std;
using namespace NTL;

const long MAXB = 100;
const u32bit BS = 16;
const u32bit KL = 32;

byte Pi[256] = {
252,238,221, 17,207,110, 49, 22,251,196,250,218, 35,197,  4, 77,
233,119,240,219,147, 46,153,186, 23, 54,241,187, 20,205, 95,193,
249, 24,101, 90,226, 92,239, 33,129, 28, 60, 66,139,  1,142, 79,
  5,132,  2,174,227,106,143,160,  6, 11,237,152,127,212,211, 31,
235, 52, 44, 81,234,200, 72,171,242, 42,104,162,253, 58,206,204,
181,112, 14, 86,  8, 12,118, 18,191,114, 19, 71,156,183, 93,135,
 21,161,150, 41, 16,123,154,199,243,145,120,111,157,158,178,177,
 50,117, 25, 61,255, 53,138,126,109, 84,198,128,195,189, 13, 87,
223,245, 36,169, 62,168, 67,201,215,121,214,246,124, 34,185,  3,
224, 15,236,222,122,148,176,188,220,232, 40, 80, 78, 51, 10, 74,
167,151, 96,115, 30,  0, 98, 68, 26,184, 56,130,100,159, 38, 65,
173, 69, 70,146, 39, 94, 85, 47,140,163,165,125,105,213,149, 59,
  7, 88,179, 64,134,172, 29,247, 48, 55,107,228,136,217,231,137,
225, 27,131, 73, 76, 63,248,254,141, 83,170,144,202,216,133, 97,
 32,113,103,164, 45, 43,  9, 91,203,155, 37,208,190,229,108, 82,
 89,166,116,210,230,244,180,192,209,102,175,194, 57, 75, 99,182};

byte InvPi[256];

byte L_Tab[16] = {1,148,32,133,16,194,192,1,251,1,192,194,16,133,32,148};

byte RoundKey[10][16];

/*
void GF2XFromZZ( GF2X &x, ZZ &n )
{
	byte buf[MAXB];

	BytesFromZZ( buf, n, MAXB );
	GF2XFromBytes(x, buf, MAXB);
}
*/
GF2X GF2XFromZZ( const ZZ &n )
{
	GF2X x;
	byte buf[MAXB];

	BytesFromZZ( buf, n, MAXB );
	GF2XFromBytes(x, buf, MAXB);
	return x;
}

void ZZFromGF2X ( ZZ &n, GF2X &x )
{
	byte buf[MAXB];

	BytesFromGF2X( buf, x, MAXB );
	ZZFromBytes( n, buf, MAXB );
}

ZZ ZZFromGF2X ( GF2X &x )
{
	ZZ n;
	byte buf[MAXB];

	BytesFromGF2X( buf, x, MAXB );
	ZZFromBytes( n, buf, MAXB );
	return n;
}

void OutputGF2EX( GF2EX &x )
{
	long d = deg ( x );
	for ( long i = 0; i < d+1; i++ )
	{
		GF2X tx = conv<GF2X>( coeff( x, i ) );
		cout << hex << setw(2) << setfill('0')
			<< conv <long> ( ZZFromGF2X( tx ) ) << " ";
	}
}

void OutputVecGF2E( vec_GF2E &x )
{
	long d = x.length();
	for ( long i = 0; i < d; i++ )
	{
		GF2X tx = conv<GF2X>( x[i] );
		cout << hex << setw(2) << setfill('0')
			<< conv <long> ( ZZFromGF2X( tx ) ) << " ";
	}
}

void OutputGF2E( GF2E &x )
{
	GF2X tx = conv<GF2X>( x );
	cout << hex << setw(2) << setfill('0')
			<< conv <long> ( ZZFromGF2X( tx ) );
}

void OutputBlock ( byte Block[BS] )
{
	for ( int i = 0; i < BS; i++ )
		cout << hex << setw(2) << setfill('0')
			<< conv <long> ( Block[i] ) << " ";
}

void Init(  )
{
	for ( long i = 0; i < 256; i++ )
		InvPi[ Pi[i] ] = i;
}

// X-�������������� (���������� �����)
void X_conv( byte Block[BS], byte key[16] )
{
	xor_buf( Block, key, BS );
}

// S-�������������� (����������)
void S_conv ( byte Block[BS] )
{
	for ( long i = 0; i < BS; i++ )
		Block[i] = Pi[ Block[i] ];
}

// �������� S-�������������� (����������)
void InvS_conv ( byte Block[BS] )
{
	for ( long i = 0; i < BS; i++ )
		Block[i] = InvPi[ Block[i] ];
}

// L-�������������� (��������)
void L_conv ( byte Block[BS] )
{
	ZZ p;
	// ������������� ��������� ���� ��������� GF2
	p = 0x1c3;
	GF2X Px;
	Px = GF2XFromZZ ( p );
	GF2E::init(Px);

	vec_GF2E Lv;
	Lv.SetLength(16);
	for ( long i = 0; i < BS; i++ )
		Lv[i] = conv<GF2E>( GF2XFromZZ( conv<ZZ>( L_Tab[i] )));

	// OutputVecGF2E ( Lv );
	// cout << endl;

	vec_GF2E Av;
	Av.SetLength(16);
	for ( long i = 0; i < BS; i++ )
		Av[i] = conv<GF2E>( GF2XFromZZ( conv<ZZ>( Block[i] )));

	// OutputVecGF2E ( Av );
	// cout << endl;

	for ( long j = 0; j < BS; j++ )
	{
		GF2E Se;
		// Se = conv<GF2E>( GF2XFromZZ( conv<ZZ>( 0 ) ) );
		clear( Se );
		// OutputGF2E ( Se );
		for ( long i = 0; i < BS; i++ )
			Se += Lv[i] * Av[i];

		for ( long i = 1; i < BS; i++ )
			Av[i-1] = Av[i];
		Av[BS-1] = Se;
		OutputVecGF2E ( Av );
		cout << endl;
	}

	for ( long i = 0; i < BS; i++ )
	{
		GF2X tx = conv<GF2X>( Av[i] );
		Block[i] = conv<long>( ZZFromGF2X ( tx ));
	}
}

// �������� L-�������������� (��������)
void InvL_conv ( byte Block[BS] )
{
	ZZ p;
	// ������������� ��������� ���� ��������� GF2
	p = 0x1c3;
	GF2X Px;
	Px = GF2XFromZZ ( p );
	GF2E::init(Px);

	vec_GF2E Lv;
	Lv.SetLength(16);
	for ( long i = 0; i < BS; i++ )
		Lv[i] = conv<GF2E>( GF2XFromZZ( conv<ZZ>( L_Tab[i] )));

	// OutputVecGF2E ( Lv );
	// cout << endl;

	vec_GF2E Av;
	Av.SetLength(16);
	for ( long i = 0; i < BS; i++ )
		Av[i] = conv<GF2E>( GF2XFromZZ( conv<ZZ>( Block[i] )));

	// OutputVecGF2E ( Av );
	// cout << endl;
	for ( long j = 0; j < BS; j++ )
	{
		GF2E Se;
		// Se = conv<GF2E>( GF2XFromZZ( conv<ZZ>( 0 ) ) );
		clear( Se );
		// OutputGF2E ( Se );
		for ( long i = 0; i < BS-1; i++ )
			Se += Lv[i+1] * Av[i];

		GF2E Te;
		Te = Av[BS-1] - Se;

		for ( long i = BS-1; i > 0; i-- )
			Av[i] = Av[i-1];
		Av[0] = Te;
		// OutputVecGF2E ( Av );
		//	cout << endl;
	}

	for ( long i = 0; i < BS; i++ )
	{
		GF2X tx = conv<GF2X>( Av[i] );
		Block[i] = conv<long>( ZZFromGF2X ( tx ));
	}
}

void Round ( byte Block[BS], byte Key[BS] )
{
	// X-�������������� (���������� �����)
	X_conv ( Block, Key );

	// OutputBlock ( Block );
	// cout << endl;

	// S-�������������� (����������)
	S_conv ( Block );

	// OutputBlock ( Block );
	// cout << endl;

	// L-�������������� (��������)
	L_conv ( Block );

	OutputBlock ( Block );
	cout << endl;
}

void InvRound ( byte Block[BS], byte Key[BS] )
{
	// X-�������������� (���������� �����)
	X_conv ( Block, Key );

	// OutputBlock ( Block );
	// cout << endl;

	// �������� L-�������������� (��������)
	InvL_conv ( Block );

	// OutputBlock ( Block );
	// cout << endl;

	// �������� S-�������������� (����������)
	InvS_conv ( Block );

	OutputBlock ( Block );
	cout << endl;
}

void GenKeys ( byte Key[KL] )
{
	for ( long i = 0; i < 10; i++ )
		for ( long j = 0; j < 16; j++ )
			RoundKey[i][j] = rand();
}

void EncryptKuz( byte OpenData[BS], byte EncData[BS] )
{
	byte Block[BS];

	for ( long i = 0; i < BS; i++ )
		Block[i] = OpenData[i];

	cout << "\nEncryption...\n";
	for ( long round = 0; round < 9; round++ )
	{
		cout << "\nRound " << round+1 << endl;
		// cout << "\nRound key\n";
		// OutputBlock( RoundKey[round] );
		// cout << endl;
		Round( Block, RoundKey[round] );
	}
	// cout << endl;
	// OutputBlock( RoundKey[9] );
	// cout << endl;
	X_conv ( Block, RoundKey[9] );

	for ( long i = 0; i < BS; i++ )
		 EncData[i] = Block[i];
}

void DecryptKuz( byte EncData[BS], byte DecData[BS] )
{
	byte Block[BS];

	for ( long i = 0; i < BS; i++ )
		Block[i] = EncData[i];

	cout << "\nDecryption...\n";
	for ( long round = 0; round < 9; round++ )
	{
		cout << "\nRound " << round+1 << endl;
		// cout << "\nRound key\n";
		// OutputBlock( RoundKey[9-round] );
		// cout << endl;
		InvRound( Block, RoundKey[9-round] );
	}
	// cout << endl;
	// OutputBlock( RoundKey[0] );
	// cout << endl;
	X_conv ( Block, RoundKey[0] );

	for ( long i = 0; i < BS; i++ )
		 DecData[i] = Block[i];
}

int main()
{
	byte OpenData[BS] =
		{0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,
		0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33};

	// for ( int i = 0; i < BS; i++ )
	//	OpenData[i] = 1;

	byte EncData[BS];
	byte DecData[BS];
	byte Block[BS];

	byte Key[KL];

	// ������������ ����
	GenKeys( Key );
	Init();

	cout << "\nOpen data\n";
	OutputBlock ( OpenData );
	cout << endl;

	// ������������
	EncryptKuz ( OpenData, EncData );

	cout << "\nEncrypted data\n";
	OutputBlock ( EncData );
	cout << endl;

	// �������������
	DecryptKuz ( EncData, DecData );

	cout << "\nDecrypted data\n";
	OutputBlock ( DecData );
	cout << endl;

}
