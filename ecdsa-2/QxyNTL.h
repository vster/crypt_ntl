extern long L;

class Qxy
{
private:
	ZZ_p x, y;
public:
	Qxy ( )
	{ };
	Qxy( ZZ_p xx, ZZ_p yy )
	{ x = xx; y = yy; }
	void getQxy ( ZZ_p xx, ZZ_p yy )
	{ x  = xx; y = yy; }
	void getQxy ( int xx, int yy )
	{ x  = conv<ZZ_p>(xx); y = conv<ZZ_p>(yy); }
	void getQxy ( long xx, long yy )
	{ x  = conv<ZZ_p>(xx); y = conv<ZZ_p>(yy); }
	void getQxy ( ZZ xx, ZZ yy )
	{ x  = conv<ZZ_p>(xx); y = conv<ZZ_p>(yy); }
	ZZ_p putx( )
		{ return x; }
	ZZ_p puty( )
		{ return y; }
	void putQxy ( )
	{
		cout << "\nx (dec) = \n" << x << endl;
		cout << "\nx (hex) = \n"; show_dec_in_hex (conv<ZZ>(x), L);
		cout << "\ny (dec) = \n" << y; cout << endl;
		cout << "\ny (hex) = \n"; show_dec_in_hex (conv<ZZ>(y), L);
		cout << endl;
		// cout << "(" << x << "," << y << ")";
	}
	bool operator == ( Qxy q2 );
	Qxy operator + ( Qxy q2 );
	Qxy double_p ( );
	Qxy operator * ( ZZ k );
};
