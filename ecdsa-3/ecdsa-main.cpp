#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <ctime>
#include "zzhex.h"
#include "QxyNTL.h"
#include "ecdsa.h"

using namespace std;
using namespace NTL;

const long MAXP = 200;

ZZ p, a, b, q;
long L;

struct ECPar
{
	char pname[MAXP];
	long L_dec;
	char p_dec[MAXP];	// p
	char n_dec[MAXP];	// q
	char a_dec[MAXP]; 
	char c_hex[MAXP]; 
	char b_hex[MAXP]; 
	char xg_hex[MAXP];
	char yg_hex[MAXP];
};

ECPar	ecp[5] = {
	// FIPS 186-3, Curve P-192
	{
	"Curve P-192",
	192,
	"6277101735386680763835789423207666416083908700390324961279",
	"6277101735386680763835789423176059013767194773182842284081",
	"-3",
	"3099d2bbbfcb2538542dcd5fb078b6ef5f3d6fe2c745de65",
	"64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1",
	"188da80eb03090f67cbf20eb43a18800f4ff0afd82ff1012",
	"07192b95ffc8da78631011ed6b24cdd573f977a11e794811"
	},
	// FIPS 186-3, Curve P-224
	{
	"Curve P-224",
	224,
	"26959946667150639794667015087019630673557916260026308143510066298881",
	"26959946667150639794667015087019625940457807714424391721682722368061",
	"-3",
	"5b056c7e11dd68f40469ee7f3c7a7d74f7d121116506d031218291fb",
	"b4050a850c04b3abf54132565044b0b7d7bfd8ba270b39432355ffb4",
	"b70e0cbd6bb4bf7f321390b94a03c1d356c21122343280d6115c1d21",
	"bd376388b5f723fb4c22dfe6cd4375a05a07476444d5819985007e34"
	},
	// FIPS 186-3, Curve P-256
	{
	"Curve P-256",	
	256,
	"115792089210356248762697446949407573530086143415290314195533631308867097853951",
	"115792089210356248762697446949407573529996955224135760342422259061068512044369",
	"-3",
	"7efba1662985be9403cb055c75d4f7e0ce8d84a9c5114abcaf3177680104fa0d",
	"5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b",
	"6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",
	"4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5"
	},
	// FIPS 186-3, Curve P-384
	{
	"Curve P-384",	
	384,
	"39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112319",
	"39402006196394479212279040100143613805079739270465446667946905279627659399113263569398956308152294913554433653942643",
	"-3",
	"79d1e655f868f02fff48dcdee14151ddb80643c1406d0ca10dfe6fc52009540a495e8042ea5f744f6e184667cc722483",
	"b3312fa7e23ee7e4988e056be3f82d19181d9c6efe8141120314088f5013875ac656398d8a2ed19d2a85c8edd3ec2aef",
	"aa87ca22be8b05378eb1c71ef320ad746e1d3b628ba79b9859f741e082542a385502f25dbf55296c3a545e3872760ab7",
	"3617de4a96262c6f5d9e98bf9292dc29f8f41dbd289a147ce9da3113b5f0b8c00a60b1ce1d7e819d7a431d7c90ea0e5f"
	},
	// FIPS 186-3, Curve P-521
	{
	"Curve P-521",	
	521,
	"6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151",
	"6864797660130609714981900799081393217269435300143305409394463459185543183397655394245057746333217197532963996371363321113864768612440380340372808892707005449",
	"-3",
	"0b48bfa5f420a34949539d2bdfc264eeeeb077688e44fbf0ad8f6d0edb37bd6b533281000518e19f1b9ffbe0fe9ed8a3c2200b8f875e523868c70c1e5bf55bad637",
	"051953eb9618e1c9a1f929a21a0b68540eea2da725b99b315f3b8b489918ef109e156193951ec7e937b1652c0bd3bb1bf073573df883d2c34f1ef451fd46b503f00",
	"c6858e06b70404e9cd9e3ecb662395b4429c648139053fb521f828af606b4d3dbaa14b5e77efe75928fe1dc127a2ffa8de3348b3c1856a429bf97e7e31c2e5bd66",
	"11839296a789a3bc0045c8a5fb42c7d1bd998f54449579b446817afbd17273e662c97ee72995ef42640c550b9013fad0761353c7086a272c24088be94769fd16650"
	}
};

//======================================
void line()
{
	cout << endl;	
	for (int i = 0; i < 79; i++) cout << "=";
	cout << endl;
}

int main()
{
	// time_t begin, end;
	// double seconds;
	// ZZ_p::init(p);

	// Инициализация ДСЧ
	time_t now = time(0);
	ZZ seed = conv<ZZ>(difftime(now,0));
	SetSeed( seed ); 

	// Параметры домена

	//======================================
	line();

	cout << "\nDomain parameters:\n";
	long idp = 4;	//	id of EC params
	
	cout << ecp[idp].pname << endl;

	L = ecp[idp].L_dec;
	
	p = conv<ZZ> (ecp[idp].p_dec);
	cout << "\np (dec) = \n" << p << endl;
	cout << "\np (hex) = \n"; 
	ShowZZInHex(p);
	//show_dec_in_hex (p, L);	
	cout << endl;

	a = conv<ZZ> (ecp[idp].a_dec);
	cout << "\na (dec) = \n" << a << endl;
	cout << "\na (hex) = \n"; 
	ShowZZInHex(a);	
	// show_dec_in_hex (a, L);	
	cout << endl;

	// b = conv<ZZ> (b_dec);
	ZZFromHex(b, ecp[idp].b_hex);
	// get_dec_from_hex ( b, ecp[idp].b_hex, L );
	cout << "\nb (dec) = \n" << b << endl;
	cout << "\nb (hex) = \n"; 
	ShowZZInHex(b);	
	// show_dec_in_hex (b, L);	
	cout << endl;

	q = conv<ZZ> (ecp[idp].n_dec);
	// get_dec_from_hex (ZZ &q, n_hex, L )
	cout << "\nq (dec) = \n" << q << endl;		
	cout << "\nq (hex) = \n"; 
	ShowZZInHex(q);	
	// show_dec_in_hex (q, L);	
	cout << endl;

	
	ZZ_p::init(p);

	Qxy P;
	ZZ xp;
	ZZ yp;
	// xp = conv<ZZ>(xp_dec);
	// yp = conv<ZZ>(yp_dec);
	ZZFromHex(xp, ecp[idp].xg_hex);
	ZZFromHex(yp, ecp[idp].yg_hex);
	// get_dec_from_hex ( xp, ecp[idp].xg_hex, L );
	// get_dec_from_hex ( yp, ecp[idp].yg_hex, L );


	P.getQxy(xp, yp);

	cout << "\nBase point P:\n";
	P.putQxy();
	cout << endl;

	//======================================
	line();

	// Тест параметров ЭК
	testparams ( P, q );

	//======================================
	line();
	
	// Генерация ключей
	ZZ d;				// Закрытый ключ	1 < d < q-1
	Qxy Q;				// Открытый ключ
	genkeys ( d, Q, P, q );

	//======================================
	line();
	
	// Генерим хэш < q-1
	ZZ H;
	RandomBnd(H, q-1);		// Хэш
	cout << "\nHash H = \n" << H << endl << endl;	

	// Генерация ЭЦП
	cout << "\nGeneration of sign\n";
	ZZ r, s;
	gensign ( r, s, H, d, P, q );

	//======================================
	line();
	
	// Проверка ЭЦП
	cout << "\nVerification of sign\n";	
	ZZ v;
	verifysign ( v, r, s, H, Q, P, q  );

	//======================================
	line();

	return 0;
}