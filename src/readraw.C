#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TDirectory.h"
#include "TObject.h"

int readraw(){
    TFile *f = new TFile("raw.root");
    TTree *t = (TTree*)f->Get("tree");
    TBranch *b = 0;
    std::vector<float> *param = 0;
    t->SetBranchAddress("param", &param, &b);

    TH1F *h = new TH1F("percent", "max percent", 20, 0, 100);

    int n = t->GetEntries();
    for(int i = 0; i < n; i++){
        t->GetEntry(i);
        h->Fill(param->at(2));
    }

    h->Draw();

    return 0;
}
