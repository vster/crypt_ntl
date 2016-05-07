#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <ctime>
#include "convhex.h"

using namespace std;
using namespace NTL;

const long L = 8;
ZZ p = conv<ZZ>(307);
ZZ a = conv<ZZ>(3);
ZZ b = conv<ZZ>(7);

class Qxy
{
private:
    ZZ_p x, y;
public:
    Qxy ( )
    { };
    Qxy( ZZ_p xx, ZZ_p yy )
    {
        x = xx;
        y = yy;
    }
    void getQxy ( ZZ_p xx, ZZ_p yy )
    {
        x  = xx;
        y = yy;
    }
    void getQxy ( int xx, int yy )
    {
        x  = conv<ZZ_p>(xx);
        y = y = conv<ZZ_p>(yy);
    }
    void getQxy ( long xx, long yy )
    {
        x  = conv<ZZ_p>(xx);
        y = y = conv<ZZ_p>(yy);
    }
    void getQxy ( ZZ xx, ZZ yy )
    {
        x  = conv<ZZ_p>(xx);
        y = conv<ZZ_p>(yy);
    }
    ZZ_p putx( )
    {
        return x;
    }
    ZZ_p puty( )
    {
        return y;
    }
    void putQxy ( )
    {
        cout << "(" << x << "," << y << ")";
    }
    bool operator == ( Qxy q2 )
    {
        if ( (x == q2.x) & (y == q2.y) )
            return true;
        else
            return false;
    }

    Qxy operator + ( Qxy q2 )
    {
        Qxy tq, tq0;
        tq0.getQxy(conv<ZZ_p>(0),conv<ZZ_p>(0));
        ZZ_p dx, dy, lmb;
        tq.x = x;
        tq.y = y;
        if ( q2 == tq0 )
            return tq;
        if ( tq == tq0 )
            return q2;
        if ((x == q2.x) & ( y != q2.y))
        {
            return tq0;
        }
        if ((x == q2.x ) & (y == q2.y))
        {
            tq = q2.double_p();
            return tq;
        }
        dy = q2.y - y;
        dx = q2.x - x;
        lmb = dy / dx;

        tq.x = lmb * lmb - x - q2.x;
        tq.y = lmb * ( x - tq.x) - y;
        return tq;
    }
    Qxy double_p ( )
    {
        Qxy tq2;
        ZZ_p lmb;
        lmb = ( 3*x*x + conv<ZZ_p>(a)) / (2*y);
        tq2.x = lmb * lmb - 2 * x;
        tq2.y = lmb * ( x - tq2.x ) - y;
        return tq2;
    }

    Qxy operator * ( ZZ k )
    {
        Qxy tq, tq2, tq0;
        tq0.getQxy(conv<ZZ_p>(0),conv<ZZ_p>(0));
        tq.x = x;
        tq.y = y;

        Qxy sum;
        Qxy dtq;
        long len = NumBits(k);

        dtq = tq;
        sum = tq0;
        for ( long i = 0; i < len; i++ )
        {
            if (bit(k,i))
                sum = sum + dtq;
            dtq = dtq.double_p();
        }
        return sum;
    }
};

ZZ muln (ZZ &a, ZZ &k )
{
    ZZ sum;
    ZZ da;
    long len = NumBits(k);

    da = a;
    sum = 0;
    for ( long i = 0; i < len; i++ )
    {
        if (bit(k,i))
            sum += da;
        da = 2 * da;
        cout << i << " " << da << " " << sum << endl;
    }
    return sum;
}

// Генерация начальных параметров
void genparams ( Qxy &P, ZZ &q, ZZ &bpn )
{
    ZZ i;
    ZZ x, y;
    ZZ f1, f2;

    for ( x = 0, i = 0; x < p; x++)
        for ( y = 0; y < p; y++)
        {
            f1 = PowerMod(y, 2, p);
            f2 = (PowerMod(x, 3, p) + a * x + b)%p;
            if ( f1 == f2 )
            {
                if ( i == bpn )
                    P.getQxy(x,y);
                i++;
            }
        }
    q = i+1;
    cout << "Parameters of elliptic curve" << endl;
    cout << "\np = " << p;
    cout << "\na = " << a;
    cout << "\nb = " << b;
    cout << "\nbpn = " << bpn << endl;
    cout << "\nq = " << q << endl;
    cout << "\nP = ";
    P.putQxy();
    cout << endl;
}

