#include <memory>

#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TRandom.h>

#ifdef __MAKECINT__
#pragma link C++ class vector<float>+;
#endif

#define PI 3.14159265359
using namespace std; 

// String options in void args: 						     \\
// trig = HighMult, MinBias, or DiMuon depending on which data trigger is being used \\
// wrongsign = kFASLE or kTRUE depending on if the like-sign tree is being used      \\
// mult = the multiplicity cut 							     \\
// pTbin = pT_0_1, pT_1_2, pT_2_3, pT_3_4, pT_4_5, pT_5_6 for trigger pT binning     \\
// corr = refref or Jpsi depending on what trigger particle is being correlated      \\


const Int_t mBin = 11;

void Corr2D_Jpsi_loop_11mBin_shell(const TString shell = "", const TString pTbin = "", const TString mult = ""){

cout << "mult = " << mult << "  pTbin = " << pTbin << endl;

TString ver = "11mBins";
TString corr = "JpsiRef";
TString trig = "DM";

int nTrkCut;
//multiplicity bins
if(mult=="mult60")  nTrkCut = 60;
if(mult=="mult80")  nTrkCut = 80;
if(mult=="mult100")  nTrkCut = 100;

double ptMin_trg_;
double ptMax_trg_;
//pT bins for Jpsi
if(pTbin=="pT02"){
 ptMin_trg_ = 0.2;
 ptMax_trg_ = 1.8;
}

if(pTbin=="pT18"){
 ptMin_trg_ = 1.8;
 ptMax_trg_ = 3.0;
}

if(pTbin=="pT30"){
 ptMin_trg_ = 3.0;
 ptMax_trg_ = 4.5;
}

if(pTbin=="pT45"){
 ptMin_trg_ = 4.5;
 ptMax_trg_ = 6.0;
}

if(pTbin=="pT60"){
 ptMin_trg_ = 6.0;
 ptMax_trg_ = 8.0;
}

if(pTbin=="pT80"){
 ptMin_trg_ = 8.0;
 ptMax_trg_ = 10.0;
}

//pT bins for charged hadron
double ptMin_ass_ = 0.3;
double ptMax_ass_ = 3.0;

//mass bins
double massMin[mBin] = {2.55, 2.65, 2.75, 2.85, 2.95, 3.05, 3.15, 3.25, 3.35, 3.45, 3.55};
double massMax[mBin] = {2.65, 2.75, 2.85, 2.95, 3.05, 3.15, 3.25, 3.35, 3.45, 3.55, 3.65};
TString massBin[mBin] = {"mass26", "mass27", "mass28", "mass29", "mass30", "mass31", "mass32", "mass33", "mass34", "mass35", "mass36"};

//eta and rapidity cuts
double yMin_trg_ = -2.4;
double yMax_trg_ = 2.4;
//double etaMinN_trg_ = -2.4;
//double etaMaxN_trg_ = -1.2;
//double etaMinP_trg_ = 1.2;
//double etaMaxP_trg_ = 2.4;
double etaMin_ass_ = -2.4;
double etaMax_ass_ = 2.4;
double yMin_ass_ = -2.4;
double yMax_ass_ = 2.4;

double zMax = 8;
double zMin = -8;
int bkgFactor_ = 10;

//shell = gSystem->Getenv("getFile");

//input files from analyzer -- the shell variable runs multiple jobs in parallel
TFile* f1 = new TFile(Form("/store/user/reynolmz/%sTrack/%s", trig.Data(), shell.Data()));

//create new file to write output trees to -- will need to merge output
TFile *file = new TFile(Form("/nobackup/user/tuos/egamma/correlationsJpsi/mikeslurmtest/%s/%s/Corr2D_%s_%s_%s_%s_%s.root", mult.Data(), pTbin.Data(), corr.Data(), trig.Data(), mult.Data(), pTbin.Data(), shell.Data()), "RECREATE");

//loop over mass bins
for(Int_t m=0; m<mBin; m++){


TH1::SetDefaultSumw2();

vector<TVector3> *pVect_trg;
vector< vector<TVector3> > *pVectVect_trg;
vector<TVector3> *pVect_ass;
vector< vector<TVector3> > *pVectVect_ass;
vector<double> *zvtxVect;
vector<double> *zvtxVect_trg;


//TH1D::SetDefaultSumw2();
TH1D* hMult = new TH1D("mult","N",500,0,500);
TH2D* hSignal = new TH2D("signal","#Delta#eta,#Delta#phi",32,-4.8-0.15,4.8+0.15,32,-PI/2+PI/32,3*PI/2-PI/32);
TH2D* hBackground = new TH2D("background","#Delta#eta, #Delta#phi",32,-4.8-0.15,4.8+0.15,32,-PI/2+PI/32,3*PI/2-PI/32);
TH2D* hCorrelation = new TH2D("correlation","#Delta#eta, #Delta#phi",32,-4.8-0.15,4.8+0.15,32,-PI/2+PI/32,3*PI/2-PI/32);

TH1D* hDeltaPhi = new TH1D("deltaPhi","#Delta#phi",500, -2*PI, 2*PI);
TH1D* hDeltaEta = new TH1D("deltaEta","#Delta#eta",500, -4.0, 4.0);


pVectVect_trg = new vector< vector<TVector3> >;
pVectVect_ass = new vector< vector<TVector3> >;
zvtxVect = new vector<double>;
zvtxVect_trg = new vector<double>;


Int_t nTrk;
Int_t Ntrkoffline;
//Float_t phir0;
Float_t phi[20000];
Float_t pT[20000];
Float_t eta[20000];
Float_t bestvtxZ;

Float_t phi_trg[20000];
Float_t pT_trg[20000];
Float_t eta_trg[20000];
Float_t mass_trg[20000];
Float_t y_trg[20000];
Float_t bestvtxZ_trg;
UInt_t candSize;
Short_t nMatchedStationD1[20000];
Short_t nMatchedStationD2[20000];
Bool_t HighPurityDaughter1[20000];
Bool_t HighPurityDaughter2[20000];
Bool_t OneStMuon1[20000];
Bool_t OneStMuon2[20000];
Bool_t SoftMuon1[20000];
Bool_t SoftMuon2[20000];

//track-quality-cuts-tuos
Float_t trkPtErrOverPt[20000];
Float_t trkDzOverDzSigma[20000];
Float_t trkDxyOverDxySigma[20000];

//TFile* f2 = new TFile(Form("/home/reynolmz/JpsiAnalysis/Data/merged/dimuana%s_merged.root", trig.Data()));

TTree* t1 = (TTree*)f1->Get("trackana/TrackNtuple");
TTree* t2 = (TTree*)f1->Get("dimucontana/VertexCompositeNtuple");
t1->AddFriend(t2);

t1->SetBranchAddress("nTrk", &nTrk);
t1->SetBranchAddress("pT", &pT);
t1->SetBranchAddress("eta", &eta);
t1->SetBranchAddress("phi", &phi);
t1->SetBranchAddress("bestvtxZ", &bestvtxZ);   
 
//track-quality-cuts-tuos
t1->SetBranchAddress("trkPtErrOverPt", &trkPtErrOverPt);
t1->SetBranchAddress("trkDzOverDzSigma", &trkDzOverDzSigma);
t1->SetBranchAddress("trkDxyOverDxySigma", &trkDxyOverDxySigma);
 

t2->SetBranchAddress("Ntrkoffline", &Ntrkoffline);
t2->SetBranchAddress("pT", &pT_trg);
t2->SetBranchAddress("eta", &eta_trg);
t2->SetBranchAddress("phi", &phi_trg);
t2->SetBranchAddress("bestvtxZ", &bestvtxZ_trg);
t2->SetBranchAddress("candSize", &candSize);
t2->SetBranchAddress("mass", &mass_trg);
t2->SetBranchAddress("y", &y_trg);
t2->SetBranchAddress("nMatchedStationD1", &nMatchedStationD1);
t2->SetBranchAddress("nMatchedStationD2", &nMatchedStationD2);
t2->SetBranchAddress("HighPurityDaugther1", &HighPurityDaughter1);
t2->SetBranchAddress("HighPurityDaugther2", &HighPurityDaughter2);
t2->SetBranchAddress("OneStMuon1", &OneStMuon1);
t2->SetBranchAddress("OneStMuon2", &OneStMuon2);
t2->SetBranchAddress("softMuon1", &SoftMuon1);
t2->SetBranchAddress("softMuon2", &SoftMuon2);


long neve=t1->GetEntries();
long neve_goodz = 0;
long neve_highmult = 0;
long neve_hasCand = 0;
long neve_goodCand = 0;
cout<<"Nevts = "<<neve<<endl;

//long neve_trg=t2->GetEntries();
//long neve_trg_goodz = 0;
//long neve_trg_highmult = 0;
//cout<<"Nevts_trg = "<<neve_trg<<endl;



//loop over events (neve)
for(long ne=0; ne<50000; ne++){
//for(long ne=0; ne<neve; ne++){
  if(ne%10000==0)  cout<<"Have run "<<ne<<" events: "<<Form("%s, %s", pTbin.Data(), massBin[m].Data() )<<endl;
  
  t1->GetEntry(ne); 
  //cout <<bestvtxZ << "  " << bestvtxZ_trg << endl;  //sanity check
  //continue;

  //t2->GetEntry(ne);
  if (nTrk < nTrkCut) continue;
    neve_highmult++;
  if (bestvtxZ > zMax || bestvtxZ < zMin) continue;
  if (bestvtxZ_trg > zMax || bestvtxZ_trg < zMin) continue;
    neve_goodz++;
  //if (candSize < 1) continue;
  //if (candSize > 1) continue;
    neve_hasCand++;
  
  
  pVect_ass = new vector<TVector3>;
  pVect_trg = new vector<TVector3>;

  //loop over tracks
  for(int nh=0;nh<nTrk;nh++){
    double Eta = eta[nh];
    double Phi = phi[nh];
    double pt  = pT[nh];
         
      //cout << "pt = " << pT[nh] << endl;

//track-quality-cuts-tuos
    if(trkPtErrOverPt[nh]>=0.1 || trkDzOverDzSigma[nh]>=3.0 || trkDxyOverDxySigma[nh]>=3.0) continue;

    TVector3 pvector;
    pvector.SetPtEtaPhi(pt,Eta,Phi);
    if(eta[nh] <= etaMax_ass_ && eta[nh] >= etaMin_ass_ && pT[nh] <= ptMax_ass_ && pT[nh] >= ptMin_ass_) pVect_ass->push_back(pvector);
    //if (pT[nh]<=ptMax_ass_ && pT[nh]>=ptMin_ass_) pVect_ass->push_back(pvector);

  } // end of loop over tracks
  
  //loop over cands
  for(int nh=0;nh<candSize;nh++){
    //if (mass_trg[nh] < massMin[m] || mass_trg[nh] >= massMax[m] || fabs(y_trg[nh]) < 1.4 || fabs(y_trg[nh]) > 2.4) continue;
    if ((mass_trg[nh] < massMin[m]) || (mass_trg[nh] >= massMax[m])) continue;
    if(!(HighPurityDaughter1[nh] && HighPurityDaughter2[nh] && OneStMuon1[nh] && OneStMuon2[nh] && SoftMuon1[nh] && SoftMuon2[nh])) continue;
    neve_goodCand++;
    double Eta = eta_trg[nh];
    double Phi = phi_trg[nh];
    double pt  = pT_trg[nh];
         
      //cout << "pt = " << pT[nh] << endl;

    TVector3 pvector_trg;
    pvector_trg.SetPtEtaPhi(pt,Eta,Phi);
    if(y_trg[nh] < yMax_trg_ && y_trg[nh] >= yMin_trg_ && pT_trg[nh] < ptMax_trg_ && pT_trg[nh] >= ptMin_trg_) pVect_trg->push_back(pvector_trg);    
    //if(pT_trg[nh]<ptMax_trg_ && pT_trg[nh]>=ptMin_trg_) pVect_trg->push_back(pvector_trg);    
    //pVect_trg->push_back(pvector_trg);    
      //cout<<"work here"<<endl;
  
    //cout << "mass = " << mass_trg[nh] << endl;
  }//end loop over cands      	

  int nMult_trg = (int)pVect_trg->size();
  int nMult_ass = (int)pVect_ass->size();
  hMult->Fill(nMult_trg);
    //cout << "hMult = " << nMult_trg << endl;	

  //loop over trigger particle 
  for(int ntrg=0;ntrg<nMult_trg;ntrg++){
    TVector3 pvector_trg = (*pVect_trg)[ntrg];
    double eta_trg2 = pvector_trg.Eta();
    double phi_trg2 = pvector_trg.Phi();


    //loop over associated particle 
    for(int nass=0;nass<nMult_ass;nass++){
      TVector3 pvector_ass = (*pVect_ass)[nass];
      double eta_ass = pvector_ass.Eta();
      double phi_ass = pvector_ass.Phi();

      double deltaEta=eta_ass-eta_trg2;
      double deltaPhi=phi_ass-phi_trg2;

      if(deltaPhi>PI)
        deltaPhi=deltaPhi-2*PI;
      if(deltaPhi<-PI)
        deltaPhi=deltaPhi+2*PI;     
      
      
      if(deltaPhi>-PI && deltaPhi<-PI/2.)
        deltaPhi=deltaPhi+2*PI;

      if(deltaEta==0 && deltaPhi==0) continue;
     
      //if(fabs(deltaEta)<1.0)
      //hDeltaPhi->Fill(deltaPhi);
      //hDeltaEta->Fill(deltaEta);


      hSignal->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/nMult_trg);
      hSignal->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/nMult_trg);
      hSignal->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/nMult_trg);
      hSignal->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/nMult_trg);
      hSignal->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/nMult_trg);
      hSignal->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/nMult_trg);
    } //end loop over associated particle
  } //end loop over trigger particle

  pVectVect_trg->push_back(*pVect_trg);
  pVectVect_ass->push_back(*pVect_ass);
  zvtxVect->push_back(bestvtxZ);
  zvtxVect_trg->push_back(bestvtxZ_trg);

  delete pVect_trg;
  delete pVect_ass;
} // end of loop over events


