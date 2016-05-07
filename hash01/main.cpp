#include <fstream>        // הכÿ פאיכמגמדמ גגמהא/גûגמהא
#include <NTL/ZZ.h>
#include <iomanip>
#include "hash.h"

using namespace std;
using namespace NTL;

const int HSB = 32;


// Output of text in low-endian
void out_text_le ( unsigned char *TextToOut )
{
    cout << "Text to hash (low-endian)= \n" << "\""
         << TextToOut << "\"" << endl << endl;
}

// Output of text in big-endian
void out_text_be ( unsigned char *TextToOut, int len )
{
    int i;
    cout << "\nText to hash (big-endian) = " << endl;

    for (i = len-1; i >= 0; i--)
        cout << hex << setw(2) << setfill('0')
             << (int)TextToOut[i] << " ";
    cout << endl << endl;
}

// Output of hash-code in low-endian
void out_hash_le( byte hashed[HSB] )
{
    int i;
    cout << "Hash-code (low-endian) = \n";
    for( i=0; i<HSB; ++i )
        cout << hex << setfill('0') << setw(2)
             << (int)hashed[i] << " ";
    cout << endl << endl;
}

// Output of hash-code in big-endian
void out_hash_be( byte hashed[HSB] )
{
    int i;
    cout << "Hash-code (big-endian) = \n";
    for( i=HSB-1; i>=0; i-- )
        cout << hex << setfill('0') << setw(2)
             << (int)hashed[i] << " ";
    cout << endl << endl;
}


int main()
{

    ZZ a, b;
    unsigned char p[100];
    byte hashed[HSB];
    long l = 512;

    // RandomBits( a, l );

    // a = 1000;
    // cout << a << endl;

    ofstream outfile;
    outfile.open("hasharr.dat");
    if ( !outfile )
    {
        cerr << "\nCan't open hasharr.dat\n";
        exit(-1);
    }

    long num;
    // num = NumBytes(a);
    num = 36;
    // cout  << num << endl;

    a = 16842752;
    for (long j = 0; j<0x10000; j++)
    {
        BytesFromZZ(p, a, num);
        /*
        for (long i = num-1; i >= 0; i--)
        	cout << hex << setw(2) << setfill('0')
        		 << (int)p[i];
        cout << endl;
        */
        // out_text_be (p, num);

        hash((byte*)p, num, hashed);

        // out_hash_be( hashed );

        outfile.write(reinterpret_cast<char*>(hashed),HSB);
        a++;
    }

    outfile.close();
    return 0;
}
