// ECDSA

void genparams ( Qxy &P, ZZ &q, ZZ &bpn );
void genparam_q ( Qxy &P, ZZ &q );
void genparam_P ( Qxy &P, ZZ &q, ZZ &bpn );
void testparams ( Qxy &P, ZZ &q);
void genkeys ( ZZ &d, Qxy &Q, Qxy &P, ZZ &q ); 
void gensign (ZZ &r, ZZ &s, ZZ &H, ZZ &d, Qxy &P, ZZ &q);
void verifysign (ZZ &v, ZZ &r, ZZ &s, ZZ &H, Qxy &Q, Qxy &P, ZZ &q  );
