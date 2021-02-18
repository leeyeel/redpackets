#!/usr/bin/env python3

import ROOT
from ROOT import TFile, TTree, gROOT, addressof
import numpy as np

rawDataName = '../data/2021.raw'
rawRootName = 'raw.root'

rootFile = ROOT.TFile(rawRootName, "RECREATE")
tree = ROOT.TTree("tree", "raw data")
vect = ROOT.std.vector("float")(100)
param = ROOT.std.vector("float")(3)
tree.Branch("data", vect)
tree.Branch("param", param)
for line in open(rawDataName):
    nums = line.split(' ')
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
    li = [round(100 * x / total, 2) for x in li]
    for i in li:
        print(i)
    param.clear()
    maxv = max(li)
    param.emplace_back(maxv)
    param.emplace_back(li.index(maxv))
    param.emplace_back(100 * param[1] / count)

    tree.Fill()

rootFile.Write()
