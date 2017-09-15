def verbing(s):
    if len(s)>2:
        print(s[-3:0])
        if s[-3:len(s)]=="ing":
            s=s+"ly"
        else:
            s=s+"ing"
    return s
def not_bad(s):
    if (s.find("bad")>s.find("not")):
        s1=s[s.find("not"):s.find("bad")+3]
        s=s.replace(s1,"good")
    return s
def front_back(a, b):
    s=a[0:(int)((len(a)-1)/2)+1]+b[0:(int)((len(b)-1)/2)+1]+a[(int)((len(a)+1)/2):len(a)]+b[(int)((len(b)+1)/2):len(b)]
    return s;

