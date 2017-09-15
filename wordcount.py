def print_words(words):
    d=dict()
    for s in words:
        s1=s.lower();
        if s1 not in d:
            d[s1]=1;
        else:
            d[s1]+=1
    for ukaz in sorted(d.keys(),key=lambda k : d[k],reverse=False):
        print(ukaz,d[ukaz])
def print_top(words):
    d=dict()
    for s in words:
        s1=s.lower();
        if s1 not in d:
            d[s1]=1;
        else:
            d[s1]+=1
    d1=sorted(d.keys(),key=lambda k : d[k],reverse=False)
    if (len(d1)>20):
        for uk in d1[-20:]:
            print(uk,d[uk])
    else:
        for uk in d1:
            print(uk,d[uk])
        
