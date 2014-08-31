#!/usr/bin/python

import os,sys
import fileinput

for line in fileinput.input():
    cur = int(line, 2)
    print cur
