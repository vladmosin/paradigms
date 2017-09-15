def print_words(words):
    d=dict()
    for s in words:
        s1=s.lower();
        if s1 not in d:
            d[s1]=1;
        else:
            d[s1]+=1
    for ukaz in sorted(d.keys(),key=lambda k : d[k],reverse=True):
        print(ukaz," ",d[ukaz])
def print_top(words):
    d=dict()
    for s in words:
        s1=s.lower();
        if s1 not in d:
            d[s1]=1;
        else:
            d[s1]+=1
    h=0
    for ukaz in sorted(d.keys(),key=lambda k : d[k],reverse=True):
        if h<20:
            print(ukaz," ",d[ukaz])
            h+=1
