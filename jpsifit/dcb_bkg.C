#include "TLorentzVector.h"
#include <vector>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "RooGenericPdf.h"
#include "RooTFnBinding.h"

#include "RooCrystalBall.h"
#include "RooExponential.h"

using namespace RooFit;


int dcb_bkg(){


TFile *inFile = new TFile("/store/user/reynolmz/JpsiHist_HighMult.root","READ");
TH1D *real_mass;
real_mass = (TH1D *)inFile->Get(Form("histDir/hJpsiMass"));

  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);

 real_mass->SetTitle(" "); 
 real_mass->SetMinimum(0.0001);
 real_mass->SetXTitle("m_{#mu#mu} (GeV/c^{2})");
 real_mass->SetYTitle("Events / (0.02 GeV)"); 
 real_mass->SetMaximum(real_mass->GetMaximum()*1.3);
 real_mass->GetXaxis()->CenterTitle(1);
 real_mass->GetYaxis()->CenterTitle(1);
 real_mass->GetYaxis()->SetTitleOffset(1.1);
 real_mass->GetXaxis()->SetTitleOffset(0.95);
 real_mass->GetXaxis()->SetTitleSize(0.066);
 real_mass->GetYaxis()->SetTitleSize(0.066);
 real_mass->GetXaxis()->SetLabelSize(0.05);
 real_mass->GetYaxis()->SetLabelSize(0.05);
 real_mass->GetXaxis()->SetNdivisions(512);
real_mass->SetMarkerStyle(20);
real_mass->SetMarkerSize(1.2);
real_mass->Draw("pez");
gStyle->SetOptStat(0);
//real_mass->SetTitle(";m(J/#psi) [GeV];");
//real_mass->Fit("dcb");
TLegend *LEG = new TLegend(0.6,0.8,0.89,0.89);
//LEG->AddEntry(dcb,"Double Sided Crystal Ball");
//LEG->SetBorderSize(0);
//LEG->Draw("sames");


//Roofit
RooRealVar bMass("m(J/#psi)","m(J/#psi) [GeV]",2.5,3.5);
RooDataHist hist("hist","hist",bMass,Import(*real_mass));

//DCB parameters
RooRealVar mu("mu","mu",3.1,2.5,3.5);
RooRealVar width("width","width",0.03,0.,1.);
RooRealVar a1("a1","a1",1,0.,100.);
RooRealVar p1("p1","p1",1,0.,100.);
RooRealVar a2("a2","a2",1,0.,100.);
RooRealVar p2("p2","p2",1,0.,100.);

//RooCrystalBall dcbPdf("dcbPdf","DoubleSidedCB",bMass,mu,width,a1,p1,a2,p2);
RooCrystalBall dcbPdf("dcbPdf","DoubleSidedCB",bMass,mu,width,a1,p1,a1,p1);

//BKG exp parameters
RooRealVar c_exp("c_exp","c_exp",-2,-10,10);
RooExponential expPdf("expPdf", "Exponential", bMass, c_exp);

// Sum the composite signal and background
//RooRealVar bkgfrac("bkgfrac", "fraction of background", 0.3, 0., 1.);
RooRealVar sigfrac("sigfrac", "fraction of signal", 0.1, 0., 1.);
RooAddPdf dcb_exp_Pdf("dcb_exp_Pdf", "dcb+exp", RooArgList(dcbPdf, expPdf), sigfrac);

auto result = dcb_exp_Pdf.fitTo(hist, RooFit::Save(true));
result->Print();

auto pl = bMass.frame();

hist.plotOn(pl, LineColor(1), LineWidth(1), DrawOption("pez"));
dcb_exp_Pdf.plotOn(pl, LineColor(2), LineWidth(2), LineStyle(1));
dcb_exp_Pdf.plotOn(pl, Components(dcbPdf), LineColor(kOrange-4), LineWidth(2), LineStyle(2), DrawOption("F"),FillColor(kOrange-4));
dcb_exp_Pdf.plotOn(pl, Components(expPdf), LineColor(4), LineWidth(2), LineStyle(2));

pl->Draw("same"); 
real_mass->Draw("samepez");

// legend
TH1D *fSig = new TH1D("fSig", "fSig",10, 0, 1);
TF1  *fBkg = new TF1("fBkg", "1", 0, 1);
TF1  *fSigBkg = new TF1("fSigBkg", "1", 0, 1);
fSig->SetLineColor(kOrange-4);
fSig->SetFillStyle(3001);
fSig->SetFillColor(kOrange-4);
//fSig->SetLineWidth(3);
//fSig->SetLineStyle(2);
fBkg->SetLineColor(4);
fBkg->SetLineWidth(2);
fBkg->SetLineStyle(2);
fSigBkg->SetLineColor(2);
fSigBkg->SetLineWidth(2);

    TLegend  *leg =  new TLegend(0.7, 0.72, 0.84, 0.93);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetFillColor(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->AddEntry(real_mass, "data", "pl");
    leg->AddEntry(fSigBkg, "Fit", "l");
    leg->AddEntry(fSig, "J/#psi Signal", "f");
    leg->AddEntry(fBkg, "Background", "l");
    leg->Draw("same");

c1->SaveAs("plot_dcb_bkg.C");
c1->SaveAs("plot_dcb_bkg.png");
c1->SaveAs("plot_dcb_bkg.pdf");

return 0;
}

