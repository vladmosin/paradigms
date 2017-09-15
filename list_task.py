def verbing(s):
    if len(s)>2:
        if s.endswith("ing"):
            s.concat("ing")
        else:
            s.concat("ly")
    return s
def not_bad(s):
    if (s.find("bad")>s.find("not")):
        s.replace(s[s.find("not"):s.find("bad")],"good")
    return s

