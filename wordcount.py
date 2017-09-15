def print_words(words):
    d=dict()
    for s in words:
        if s not in d:
            d[s]=1;
        else:
            d[s]+=1
    max=0
    for key in d:
        if d[key]>max:
            max=d[key]
    while(max>0):
        for key in d:
            if (d[key])==max:
                print(key+'\n')
        max-=1
def print_top(words):
    d=dict()
    for s in words:
        if s not in d:
            d[s]=1;
        else:
            d[s]+=1
    max=0
    v=0
    for key in d:
        if d[key]>max:
            max=d[key]
    while(max>0 and v<2):
        for key in d:
            if (d[key])==max:
                print(key+'\n')
                v+=1
        max-=1       
        
