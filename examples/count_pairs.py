#!/usr/bin/python

import os,sys
import fileinput

data = []

def isPowerOfTwo(x):
 return ((x != 0) and ((x & (~x + 1)) == x))

for line in fileinput.input():
	cur = int(line, 2)
	data.append(cur)

counter = 0
for i in data:
 for j in data:
  if isPowerOfTwo(i^j):
   counter = counter+1
print counter
