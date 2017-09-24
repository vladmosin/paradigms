import numpy as np


def rightsize(a):
	k = 1
	n = np.shape(a[0])
	while k < n:
		k *= 2
	x = np.zeros((n, k - n))
	y = np.zeros((k - n, k))
	r = np.vstack((y, np.hstack((a, x))))
	return r
	
	
def inp(n):
	a = ([],[])
	for i in range(n):
		ls = input().split()
		for index in range(n):
			a[i].append(int(j) for j in input().split())
 	return a

	
def shtrassen(a, b):
	n = np.shape(a[0])
	if n == 1:
		return a*b
	else:
		a11 = a[:n//2, :n//2]
		a12 = a[:n//2, n//2+1:]
		a21 = a[n//2 + 1:, :n//2]
		a22 = a[n//2+1:, n//2+1:]
		b11 = b[:n//2,:n//2]
		b12 = b[:n//2, n//2+1:]
		a21 = b[n//2 + 1:, :n//2]
		b22 = b[n//2+1:,n//2+1:]
		p1 = shtrassen((a11 + a22), (b11 + b22))
		p2 = shtrassen((a21 + a22), b11)
		p3 = shtrassen(a11, (b12 - b22))
		p4 = shtrassen(a22, (b21 - b11))
		p5 = shtrassen((a11 + a12), b22)
		p6 = shtrassen((a21 - a11), (b11 + b12))
		p7 = shtrassen((a12 - a22), (b21 + b22))
		c11 = p1 + p4 - p5 + p7
		c12 = p3 + p5
		c21 = p2 + p4
		c22 = p1 - p2 + p3 + p6
		c1 = np.hstack(c11, c12)
		c2 = np.hstack(c21, c22)
		c = np.vstack(c1, c2)
		return c


def main():
	n = int(input())
	a = rightsize(inp(n))
	b = rightsize(inp(n))
	c = shtrassen(a, b)
	for i in range(n):
		print(" ".join(c[i]))
		print('\n') 
if __name__ == "__main__":
	main()	


	
				

