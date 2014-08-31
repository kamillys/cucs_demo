#!/usr/bin/python

import os,sys
import fileinput

data = []

def isPowerOfTwo(x):
 return ((x != 0) and ((x & (~x + 1)) == x))

for line in fileinput.input():
	cur = int(line, 2)
	data.append(cur)

for i in xrange(0, len(data)):
 for j in xrange(0, len(data)):
  if isPowerOfTwo(data[i]^data[j]):
   print i, j
