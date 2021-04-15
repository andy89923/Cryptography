#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/rijndael.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
using namespace CryptoPP;

#define BLOCKSIZE 4
#define BLOCKSIZE2 2

const string plain = "AES is the block cipher standard.";

const int key_size = 16;
const int iv_size = 16;

const byte iv0[17] = "0000000000000000";
const byte iv9[17] = "9999999999999999";
const byte key[17] = "AES Key:81243716";

string cfbDecrypt4(string cipher, const byte* iv) {
	AlgorithmParameters params = MakeParameters
                            	(Name::FeedbackSize(), BLOCKSIZE)
                                (Name::IV(), ConstByteArrayParameter(iv, iv_size));

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

string cfbDecrypt2(string cipher, const byte* iv) {
	AlgorithmParameters params = MakeParameters
                            	(Name::FeedbackSize(), BLOCKSIZE2)
                                (Name::IV(), ConstByteArrayParameter(iv, iv_size));

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

string ecbDecrypt(string cipher, string padMod) {
	ECB_Mode< AES >::Decryption dec;
    dec.SetKey( key, key_size );

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

int main() { 
	string cipher1 = "3EB014EB027A97DD37D62E76E9AA93AA5FD20218FD2F5A2E3A6AB30F82669572";
	string cipher2 = "B2BA8D9BEF06D9DE06AF5536296D361072095A04E4D4EEFAB3C9F9D30028278A";
	string cipher3 = "F5A33AF09EBA924860797F44EAF6ADA18C72794AD2060A82231276C04D90D316";

	string tmp, now;
	string now_cip = cipher3;

	now = now_cip;
	cout << "   AES Mode: CFB 4-Byte Block\n";
	cout << "Initial Vec: " << iv0 << '\n';
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = cfbDecrypt4(now, iv0);
	cout << "\nDecrypt: " << tmp << '\n';

	cout << "\n===========================================\n\n";

	now = now_cip;
	cout << "   AES Mode: CFB 4-Byte Block\n";
	cout << "Initial Vec: " << iv9 << '\n';
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = cfbDecrypt4(now, iv9);
	cout << "\nDecrypt: " << tmp << '\n';

	cout << "\n===========================================\n\n";

	now = now_cip;
	cout << "   AES Mode: CFB 2-Byte Block\n";
	cout << "Initial Vec: " << iv0 << '\n';
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = cfbDecrypt2(now, iv0);
	cout << "\nDecrypt: " << tmp << '\n';

	cout << "\n===========================================\n\n";

	now = now_cip;
	cout << "   AES Mode: CFB 2-Byte Block\n";
	cout << "Initial Vec: " << iv9 << '\n';
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = cfbDecrypt2(now, iv9);
	cout << "\nDecrypt: " << tmp << '\n';





	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CBC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

	cout << "\n===========================================\n\n";

	now = now_cip;
	cout << "   AES Mode: CBC with ZeroPads\n";
	cout << "Initial Vec: " << iv0 << '\n';
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = cbcDecrypt(now, iv0, "ZeroPads");
	cout << "\nDecrypt: " << tmp << '\n';

	cout << "\n===========================================\n\n";

	now = now_cip;
	cout << "   AES Mode: CBC with ZeroPads\n";
	cout << "Initial Vec: " << iv9 << '\n';
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = cbcDecrypt(now, iv9, "ZeroPads");
	cout << "\nDecrypt: " << tmp << '\n';

	cout << "\n===========================================\n\n";

	// now = now_cip;
	// cout << "   AES Mode: CBC with PKCS\n";
	// cout << "Initial Vec: " << iv0 << '\n';
	// cout << "        Key: " << key << '\n';
	// cout << "Cipher Text: " << now << '\n';

	// tmp = cbcDecrypt(now, iv0, "PKCS");
	// cout << "\nDecrypt: " << tmp << '\n';

	// cout << "\n===========================================\n\n";

	// now = now_cip;
	// cout << "   AES Mode: CBC with PKCS\n";
	// cout << "Initial Vec: " << iv9 << '\n';
	// cout << "        Key: " << key << '\n';
	// cout << "Cipher Text: " << now << '\n';

	// tmp = cbcDecrypt(now, iv9, "PKCS");
	// cout << "\nDecrypt: " << tmp << '\n';

	// cout << "\n===========================================\n\n";








	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ECB ~~~~~~~~~~~~~~~~~~~~~~~ //

	// now = now_cip;
	// cout << "   AES Mode: ECB with PKCS\n";
	// cout << "        Key: " << key << '\n';
	// cout << "Cipher Text: " << now << '\n';

	// tmp = ecbDecrypt(now, "PKCS");
	// cout << "\nDecrypt: " << tmp << '\n';

	// cout << "\n===========================================\n\n";

	now = now_cip;
	cout << "   AES Mode: ECB with ZeroPads\n";
	cout << "        Key: " << key << '\n';
	cout << "Cipher Text: " << now << '\n';

	tmp = ecbDecrypt(now, "ZeroPads");
	cout << "\nDecrypt: " << tmp << '\n';

    return 0;
}

/* Result
Case 1:
   AES Mode: ECB with ZeroPads
        Key: AES Key:81243716
Cipher Text: 3EB014EB027A97DD37D62E76E9AA93AA5FD20218FD2F5A2E3A6AB30F82669572

Decrypt: RSA is a public-key system.


Case 2:
   AES Mode: CBC with ZeroPads
Initial Vec: 0000000000000000
        Key: AES Key:81243716
Cipher Text: B2BA8D9BEF06D9DE06AF5536296D361072095A04E4D4EEFAB3C9F9D30028278A

Decrypt: Pseudorandom numbers


Case 3:
   AES Mode: CFB 2-Byte Block
Initial Vec: 0000000000000000
        Key: AES Key:81243716
Cipher Text: F5A33AF09EBA924860797F44EAF6ADA18C72794AD2060A82231276C04D90D316

Decrypt: The Advanced Encryption Standard
*/