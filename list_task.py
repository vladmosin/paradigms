def remove_adjacent(lst):
    for i in range(0,len(lst)-1):
        if(lst[i]==lst[i+1]):
            lst.pop(i)
    return lst
def linear_merge(lst1,lst2):
    a=0
    b=0
    lst=[]
    for i in range(0,len(lst1)+len(lst2)):
        if a==len(lst1):
            lst.append(lst2[b])
            b=b+1
        elif b==len(lst2):
            lst.append(lst1[a])
            a=a+1
        elif lst1[a]<lst2[b]:
            lst.append(lst1[a])
            a=a+1
        elif lst1[a]>=lst2[b]:
            lst.append(lst2[b])
            b=b+1
    return lst
