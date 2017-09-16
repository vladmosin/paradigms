def verbing(s):
    if len(s) > 2:
        if s[-3:] == "ing":
            s = s + "ly"
        else:
            s = s + "ing"
    return s


def not_bad(s):
    a =- 1
    b =- 1
    a = s.find("not")
    b = s.find("bad")
    if a < b and a !=- 1:
        s = s[:a] + "good" + s[b+3:]
    return s


def front_back(a, b):
    c = (len(a) + 1) // 2
    d = (len(b) + 1) // 2
    s = a[:c] + b[:d] + a[c:] + b[d:]
    return s;

