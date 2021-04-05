#include <bits/stdc++.h>
using namespace std;
#define BS bitset 
#define BIT64 64
#define BIT56 56
#define BIT48 48
#define BIT32 32
#define BIT28 28
#define BIT16 16
#define BIT4  4

struct DES {
	const int IP[BIT64] = {
		58, 50, 42, 34, 26, 18, 10,  2,
		60, 52, 44, 36, 28, 20, 12,  4,
		62, 54, 46, 38, 30, 22, 14,  6,
		64, 56, 48, 40, 32, 24, 16,  8,
		57, 49, 41, 33, 25, 17,  9,  1,
		59, 51, 43, 35, 27, 19, 11,  3,
		61, 53, 45, 37, 29, 21, 13,  5,
		63, 55, 47, 39, 31, 23, 15,  7
	};
	const int invIP[BIT64] = {
		40,  8, 48, 16, 56, 24, 64, 32,
		39,  7, 47, 15, 55, 23, 63, 31,
		38,  6, 46, 14, 54, 22, 62, 30,
		37,  5, 45, 13, 53, 21, 61, 29,
		36,  4, 44, 12, 52, 20, 60, 28,
		35,  3, 43, 11, 51, 19, 59, 27,
		34,  2, 42, 10, 50, 18, 58, 26,
		33,  1, 41,  9, 49, 17, 57, 25
	};
	const int expTab[BIT48] = {
	  	32,  1,  2,  3,  4,  5,
	   	 4,  5,  6,  7,  8,  9,
	     8,  9, 10, 11, 12, 13,
	   	12, 13, 14, 15, 16, 17,
	   	16, 17, 18, 19, 20, 21,
	   	20, 21, 22, 23, 24, 25,
	   	24, 25, 26, 27, 28, 29,
	   	28, 29, 30, 31, 32, 01
	};
	const int sBox[8][BIT4][BIT16] = {
		{   /* S1 */
			14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
			0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
			4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
			15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
		},{ 
			/* S2 */
			15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
			3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
			0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
			13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
		},{ /* S3 */
			10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
			13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
			13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
			1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
		},{ /* S4 */
			7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
			13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
			10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
			3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
		},{ /* S5 */
			2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
			14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
			4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
			11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
		},{ /* S6 */
			12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
			10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
			9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
			4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
		},{ /* S7 */
			4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
			13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
			1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
			6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
		},{ /* S8 */
			13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
			1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
			7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
			2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
		}
	};
	// Key -> Permutaion
	const int pmtTable[BIT32] = {
		16,  7, 20, 21, 29, 12, 28, 17,
		 1, 15, 23, 26, 05, 18, 31, 10,
		 2,  8, 24, 14, 32, 27,  3,  9,
		19, 13, 30,  6, 22, 11,  4, 25
	};
	const int p1table[BIT56] = {
		57, 49, 41, 33, 25, 17,  9,  1,
		58, 50, 42, 34, 26, 18, 10,  2,
		59, 51, 43, 35, 27, 19, 11,  3,
		60, 52, 44, 36, 63, 55, 47, 39,
		31, 23, 15,  7, 62, 54, 46, 38,
		30, 22, 14,  6, 61, 53, 45, 37,
		29, 21, 13,  5, 28, 20, 12,  4
	};
	const int p2table[BIT48] = {
		14, 17, 11, 24,  1,  5,  3, 28,
		15,  6, 21, 10, 23, 19, 12,  4,
		26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32
	};
	const int shiftNumber[BIT16] = {
		1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
	};

	int hexToDc(char c) {
		if (c >= 'A' && c <= 'F') return c - 'A' + 10;
		return c - '0'; 
	}

	// p1table 
	BS<BIT56> compressKey(BS<BIT64> key) {
		BS<BIT56> ret; ret.reset();
		for (int i = 0; i < BIT56; i++) 
			ret[i] = key[p1table[i] - 1];
		return ret;
	} 

	// p2table
	BS<BIT48> genSubKey(BS<BIT56> key) {
		BS<BIT48> ret; ret.reset();
		for (int i = 0; i < BIT48; i++) 
			ret[i] = key[p2table[i] - 1];
		return ret;
	}

	BS<BIT56> keyShift(BS<BIT56> key, int t) {
		BS<BIT28> lef, rig;
		lef.reset();
		rig.reset();

		for (int i = 0; i < 28; i++) {
			lef[i] = key[i];
			rig[i] = key[i + 28];
		}
		int tmp;
		for (int i = 1; i <= t; i++) {
			tmp = lef[0]; lef >>= 1;
			lef[27] = tmp;

			tmp = rig[0]; rig >>= 1;
			rig[27] = tmp;
		}
		for (int i = 0; i < 28; i++) {
			key[i] = lef[i];
			key[i + 28] = rig[i];
		}
		return key;
	}

	// expTab
	BS<BIT48> expandBit(BS<BIT32> rig) {
		BS<BIT48> ret; ret.reset();
		for (int i = 0; i < BIT48; i++) 
			ret[i] = rig[expTab[i] - 1];
		return ret;
	}

	BS<BIT32> sBoxComps(BS<BIT48> now) {
		BS<BIT32> ret; ret.reset();

		int k = 0, p = 0;
		for (int i = 0; i < 8; i++) {
			int tmp = now[k] * 2 + now[k + 5];
			int poi = now[k + 1] * 8 + now[k + 2] * 4 + now[k + 3] * 2 + now[k + 4];

			int num = sBox[i][tmp][poi];
			for (int j = 8; j >= 1; j /= 2) {
				if (num >= j) {
					ret[p] = 1;
					num -= j;
				}
				p ++;
			}
			k += 6;
		}
		return ret;
	}

