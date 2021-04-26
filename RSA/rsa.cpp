#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/rijndael.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/rsa.h"
#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
using namespace CryptoPP;

string encrypt(Integer n, Integer e, string plainText) {
	Integer m((const byte *)plainText.data(), plainText.size());

	RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);
		
	Integer c = pubKey.ApplyFunction(m);
	string cipher;

	stringstream ss;
	ss << hex << c;
	ss >> cipher;

	cipher = cipher.substr(0, cipher.length() - 1);

	return cipher;
}

string decrypt(Integer n, Integer e, Integer d, Integer c) {
	AutoSeededRandomPool prng;

	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	Integer r = privKey.CalculateInverse(prng, c);
	string recovered;

	size_t req = r.MinEncodedSize();
	recovered.resize(req);

	r.Encode((byte *) &recovered[0], recovered.size());

	return recovered;
}

void encryptTestCase(ofstream& fout) {
	Integer n, e, d;

	const char* ns[] = {
		"0xb14022eef719f1bb", 
		"0xb2c8d1404ed5fc2f7ad1254bb428f0d5",
		"0xcf625a8e47bc1cf9a3b517b31d870108c0cd97466003842a3b394d6cd857e9b7"
	};
	const char* es[] = {
		"0x11",
		"0x11",
		"0x10001"
	};
	const string plainTexts[] = {
		"Alice",
		"Hello World!",
		"RSA is public key.",
	};

	int smlCase = 0, bigCase = 3;
	for (int i = smlCase; i < bigCase; i++) {
		n = Integer(ns[i]);
		e = Integer(es[i]);
		
		string ans = encrypt(n, e, plainTexts[i]);

		fout << ans << '\n';
		cout << ans << '\n';
	}
}

void decryptTestcase(ofstream& fout) {
	Integer n, e, d, c;

	const char* ds[] = {
		"0x16282b21a7866bf5",
		"0x12e6a85100b889c9905a939b274a91bc57ca85d52e6c464fb455c86a29d63c89"
	};
	const char* ns[] = {
		"0x9d001e6473dfacf9",
		"0xd6361e40b2d619970ead338912a273adb75a4ce21356304834753fe94e6de24b"
	};
	const char* cs[] = {
		"0x154c638cd3615216",
		"0xa1676afd68a2fc67dac32c633600b76fa90aca9f9cca5201490a20c8b01a061a"
	};
	const unsigned int bits[] = {
		64,
		256
	};

	int smlCase = 0, bigCase = 2;
	for (int i = smlCase; i < bigCase; i++) {
		n = Integer(ns[i]);
		d = Integer(ds[i]);
		c = Integer(cs[i]);

		e = Integer("0");

		while (true) {
			RSA::PrivateKey privKey;
			try {
				privKey.Initialize(n, d, e);
			} catch(InvalidArgument k) {
				e = e + 1;
				continue;
			}
			string ans = decrypt(n, e, d, c);

			cout << "Publice Key = " << hex << e << '\n';
			cout << ans << '\n';
			
			fout << hex << e << '\n';
			fout << ans << '\n';
			break;
		}
	}
}

int main() {
	ofstream fout;
	fout.open("output.txt");

	encryptTestCase(fout);
	decryptTestcase(fout);

	return 0;
}

/* Output

73dc304c7bf6a0fd
4fd46914533f2735ca7e692f1d3ae5b0
295de4ebe864de606d7e9c3de4bde243c3f7cb3447bca511dd665103e3949912
Publice Key = 10001h
Secret
Publice Key = 11h
ECC has shorter keys.

*/