void genparam_q ( Qxy &P, ZZ &q )
{
    ZZ i;
    ZZ x, y;
    ZZ f1, f2;

    for ( x = 0, i = 0; x < p; x++)
        for ( y = 0; y < p; y++)
        {
            f1 = PowerMod(y, 2, p);
            f2 = (PowerMod(x, 3, p) + a * x + b)%p;
            if ( f1 == f2 ) i++;
        }
    q = i+1;
    cout << "\np = " << p;
    cout << "\na = " << a;
    cout << "\nb = " << b;
    cout << "\nq = " << q << endl;
}

void genparam_P ( Qxy &P, ZZ &q, ZZ &bpn )
{
    ZZ i;
    ZZ x, y;
    ZZ f1, f2;

    for ( x = 0, i = 0; x < p; x++)
        for ( y = 0; y < p; y++)
        {
            f1 = PowerMod(y, 2, p);
            f2 = (PowerMod(x, 3, p) + a * x + b)%p;
            if ( f1 == f2)
            {
                if (i == bpn)
                {
                    P.getQxy(x,y);
                    goto out;
                }
                i++;
            }
        }
out:
    {}

}
// Тест параметров ЭК
void testparams ( Qxy &P, ZZ &q)
{
    // Тест: некая точка * порядок кривой = нулевая точка
    Qxy TQ = P*q;
    cout << "\nTest Q = ";
    TQ.putQxy();

    cout << "\nMust be (0,0)\n" << endl;
}
// Генерация ключей
void genkeys ( ZZ &d, Qxy &Q, Qxy &P, ZZ &q )
{
    RandomBnd(d, q-1);				// Закрытый ключ	1 < d < q-1
    // d = 15;
    Q = P*d;			// Открытый ключ
    cout << "\nPrivate key d = " << d << endl;
    cout << "Public key Q = ";
    Q.putQxy();
    cout << endl;
}

// Генерация ЭЦП
void gensign (ZZ &r, ZZ &s, ZZ &H, ZZ &d, Qxy &P, ZZ &q)
{
    ZZ k;
    Qxy Q;

    // srand (time(NULL));
    while ( true )
    {
        RandomBnd(k, q-1);
        if ( GCD(k,q) > 1 )
            continue;
        // k = 5;
        Q = P*k;
        r = (conv<ZZ>(Q.putx()))%q;
        if ( r == 0)
            continue;

        ZZ k1;
        if (InvModStatus( k1, k, q ))
            continue;
        k1 = InvMod(k,q);
        s = (k1*((H+r*d)%q))%q;
        if ( s > 0)
            break;
    }

    cout << "k = " << k << endl
         << "(r,s) = ("
         << r << "," << s << ")" << endl;
}

// Проверка ЭЦП
void verifysign (ZZ &v, ZZ &r, ZZ &s, ZZ &H, Qxy &Q, Qxy &P, ZZ &q  )
{
    ZZ u1, u2;
    Qxy Q2;
    ZZ s1;
    if (InvModStatus( s1, s, q ))
    {
        cout << "\nError in sign\n";
        goto end;
    }
    s1 = InvMod(s,q);
    u1 = (s1*H)%q;
    u2 = (s1*r)%q;
    Q2 = P*u1 + Q*u2;
    v = (conv<ZZ>(Q2.putx()))%q;

    cout << "u1 = " << u1 << endl
         << "u2 = " << u2 << endl
         << "Q2 = ";
    Q2.putQxy();
    cout << endl;
end:
    if ( r == v )
        cout << "\nr = v\nSign is OK";
    else
        cout << "Sign is FAILD";
    cout << endl;

}

int main()
{
    time_t begin, end;
    double seconds;
    ZZ_p::init(p);

    // Инициализация ДСЧ
    // srand (time(NULL));
    time_t now = time(0);
    ZZ seed = conv<ZZ>(difftime(now,0));
    SetSeed( seed );

    // ZZ pt;
    // long err = 80;
    // GenPrime(pt, L, err);
    // cout << pt << endl;

    // Генерация начальных параметров
    Qxy P, P1, P2, P3, P4;
    ZZ q;
    ZZ bpn;

    cout << "Generation of parameters...\n";
    begin = time(NULL);
    genparam_q ( P, q );
    end = time(NULL);

    seconds = difftime(end, begin);
    cout << "\nGeneration = " << seconds << " sec" << endl;

    // bpn	= 1;
    RandomBnd(bpn, q-1);
    genparam_P ( P, q, bpn );
    cout << "\nbpn = " << bpn << endl;
    cout << "\nP = ";
    P.putQxy();
    cout << endl;

    // Тест параметров ЭК
    testparams ( P, q );

    // Генерация ключей
    ZZ d;				// Закрытый ключ	1 < d < q-1
    Qxy Q;				// Открытый ключ
    genkeys ( d, Q, P, q );

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