	BS<BIT32> fFunc(BS<BIT32> rig, BS<BIT48> key) {
		BS<BIT48> now = expandBit(rig) ^ key;
		BS<BIT32> tmp = sBoxComps(now), ret;

		// straight permutation
		for (int i = 0; i < BIT32; i++) {
			ret[i] = tmp[pmtTable[i] - 1];
		}
		return ret;
	}

	BS<BIT64> textPermu(BS<BIT64> txt, const int* table) {
		BS<BIT64> ret; ret.reset();
		for (int i = 0; i < BIT64; i++) 
			ret[i] = txt[table[i] - 1];
		return ret;
	}

	BS<BIT64> hexToBin(string s) {
		if (s.length() != 16) {
			assert("Text's length != 16");
			exit(0);
		}
		bitset<64> bs; bs.reset();
		for (int i = 0; i < 16; i++) {
			
			int now = hexToDc(s[i]), k = 8;
			for (int j = 0; j < 4; j++) {
				if (now >= k) {
					bs[i * 4 + j] = 1;
					now -= k;
				}
				k /= 2;
			}
		}
		return bs;
	}

	string binToHex(BS<BIT64> b) {
		string ans = "";
		for (int i = 0; i < 64; i += 4) {
			int now = b[i] * 8 + b[i+1] * 4 + b[i+2] * 2 + b[i+3];

			char c;
			if (now >= 10)
				c = 'A' + now - 10;
			else
				c = now + '0';

			ans = ans + c;
		}
		return ans;
	}

	const int numberOfRound = 16;
	string encrypt(string plainText, string keyText) {
		BS<BIT64> binPla = hexToBin(plainText);
		BS<BIT64> binKey = hexToBin(keyText);
		BS<BIT56> nowKey = compressKey(binKey);

		binPla = textPermu(binPla, IP);
		BS<BIT32> lef, rig, tmp;
		for (int j = 0; j < BIT32; j++) {
			lef[j] = binPla[j];
			rig[j] = binPla[j + 32];
		}

		for (int i = 0; i < numberOfRound; i++) {
			nowKey = keyShift(nowKey, shiftNumber[i]);

			tmp = rig;
			rig = fFunc(rig, genSubKey(nowKey)) ^ lef;
			lef = tmp;
		}
		swap(lef, rig);

		for (int j = 0; j < BIT32; j++) {
			binPla[j] = lef[j];
			binPla[j + 32] = rig[j];
		}
		binPla = textPermu(binPla, invIP);

		string cipherText = binToHex(binPla);
		return cipherText;
	}

	string decrypt(string cipherText, string keyText) {
		BS<BIT64> binCip = hexToBin(cipherText);
		BS<BIT64> binKey = hexToBin(keyText);
		BS<BIT56> nowKey = compressKey(binKey);
		BS<BIT56> tmpKey;

		binCip = textPermu(binCip, IP);

		BS<BIT32> lef, rig, tmp;
		for (int j = 0; j < BIT32; j++) {
			lef[j] = binCip[j];
			rig[j] = binCip[j + 32];
		}
		swap(lef, rig);

		for (int i = numberOfRound - 1; i >= 0; i--) {
			tmpKey = nowKey;
			for (int j = 0; j <= i; j++) tmpKey = keyShift(tmpKey, shiftNumber[j]);

			tmp = lef;
			lef = fFunc(lef, genSubKey(tmpKey)) ^ rig;
			rig = tmp;
		}
		for (int j = 0; j < BIT32; j++) {
			binCip[j] = lef[j];
			binCip[j + 32] = rig[j];
		}
		binCip = textPermu(binCip, invIP);

		string plainText = binToHex(binCip);
		return plainText;
	}
};

// int main() {
// 	string plainText = "123456ABCD132536";
// 	string key = "AABB09182736CCDD";

// 	// cout << "Test key Shift \n";
// 	// BS<56> b;
// 	// b.reset();

// 	// b[0] = 1; b[28] = 1;

// 	// b = des.keyShift(b, 1);

// 	// cout << "Result\n";
// 	// cout << b[0] << ' ' << b[27] << '\n';
// 	// cout << b[28] << ' ' << b[55] << '\n';

// 	cout << des.encrypt(plainText, key) << '\n';

// 	return 0;
// }
/*
plainText = "123456ABCD132536";
key = "AABB09182736CCDD";
will generate
round    left       right     Round Key
   1    18CA18AD    5A78E394  194CD072DE8C
   2    5A78E394    4A1210F6  4568581ABCCE
   3    4A1210F6    B8089591  06EDA4ACF5B5
   4    B8089591    236779C2  DA2D032B6EE3
   5    236779C2    A15A4B87  69A629FEC913
   6    A15A4B87    2E8F9C65  C1948E87475E
   7    2E8F9C65    A9FC20A3  708AD2DDB3C0
   8    A9FC20A3    308BEE97  34F822F0C66D
   9    308BEE97    10AF9D37  84BB4473DCCC
  10    10AF9D37    6CA6CB20  02765708B5BF
  11    6CA6CB20    FF3C485F  6D5560AF7CA5
  12    FF3C485F    22A5963B  C2C1E96A4BF3
  13    22A5963B    387CCDAA  99C31397C91F
  14    387CCDAA    BD2DD2AB  251B8BC717D0
  15    BD2DD2AB    CF26B472  3330C5D9A36D
  16    19BA9212    CF26B472  181C5D75C66D
Plain  Text: 123456ABCD132536
Key        : AABB09182736CCDD
Cipher Text: C0B7A8D05F3A829C
Plain  Text: 0001001000110100010101101010101111001101000100110010010100110110
Key        : 1010101010111011000010010001100000100111001101101100110011011101
Cipher Text: 1100000010110111101010001101000001011111001110101000001010011100
*/