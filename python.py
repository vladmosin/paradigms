import os
from os import walk
import sys
from os import path
from hashlib import sha1 as hasher
	
def main():	
	s = sys.argv[1]
	d = dict()
	for path, _, files in walk(s):	
		for f_names in files:
			if f_files[0] != '.' and f.files[0] != '~' :
				if not os.path.islink(os.path.join(path, f_names)):
					with open(os.path.join(path, f_names), mode = 'rb') as f:
						h1 = hasher()
						n = h1.update(f.read()).hexdigest()
					if n not in d:
						d[n] = [1, os.path.join(path, f_names)]
					else:
						d[n][0] = 2
						d[n][1].append(os.path.join(path, f_names))
	for hsh in d:
		if d[hsh][0] == 2:
			while lst in d[hsh][1]:
				print(lst + ':')
			print('\n')
if __name__ == "__main__":
	main()		
				
			
		
	
	

