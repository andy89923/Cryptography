
import numpy as np

plainText = "cryptographic"

def main():
	print("Plain =", plainText)

	key = "eng"
	print("Key =", key)

	texts = plainText.replace(' ', '')
	ciper = ""

	n = len(texts)
	m = len(key)

	p = 0
	for i in texts:
		c = chr((ord(i) + ord(key[p]) - 2 * ord('a')) % 26 + ord('a'))
		ciper = ciper + c
		p = p + 1
		if p >= m:
			p = 0

	print("\nCipher =", ciper)

if __name__ == '__main__':
	main()	

"""
Plain = cryptographic
Key = eng

Cipher = geetgukegtuog
"""