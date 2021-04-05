
import numpy as np

plainText = "meet me at the usual place at ten rather than eight o clock"

def main():
	print("Plain =", plainText)

	key = np.array([ [7, 3], 
					 [2, 5]])

	print("Key =\n", key)

	texts = plainText.replace(' ', '')
	ciper = ""

	n = len(texts)
	if n % 2 == 1:
		texts = texts + 'q'

	for i in range(0, n, 2):
		s1 = ord(texts[i])
		s2 = ord(texts[i + 1])

		now = np.array([int(s1 - ord('a')), int(s2 - ord('a'))])
		now = now.dot(key)

		c = chr((now[0] % 26) + ord('a'))
		ciper = ciper + c

		c = chr((now[1] % 26) + ord('a'))
		ciper = ciper + c

	print("\nCipher =", ciper)


if __name__ == '__main__':
	main()	

"""
Plain = meet me at the usual place at ten rather than eight o clock
Key =
 [[7 3]
 [2 5]]

Cipher = oeodoemrroqikywdxwekcmpwczpzroktroansaebfxkjyayg
"""