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

int writeraw(){
    TFile *f = new TFile("raw.root","RECREATE");
    TTree *t = new TTree("tree","data from ascii file");
    std::vector<float> vec;
    t->Branch("data",&vec);

    std::ifstream in("../data/2021.raw", std::ios::in);
    std::string str;
    while(getline(in, str)){
        str = str + ' ';
        std::string::size_type size = str.size();
        std::string::size_type pos = 0;
        vec.clear();
        for(std::string::size_type i = 0; i < size; i = pos + 1){
            pos = str.find(' ', i);
            if(pos >= size){
                break;
            }
            std::string s = str.substr(i, pos - i);
            TString num(s);
            vec.emplace_back(num.Atof());
        }
        t->Fill();
    };

    f->Write();

    return 0;
}
