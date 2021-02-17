#!/usr/bin/env python3

import ROOT
from ROOT import TFile, TTree, gROOT, addressof
import numpy as np

rawDataName = '../data/2021.raw'
rawRootName = 'raw.root'

rootFile = ROOT.TFile(rawRootName, "RECREATE")
tree = ROOT.TTree("raw", "raw data")
vect = ROOT.std.vector("float")(100)
tree.Branch("raw", vect)
maxValue = np.empty((1), dtype=float)
maxIndex = np.empty((1), dtype=int)
maxIndexPercent = np.empty((1), dtype=float)
tree.Branch("maxValue", maxValue, "maxValue/F")
tree.Branch("maxIndex", maxIndex, "maxIndex/I")
tree.Branch("maxIndexPercent", maxIndexPercent, "maxIndexPercent/F")
for line in open(rawDataName):
    nums = line.split(' ')
    #为了偷懒使用python中的内置函数
    li = list()
    for num in nums:
        if not num: continue
        li.append(float(num.strip()))
    li.reverse()
    #原始值保存
    vect.clear()
    for x in li:
        vect.emplace_back(x)

    total = sum(li)
    count = len(li)
    li = [100 * i/total for i in li]
    maxValue[0] = max(li)
    maxIndex[0] = li.index(maxValue[0])
    maxIndexPercent[0] = 100 * maxIndex[0]/count
    tree.Fill()

rootFile.Write()
