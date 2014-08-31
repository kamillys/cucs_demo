#!/usr/bin/python

import os,sys
import fileinput

prev = 0
isSorted = True
fails = 0

for line in fileinput.input():
    cur = int(line, 2)
    if prev > cur:
       isSorted = False;
       fails = fails + 1
    prev = cur

print isSorted
if not isSorted:
    print "Fails", fails