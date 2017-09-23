import os
from os import walk
import sys
from os import path
from hashlib import sha1 as hasher
	
def hashing(s):
	with open(os.path.join(path, f_names), mode = 'rb') as f:
		h1 = hasher()
		s = f.read(1000)
		if len(s) != 0:
			n += h1.update(s).hexdigest()
	return n
def main():	
	s = sys.argv[1]
	d = dict()
	for path, _, files in walk(s):	
		for f_names in files:
			if f_files[0] != '.' and f.files[0] != '~' :
				if not os.path.islink(os.path.join(path, f_names)):
					n = hashing(os.path.join(path, f_names))
					if n not in d:
						d[n] = os.path.join(path, f_names)
					else:
						d[n].append(os.path.join(path, f_names))
	for hsh in d:
		if d[hsh].size() > 1:
			while lst in d[hsh]:
				print(lst.join(":"))
			print('\n')
if __name__ == "__main__":
	main()		
				
			
		
	
	

