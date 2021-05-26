#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
using namespace CryptoPP;

int main() {
	ofstream fout;
	fout.open("sha256.txt");

	// string msg = "Hello!";
    string msg = "Bitcoin is a cryptocurrency, a form of electronic cash.";
	string digest, encoded;

	SHA256 hash;
	hash.Update((const byte*) msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((byte*)&digest[0]);

	StringSource ss( digest, true,
        new HexEncoder( 
        new StringSink( encoded ) )
    );

	cout << "Message: " << msg << endl;
	cout << "Digest: " << encoded << endl;

	fout << encoded << endl;
	return 0;
}
/*
Message: Hello!
Digest: 334D016F755CD6DC58C53A86E183882F8EC14F52FB05345887C8A5EDD42C87B7

Message: Bitcoin is a cryptocurrency, a form of electronic cash.
Digest: B22C6535F65B1CBBF6BB86EDF8010C7BB563E36059AB3A26F94F824A0CCB9B7C
*/