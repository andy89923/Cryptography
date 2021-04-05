#include <bits/stdc++.h>
using namespace std;
#include "DES.cpp"

char toHex(int x) {
	if (x >= 10) return 'A' + x - 10;
	return '0' + x;
}

string textToHex(string s) {
	string ans = "";
	for (int i = 0; i < 8; i++) {
		int num = (int) s[i];

		int f = num / 16; num %= 16;
		int s = num;

		ans = ans + toHex(f);
		ans = ans + toHex(s);
	}
	return ans;
}

DES solver;

int main() {
	ifstream fin; 
	ofstream fout;

	string ss, key, plainText;

	fin.open("DES-Key-Plaintext.txt");
	fout.open("out.txt");

	double cpu_time_used_sum = 0.0;
	int cpu_time_used_cnt = 0;

	while (getline(fin, ss)) {
		key = "";
		plainText = "";
		for (int i = 0; i < 8; i++) {
			char c = ss[i];
			key = key + ss[i];
		}

		for (int i = 9; i < 17; i++) {
			char c = ss[i];
			plainText = plainText + c;
		}
		cout << "Key = " << key << '\n';
		cout << "Plain Text = " << plainText << '\n';
		
		key = textToHex(key);
		plainText = textToHex(plainText);

		string cipherText = solver.encrypt(plainText, key);

		cout << "Cipher Text = " << cipherText << "\n";
		fout << cipherText << '\n';

		// Test time
		const int testRound = 100;

		clock_t t_start, t_end;
		double cpu_time_used = 0.0;
		for (int i = 0; i < testRound; i++) {
			t_start = clock();

			solver.encrypt(plainText, key);

			t_end = clock();

			cpu_time_used += (double (t_end - t_start)) / CLOCKS_PER_SEC;
			cpu_time_used_cnt += 1;
		}
		cpu_time_used_sum += cpu_time_used;
		
		cpu_time_used /= testRound;
		cpu_time_used *= 1000;

		cout << "Ave. Time: " << cpu_time_used << " ms\n\n";
	}
	double ans_time = cpu_time_used_sum / cpu_time_used_cnt * 1000.0;
	fout << ans_time << '\n';

	cout << "=======================\n";
	cout << "Total Ave. Time: " << ans_time << " ms\n";
	return 0;
}