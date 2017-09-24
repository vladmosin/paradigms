import numpy as np


def rightsize(a):
	k = 1
	n = len(a[0])
	while k < n:
		k *= 2
	x = np.zeros((n, k - n))
	y = np.zeros((k - n, k))
	r = np.vstack((y, np.hstack((a, x))))
	return r
	
	
def multiply(a, b):
	f = len(a[0])
	r = np.zeros((f,f))
	for i in range(f):
		for k in range(f):
			for j in range(f):
				c[i][j] = a[i][k] + b[k][j]
	return r
	
	
def inp(n):
	a = np.zeros((n, n))
	for i in range(n):
		ls = input().split()
		for index in range(n):
			a[i][index] = int(ls[index])
	return a


def summ(a, b):
	n = len(a[0])
	c = np.zeros((n, n))
	for i in range(n):
		for j in range(n):
			c[i][j] = a[i][j] + b[i][j]
	return c


def dif(a, b):
	n = len(a[0])
	c = np.zeros((n, n))
	for i in range(n):
		for j in range(n):
			c[i][j] = a[i][j] - b[i][j]
	return c
			
	
def shtrassen(a, b):
	n = len(a[0])
	if n < 5:
		array = multiply(a, b)
		return array
	else:
		a11 = a[:n//2, :n//2]
		a12 = a[:n//2, n//2+1:]
		a21 = a[n//2 + 1:, :n//2]
		a22 = a[n//2+1:, n//2+1:]
		b11 = b[:n//2,:n//2]
		b12 = b[:n//2, n//2+1:]
		a21 = b[n//2 + 1:, :n//2]
		b22 = b[n//2+1:,n//2+1:]
		p1 = shtrassen(summ(a11, a22), summ(b11, b22))
		p2 = shtrassen(summ(a21, a22), b11)
		p3 = shtrassen(a11, dif(b12, b22))
		p4 = shtrassen(a22, dif(b21, b11))
		p5 = shtrassen(summ(a11, a12), b22)
		p6 = shtrassen(dif(a21, a11), summ(b11, b12))
		p7 = shtrassen(dif(a12, a22), summ(b21, b22))
		c11 = summ(dif(summ(p1, p4), p5), p7)
		c12 = summ(p3, p5)
		c21 = summ(p2, p4)
		c22 = summ(dif(summ(p1, p3), p2), p6)
		c1 = np.hstack(c11, c12)
		c2 = np.hstack(c21, c22)
		c = np.vstack(c1, c2)
		return c


def main():
	n = int(input())
	a = rightsize(inp(n))
	b = rightsize(inp(n))
	c = shtrassen(a, b)
	return c
if __name__ == "__main__":
	main()	


	
				

