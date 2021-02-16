#!/usr/bin/env python3

import ROOT
import numpy as np

dataname = '../data/2021.raw'

for line in open(dataname):
    nums = line.split(' ')
    li = list()
    for num in nums:
        if not num: continue
        li.append(float(num.strip()))
    li.reverse()
    total = sum(li)
    num = len(li)
    li = [i/total for i in li]
    maxValue = max(li)
    maxIndex = li.index(maxValue)
    mean = np.mean(li)
    print("total value:%.02f, count:%d, max value:%.02f, index:%d, mean:%.02f" % (total, num, 100 * maxValue, maxIndex, 100 * mean) )
