#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/rijndael.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
using namespace CryptoPP;

#define BLOCKSIZE 4

const string plain = "AES is the block cipher standard.";

const int key_size = 16;
const int iv0_size = 16;

const byte iv0[17] = "0000000000000000";
const byte iv9[17] = "9999999999999999";
const byte key[17] = "1234567890ABCDEF";

string aesCFB() {
    AlgorithmParameters params = MakeParameters
                                    (Name::FeedbackSize(), BLOCKSIZE)
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

string cfbDecrypt(string cipher) {
    AlgorithmParameters params = MakeParameters
                                (Name::FeedbackSize(), BLOCKSIZE)
                                (Name::IV(), ConstByteArrayParameter(iv0, iv0_size));

    CFB_Mode< AES >::Decryption dec;
    dec.SetKey( key, key_size, params );

    string recovered, decoded;

    StringSource ss0( cipher, true,
        new HexDecoder( 
        new StringSink( decoded ) ) // HexEncoder
    ); // StringSource

    StringSource ss1( decoded, true, 
        new StreamTransformationFilter( dec,
        new StringSink( recovered ) ) // StreamTransformationFilter
    ); // StringSource
    
   return recovered;
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

string cbcDecrypt(string cipher, const byte *iv, string padMod) {

    CBC_Mode< AES >::Decryption dec;
    dec.SetKeyWithIV( key, key_size, iv );

    string recovered, decoded;

    StringSource ss0( cipher, true,
        new HexDecoder( 
        new StringSink( decoded ) ) // HexEncoder
    ); // StringSource
    
    if (padMod == "ZeroPads") {
        StringSource ss1( decoded, true, 
            new StreamTransformationFilter( dec,
            new StringSink( recovered ),
            StreamTransformationFilter::ZEROS_PADDING) // StreamTransformationFilter
        ); // StringSource      
    } else {
        StringSource ss1( decoded, true, 
            new StreamTransformationFilter( dec,
            new StringSink( recovered ),
            StreamTransformationFilter::PKCS_PADDING) // StreamTransformationFilter
        ); // StringSource
    }
    return recovered;
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

string ecbDecrypt(string cipher) {
    ECB_Mode< AES >::Decryption dec;
    dec.SetKey( key, key_size );

    string recovered, decoded;

    StringSource ss0( cipher, true,
        new HexDecoder( 
        new StringSink( decoded ) ) // HexEncoder
    ); // StringSource

    StringSource ss1( decoded, true, 
        new StreamTransformationFilter( dec,
        new StringSink( recovered ) ) // StreamTransformationFilter
    ); // StringSource

    return recovered;
}

int main() { 
    ofstream fout;
    fout.open("out.txt");

    string now;

    now = aesCFB();
    cout << "   AES Mode: CFB\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    fout << now << '\n';

    now = cfbDecrypt(now);
    cout << "\nDecrypt: " << now << '\n';




    cout << "\n===========================================\n\n";



    now = aesCBC("ZeroPads", iv0);
    cout << "   AES Mode: CBC with ZeroPads\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    fout << now << '\n';

    now = cbcDecrypt(now, iv0, "ZeroPads");
    cout << "\nDecrypt: " << now << '\n';



    cout << "\n===========================================\n\n";



    now = aesCBC("PKCS", iv9);
    cout << "   AES Mode: CBC with PKCS_PAD\n";
    cout << "Initial Vec: " << iv9 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    fout << now << '\n';

    now = cbcDecrypt(now, iv9, "PKCS");
    cout << "\nDecrypt: " << now << '\n';



    cout << "\n===========================================\n\n";



    now = aesECB("PKCS");
    cout << "   AES Mode: ECB with PKCS\n";
    cout << "Initial Vec: " << iv0 << '\n';
    cout << "        Key: " << key << '\n';
    cout << " Plain Text: " << plain << '\n';
    cout << "Cipher Text: " << now << '\n';

    fout << now << '\n';

    now = ecbDecrypt(now);
    cout << "\nDecrypt: " << now << '\n';

    return 0;
}
/*
   AES Mode: CFB
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: AES is the block cipher standard.
Cipher Text: 3FFB4B1782A193C59FF7C467936A86F7E6074BC878DD30CB260F6003E5E5F03A87

Decrypt: AES is the block cipher standard.

===========================================

   AES Mode: CBC with ZeroPads
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: AES is the block cipher standard.
Cipher Text: F1274EE85F1E44C4E2EBE55B730DE05611CC891BD0CEBE2E7EA316988EC44625A5A568AFD2F274BD06270FBED9D1D9D8

Decrypt: AES is the block cipher standard.<0x00><0x00>....

===========================================

   AES Mode: CBC with PKCS_PAD
Initial Vec: 9999999999999999
        Key: 1234567890ABCDEF
 Plain Text: AES is the block cipher standard.
Cipher Text: F1CB1698C153657417532AE041E6B3DD94D1C56E0940A75ECA07A53DF526C7FBA04878BBF32A2B4ADACCF1A573946DA6

Decrypt: AES is the block cipher standard.

===========================================

   AES Mode: ECB with PKCS
Initial Vec: 0000000000000000
        Key: 1234567890ABCDEF
 Plain Text: AES is the block cipher standard.
Cipher Text: F40B6A7579C2736FF43E532E4AABC8CB74C757E27B5C063B88AC203E706258443C19BFF0C39A336F9460D4B388D5D85D

Decrypt: AES is the block cipher standard.
*/