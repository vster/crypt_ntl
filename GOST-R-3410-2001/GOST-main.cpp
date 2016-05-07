// ���� � 34.10-2001

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <ctime>
#include "convhex.h"
#include "QxyNTL.h"
#include "G3410-2001.h"


using namespace std;
using namespace NTL;

long L = 8;
ZZ p = conv<ZZ>(37);
ZZ a = conv<ZZ>(3);
ZZ b = conv<ZZ>(7);


int main()
{
    time_t begin, end;
    double seconds;
    ZZ_p::init(p);

    // ������������� ���
    // srand (time(NULL));
    time_t now = time(0);
    ZZ seed = conv<ZZ>(difftime(now,0));
    SetSeed( seed );

    // ��������� ��������� ����������
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

    // ���� ���������� ��
    testparams ( P, q );

    // ��������� ������
    ZZ d;				// �������� ����	1 < d < q-1
    Qxy Q;				// �������� ����
    genkeys ( d, Q, P, q );

    ZZ e;
    // e = 20;
    RandomBnd(e, q-1);		// ���
    if ( e == 0 )
        e = 1;
    cout << "\nHash e = " << e << endl << endl;

    // ��������� ���
    cout << "\nGeneration of sign\n";
    ZZ r, s;
    gensign ( r, s, e, d, P, q );

    // �������� ���
    cout << "\nVerification of sign\n";
    ZZ R;
    verifysign ( R, r, s, e, Q, P, q  );

    return 0;
}
