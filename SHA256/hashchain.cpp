#include <bits/stdc++.h>
using namespace std;

#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
using namespace CryptoPP;

string toHex(string s) {
	string encoded;

	StringSource ss( s, true,
        new HexEncoder( 
        new StringSink( encoded ) )
    );

    return encoded;
}

const int maxDep = 7;
string ans_img[maxDep + 1], ans_non[maxDep + 1], ans_has[maxDep + 1];

bool dfs(string digesti, int dep) {
	if (maxDep < dep) return true;

	cout << "Finding on dep = " << dep << '\n';

	SHA256 hash;
	string msg, nonce, digest;
	int noncenum = -1;

	do {
		noncenum++;
		nonce = "";
		for (int i = 24; i >= 0; i -= 8) {
			char c = (char)((noncenum >> i) & 0xFF);
			nonce = nonce + c;
		}
		msg = digesti + nonce;

		hash.Update((const byte*) msg.data(), msg.size());
		digest.resize(hash.DigestSize());
		hash.Final((byte*)&digest[0]);

		string now = toHex(digest);
		int num = 0;
		while (now[num] == '0') num ++;

		if (num == dep) {
			if (dfs(digest, dep + 1)) {
				ans_img[dep] = toHex(digesti);
				ans_non[dep] = toHex(nonce);
				ans_has[dep] = now;
				return true;
			}
		}
	} while (noncenum != INT_MIN);

	cout << "Not Found on dep = " << dep << ", Back~\n";

	return false;
}

int main() {
	ofstream fout;
	fout.open("hashchain.txt");

	string msg = "Bitcoin", digest;
	
	SHA256 hash;
	hash.Update((const byte*) msg.data(), msg.size());
	digest.resize(hash.DigestSize());
	hash.Final((byte*)&digest[0]);
	
	dfs(digest, 0);

	for (int i = 0; i <= maxDep; i++) {
		fout << i << '\n';
		fout << ans_img[i] << '\n';
		fout << ans_non[i] << '\n';
		fout << ans_has[i] << '\n';

		cout << i << '\n';
		cout << ans_img[i] << '\n';
		cout << ans_non[i] << '\n';
		cout << ans_has[i] << '\n';
	}
	return 0;
}