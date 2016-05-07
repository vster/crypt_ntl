void genparams( ZZ &p, ZZ &q, ZZ &g );
void genkeys ( ZZ &x, ZZ &y, ZZ &p, ZZ &q, ZZ &g );
void gensign (ZZ &r, ZZ &s, ZZ &x, ZZ &H, ZZ &p, ZZ &q, ZZ &g );
void verifysign ( ZZ &w, ZZ &r, ZZ &s, ZZ &y, ZZ &H, ZZ &p, ZZ &q, ZZ &g );