int nevttotal_trg = (int)pVectVect_trg->size();
int nevttotal_ass = (int)pVectVect_ass->size();
  cout<<"nevttotal_trg="<<nevttotal_trg<<"  "<<"nevttotal_ass="<<nevttotal_ass<<endl;

for(int nround=0;nround<bkgFactor_;nround++){
  cout<<"nround="<<nround<<endl;
  for(int nevt_ass=0; nevt_ass<nevttotal_ass; nevt_ass++){
    int nevt_trg = gRandom->Integer(nevttotal_trg);
    if(nevt_trg == nevt_ass) { nevt_ass--; continue; }
    if(fabs((*zvtxVect_trg)[nevt_trg]-(*zvtxVect)[nevt_ass])>2.0) { nevt_ass--; continue; }
    //if(fabs((*zvtxVect_trg)[nevt_trg]-(*zvtxVect)[nevt_ass])>0.5) { nevt_ass--; continue; }

    vector<TVector3> pVectTmp_trg = (*pVectVect_trg)[nevt_trg];
    vector<TVector3> pVectTmp_ass = (*pVectVect_ass)[nevt_ass];
    int nMult_trg = pVectTmp_trg.size();
    int nMult_ass = pVectTmp_ass.size();
      //cout << "Nass = " << nMult_ass << endl;

    for(int ntrg=0;ntrg<nMult_trg;ntrg++){
      TVector3 pvectorTmp_trg = pVectTmp_trg[ntrg];
      double eta_trg2 = pvectorTmp_trg.Eta();
      double phi_trg2 = pvectorTmp_trg.Phi();
      
      for(int nass=0;nass<nMult_ass;nass++){
        TVector3 pvectorTmp_ass = pVectTmp_ass[nass];
        double eta_ass = pvectorTmp_ass.Eta();
        double phi_ass = pvectorTmp_ass.Phi();

        double deltaEta=eta_ass-eta_trg2;
        double deltaPhi=phi_ass-phi_trg2;
        if(deltaPhi>PI)
          deltaPhi=deltaPhi-2*PI;
        if(deltaPhi<-PI)
          deltaPhi=deltaPhi+2*PI;
        if(deltaPhi>-PI && deltaPhi<-PI/2.)
          deltaPhi=deltaPhi+2*PI;

        if(deltaEta==0 && deltaPhi==0) continue;

        hBackground->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/nMult_trg);
        hBackground->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/nMult_trg);
        hBackground->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/nMult_trg);
        hBackground->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/nMult_trg);
        hBackground->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/nMult_trg);
        hBackground->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/nMult_trg);
      }
    }
  }
}

int nEvent = hMult->Integral(2, 500);
hSignal->Scale(1.0/nEvent);
hBackground->Scale(1.0/hBackground->GetBinContent(hBackground->FindBin(0,0)));
hCorrelation->Add(hSignal);
hCorrelation->Divide(hBackground);

cout << "writing to file" << endl;
hMult->SetName(Form("hMult_%s", massBin[m].Data()));
hMult->Write();
//cout << Form("hMult_%s written", massBin[m].Data()) << endl;

hSignal->SetName(Form("hSignal_%s", massBin[m].Data()));
hSignal->Write();
//cout << Form("hSignal_%s written", massBin[m].Data()) << endl;

hBackground->SetName(Form("hBackground_%s", massBin[m].Data()));
hBackground->Write();
//cout << Form("hBackground_%s written", massBin[m].Data()) << endl;

hCorrelation->SetName(Form("hCorrelation_%s", massBin[m].Data()));
hCorrelation->Write();
//cout << Form("hCorrelation_%s written", massBin[m].Data()) << endl;

cout << "files written" << endl;

} //end loop over mass bin

cout << "closing file" << endl;
file->Close();
cout << "ALL DONE!" << endl;


} //end void
