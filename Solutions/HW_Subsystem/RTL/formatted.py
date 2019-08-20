#!/usr/bin/python3
import sys

debug_file = open('output.txt', 'w')

for row in sys.stdin:
    if any(s in row for s in ('DEBUG', 'DP', 'FSM')):
        debug_file.write(row)
    else:
        print(row.strip())

debug_file.close()
