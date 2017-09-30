import numpy as np


def split_matrix(a):
    a1, a2 = np.vsplit(a, 2)
    a11, a12 = np.hsplit(a1, 2)
    a21, a22 = np.hsplit(a2, 2)
    return a11, a12, a21, a22


def round_to_power_of_two(n):
    k = 1
    while k < n:
        k *= 2
    return k


def print_matrix(c):
    n, _ = c.shape
    for i in range(n):
        print(*c[i])


def input_matrix(n, k):
    a = np.zeros((k, k), dtype=np.int)
    for index in range(n):
        a[index][:n] = [int(j) for j in input().split(" ")]
    return a


def strassen(a, b):
    n, _ = a.shape
    if n == 1:
        return a * b
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
        return np.vstack((np.hstack((p1 + p4 - p5 + p7, p3 + p5)),
                          np.hstack((p2 + p4, p1 - p2 + p3 + p6))))


def main():
    n = int(input())
    k = round_to_power_of_two(n)
    a = input_matrix(n, k)
    b = input_matrix(n, k)
    c = strassen(a, b)
    print_matrix(c[:n][:n])


if __name__ == "__main__":
    main()
