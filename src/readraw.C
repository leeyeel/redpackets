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
    TBranch *bdata = 0;
    TBranch *bparam= 0;
    std::vector<float> *vdata= 0;
    std::vector<float> *vparam = 0;
    t->SetBranchAddress("data", &vdata, &bdata);
    t->SetBranchAddress("param", &vparam, &bparam);

    TH1F *total = new TH1F("percent", "The Position of the \"Luckiest Draw\"", 20, 0, 100);
    TH1F *h1 = new TH1F("percent", "The Position of the \"Luckiest Draw\"", 20, 0, 100);
    TH1F *h2 = new TH1F("percent", "The Position of the \"Luckiest Draw\"", 20, 0, 100);
    TCanvas *c1 = new TCanvas("c1","Histogram Drawing Options",200,10,1000,600);

    int n = t->GetEntries();
    for(int i = 0; i < n; i++){
        t->GetEntry(i);
        int size = vdata->size();
        if(size < 10){
            h1->Fill(vparam->at(2));
        }else{
            h2->Fill(vparam->at(2));
        }
        total->Fill(vparam->at(2));
    }

    total->GetYaxis()->SetTitle("counts");
    total->GetXaxis()->SetTitle("percent [%]");

    total->SetLineWidth(2);
    h1->SetLineWidth(2);
    h2->SetLineWidth(2);
    
    total->SetLineColor(kBlue);
    h1->SetLineColor(kGreen);
    h2->SetLineColor(kRed);

    total->SetMarkerStyle(21);
    total->SetMarkerColor(kBlue);
    h1->SetMarkerStyle(23);
    h1->SetMarkerColor(kGreen);
    h2->SetMarkerStyle(25);
    h2->SetMarkerColor(kRed);

    //total->Draw("ep");
    //h1->Draw("ep");
    h2->Draw("ep");

    c1->SetGrid();
    c1->Update();

    return 0;
}
