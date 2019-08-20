#!/usr/bin/python3
import sys

debug_file = open('output.txt', 'w')

for row in sys.stdin:
<<<<<<< HEAD
	if any(s in row for s in ('DEBUG', 'DP', 'FSM')):
		debug_file.write(row)
	else:
		print(row.strip())
		
=======
    if any(s in row for s in ('DEBUG', 'DP', 'FSM')):
        debug_file.write(row)
    else:
        print(row.strip())

>>>>>>> PSE-univr-project/master
debug_file.close()
