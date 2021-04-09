#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/rijndael.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
using namespace CryptoPP;

const string plain = "Hello World!";

const int key_size = 16;
const int iv0_size = 16;

const byte iv0[17] = "0000000000000000";
const byte iv9[17] = "9999999999999999";
const byte key[17] = "1234567890ABCDEF";

string aesCFB() {
    AlgorithmParameters params = MakeParameters
                                    (Name::FeedbackSize(), 4)
                                    (Name::IV(), ConstByteArrayParameter(iv0, iv0_size));

    CFB_Mode< AES >::Encryption enc;
    enc.SetKey(key, key_size, params);

    string cipher, encoded;

    StringSource ss1( plain, true,
        new StreamTransformationFilter( enc, 
        new StringSink( cipher )) // StreamTransformationFilter
    ); // StringSource

    StringSource ss2( cipher, true,
        new HexEncoder( 
        new StringSink( encoded ) ) // HexEncoder
    ); // StringSource

    return encoded;
}

string aesCBC(string padMod, const byte *iv) {
    CBC_Mode< AES >::Encryption enc;
    enc.SetKeyWithIV(key, key_size, iv);

    string cipher, encoded;

    if (padMod == "ZeroPads") {
        StringSource ss1( plain, true, 
                new StreamTransformationFilter( enc,
                new StringSink( cipher ),
                StreamTransformationFilter::ZEROS_PADDING) // StreamTransformationFilter      
        ); // StringSource
    } else {
        StringSource ss1( plain, true, 
                new StreamTransformationFilter( enc,
                new StringSink( cipher ),
                StreamTransformationFilter::PKCS_PADDING) // StreamTransformationFilter      
        ); // StringSource  
    }

    StringSource ss2( cipher, true,
        new HexEncoder( 
        new StringSink( encoded )) // HexEncoder
    ); // StringSource

    return encoded;
}

string aesECB(string padMod) {
    ECB_Mode< AES >::Encryption enc;
    enc.SetKey(key, key_size);

    string cipher, encoded;

    StringSource ss1( plain, true, 
            new StreamTransformationFilter( enc,
            new StringSink( cipher ),
            StreamTransformationFilter::PKCS_PADDING) // StreamTransformationFilter      
    ); // StringSource

    StringSource ss2( cipher, true,
        new HexEncoder( 
        new StringSink( encoded )) // HexEncoder
    ); // StringSource

    return encoded;
}

int main() { 
    string now;

    now = aesCFB();
    cout << "   AES Mode: CFB\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    cout << "\n===========================================\n\n";

    now = aesCBC("ZeroPads", iv0);
    cout << "   AES Mode: CBC with ZeroPads\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    cout << "\n===========================================\n\n";

    now = aesCBC("PKCS", iv0);
    cout << "   AES Mode: CBC with PKCS_PAD\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    cout << "\n===========================================\n\n";

    now = aesECB("PKCS");
    cout << "   AES Mode: ECB with PKCS\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';
    return 0;
}
/*
   AES Mode: CFB
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: Hello World!
Cipher Text: 36DB745B3B6DA69ABF5FEB23

===========================================

   AES Mode: CBC with ZeroPads
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: Hello World!
Cipher Text: 4C855D6317608F8DD39461E5BCC940B8

===========================================

   AES Mode: CBC with PKCS_PAD
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: Hello World!
Cipher Text: D6F61A228CD21DDF80D8C344733D9419

===========================================

   AES Mode: ECB with PKCS
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: Hello World!
Cipher Text: D523326C27EE0F2165C7696B36F2688E
*/