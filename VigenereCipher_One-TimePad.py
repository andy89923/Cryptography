
import numpy as np

plainText = "sendmoremoney"

def main():
	print("Plain =", plainText)

	key = [3, 11, 5, 7, 17, 21, 0, 11, 14, 8, 7, 13, 9]
	print("Key =", key)

	texts = plainText.replace(' ', '')
	ciper = ""

	n = len(texts)
	m = len(key)

	p = 0
	for i in texts:
		c = chr((ord(i) - ord('a') + key[p]) % 26 + ord('a'))
		ciper = ciper + c
		p = p + 1

	print("\nCipher =", ciper)

	ans = []

	target = "cashnotneeded"
	for i in range(n):
		if ord(target[i]) > ord(ciper[i]):
			ans.append(ord(ciper[i]) - ord('a') + 1 + ord('z') - ord(target[i]))
		else:
			ans.append(ord(ciper[i]) - ord(target[i]))

	print("\n")
	print("Target:", target)
	print("Ans =", ans)

if __name__ == '__main__':
	main()

"""
Plain = sendmoremoney
Key = [3, 11, 5, 7, 17, 21, 0, 11, 14, 8, 7, 13, 9]

Cipher = vpskdjrpawurh


Target: cashnotneeded
Ans = [19, 15, 0, 3, 16, 21, 24, 2, 22, 18, 17, 13, 4]
"""