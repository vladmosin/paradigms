def di(words):
    d = dict()
    for s in words:
        s1 = s.lower();
        if s1 not in d:
            d[s1] = 1;
        else:
            d[s1] += 1
    return d


def print_words(words):
    d = di(words)
    for ukaz in sorted(d.keys()):
        print(ukaz, d[ukaz])

        
def print_top(words):
    d = di(words)
    d1 = sorted(d.keys(), key = lambda k : d[k], reverse = True)
    for uk in d1[:20]:
        print(uk, d[uk])
