#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/rijndael.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/rsa.h"
#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
using namespace CryptoPP;

int main() {
	Integer n("0x9d001e6473dfacf9");
	Integer e("0x10001");
	Integer d("0x16282b21a7866bf5");

	string message = "Secret", recovered;
	Integer m((const byte *)message.data(), message.size());

	// RSA::PublicKey pubKey;
	// pubKey.Initialize(n, e);

	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	RSA::PublicKey pubKey(privKey);

	cout << "e: " << hex << privKey.GetPublicExponent() << '\n';

	Integer c = pubKey.ApplyFunction(m);
	cout << "c: " << hex << c << endl;

	AutoSeededRandomPool prng;

	Integer r = privKey.CalculateInverse(prng, c);
	cout << "r: " << hex << r << endl;

	size_t req = r.MinEncodedSize();
	recovered.resize(req);

	r.Encode((byte *) &recovered[0], recovered.size());
	cout << "recovered: " << recovered << endl;

	return 0;
}