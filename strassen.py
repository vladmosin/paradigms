import numpy as np


def split_matrix(a):
    a1, a2 = np.hsplit(a, 2)
    a11, a12 = np.vsplit(a1, 2)
    a21, a22 = np.vsplit(a2, 2)
    return a11, a12, a21, a22


def to_two_degree(n):
    k = 1
    while k < n:
        k *= 2
    return k


def print_matrix(c, n):
    for i in range(n):
        print(*c[i][:n])


def input_matrix(n, k):
    a = np.zeros((k, k), dtype=np.int)
    for index in range(n):
        a[index][:n] = [int(j) for j in input().split(" ")]
    return a


def strassen(a, b):
    n = np.shape(a)[0]
    if n == 1:
        return a*b
    else:
        a11, a12, a21, a22 = split_matrix(a)
        b11, b12, b21, b22 = split_matrix(b)
        p1 = strassen((a11 + a22), (b11 + b22))
        p2 = strassen((a21 + a22), b11)
        p3 = strassen(a11, (b12 - b22))
        p4 = strassen(a22, (b21 - b11))
        p5 = strassen((a11 + a12), b22)
        p6 = strassen((a21 - a11), (b11 + b12))
        p7 = strassen((a12 - a22), (b21 + b22))
        return np.vstack((np.hstack((p1 + p4 - p5 + p7, p3 + p5)), np.hstack((p2 + p4, p1 - p2 + p3 + p6))))


def main():
    n = int(input())
    k = to_two_degree(n)
    a = input_matrix(n, k)
    b = input_matrix(n, k)
    c = strassen(a, b)
    print_matrix(c, n)


if __name__ == "__main__":
    main()
