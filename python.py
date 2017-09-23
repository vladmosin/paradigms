import os
from os import walk
import sys
from os import path
from hashlib import sha1 as hasher
	
def hashing(s):
	with open(s, mode = 'rb') as f:
		h1 = hasher()
		s1 = f.read(4096)
		if len(s1) != 0:
			n += h1.update(s1).hexdigest()
	return n
def main():	
	s = sys.argv[1]
	d = dict()
	for path, _, files in walk(s):	
		for f in files:
			if f[0] != '.' and f[0] != '~' and not os.path.islink(f):
					n = hashing(os.path.join(path, f))
					if n not in d:
						d[n] = os.path.join(path, f)
					else:
						d[n].append(os.path.join(path, f))
	for hsh in d:
		if d[hsh].size() > 1:
			while lst in d[hsh]:
				print(":".join(lst))
if __name__ == "__main__":
	main()		
				
			
		
	
	

