#include <iostream>

#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TString.h"

#include <vector>

#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "Fit/Chi2FCN.h"
#include "TList.h"
#include "Math/WrappedMultiTF1.h"
#include "HFitInterface.h"

int iparmassfit_poly3bkg_floatwidth[8] = { 0, 1, 2, 3, 4, 5, 6, 7}; //8=5crystalball + 3exp
int iparvnfit_poly3bkg_floatwidth[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //12=5crystalball + 3exp + 3exp + 1v2signal

struct GlobalChi2_poly3bkg_floatwidth {
    GlobalChi2_poly3bkg_floatwidth(  ROOT::Math::IMultiGenFunction & f1,
                                   ROOT::Math::IMultiGenFunction & f2) :
    fChi2_1(&f1), fChi2_2(&f2) {}
    
    // parameter vector is first background (in common 1 and 2)
    // and then is signal (only in 2)
    double operator() (const double *par) const {
        double p1[8];
        for(int i = 0; i < 8; ++i) p1[i] = par[iparmassfit_poly3bkg_floatwidth[i]];
        
        double p2[12];
        for(int i = 0; i < 12; ++i) p2[i] = par[iparvnfit_poly3bkg_floatwidth[i]];
        
        return (*fChi2_1)(p1) + (*fChi2_2)(p2);
    }
    
    const  ROOT::Math::IMultiGenFunction * fChi2_1;
    const  ROOT::Math::IMultiGenFunction * fChi2_2;
};

void massfitvn_combine_jpsi( const char* input_mass = "/nobackup/user/tuos/egamma/simultaneousFit/jpsi/JpsiHist_DM.root",
      const char* input_v2 = "/nobackup/user/tuos/egamma/simultaneousFit/jpsi/Extract_v2.root",
      const char* output = "v2_jpsi_ana.root"
      )
{

   gStyle->SetOptStat(0);
    double fit_range_low = 2.4;
    double fit_range_high = 3.6;
    double jpsi_mass = 3.096916;
    TFile* file_mass = TFile::Open(input_mass);
    TFile* file_v2 = TFile::Open(input_v2);
   
   TFile* ofile= new TFile(output,"RECREATE");
    
    TF1* fmasssig[9];
    TF1* fmassswap[9];
    TF1* fmassbkg[9];
    TF1* fmasstotal[9];
    TF1* fvn[9];
    
    double pt[13];
    double KET_ncq[13];
    double v2[13];
    double v2e[13];
    double v2_bkg[13];
    double v2_ncq[13];
    double v2e_ncq[13];
    //double ptbin[14] = {1.5,2.4,3,3.5,4.0,5,6,7,8,10,11.5,15,20,30};
    double ptbin[14] = {1.8,3.0,3,3.5,4.0,5,6,7,8,10,11.5,15,20,30};
    double a[13];
    double b[13];
    double sigfrac[13];
    
    TCanvas* c[10];
    for(int i=0;i<1;i++) //10
    {
        c[i] = new TCanvas(Form("c_%d",i),Form("c_%d",i),800,400);
        c[i]->Divide(2,1);
    }
    
    for(int i=0;i<1;i++) //8
    {
        c[i]->cd(1)->SetTopMargin(0.06);
        c[i]->cd(1)->SetLeftMargin(0.18);
        c[i]->cd(1)->SetRightMargin(0.043);
        c[i]->cd(1)->SetBottomMargin(0.145);
        c[i]->cd(2)->SetTopMargin(0.06);
        c[i]->cd(2)->SetLeftMargin(0.18);
        c[i]->cd(2)->SetRightMargin(0.043);
        c[i]->cd(2)->SetBottomMargin(0.145);

    }
    
    //TCanvas* c2 = new TCanvas("c2","c2",100,100);
    
    TLatex* tex = new TLatex;
    tex->SetNDC();
    tex->SetTextFont(42);
    tex->SetTextSize(0.045);
    tex->SetLineWidth(2);
 
    TLatex* texCMS = new TLatex;
    texCMS->SetNDC();
    texCMS->SetTextFont(42);
    texCMS->SetTextSize(0.05);
    texCMS->SetTextAlign(12);
    
    TH1D* hist = new TH1D("hist","",10,2.4,3.6);
    hist->SetLineWidth(0);
    //hist->GetYaxis()->SetRangeUser(0,0.3);
    hist->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
    hist->GetYaxis()->SetTitle("v_{2}^{S+B}");
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetTitleOffset(1.3);
    hist->GetYaxis()->SetTitleOffset(2);
    hist->GetXaxis()->SetLabelOffset(0.007);
    hist->GetYaxis()->SetLabelOffset(0.007);
    hist->GetXaxis()->SetTitleSize(0.045);
    hist->GetYaxis()->SetTitleSize(0.045);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.04);
    hist->GetYaxis()->SetLabelSize(0.04);
    hist->SetMinimum(-0.01);
    hist->SetMaximum(0.03);
    
    //c2->cd();
    //hist->Draw();
    
    for(int i=0;i<1;i++) //8
    {
   cout << "test" << endl;
        //TH1D* h_mc_match_signal = (TH1D*)file_mass->Get(Form("hMC_mass_small_pt%d",i));
        //TH1D* h_mc_match_all = (TH1D*)file_mass->Get(Form("hMC_mass_all_small_pt%d",i));
        
        //TH1D* h_data = (TH1D*)file_mass->Get(Form("hmass_pt%d_dca0",i));
        TH1D* h_data = (TH1D*)file_mass->Get(Form("histDir/hJpsiMass_mult1"));

        h_data->SetTitle("");
        h_data->SetMinimum(0);
        h_data->SetMarkerSize(1.0);
        h_data->SetMarkerStyle(20);
        h_data->SetLineWidth(1);
        h_data->SetOption("e");
        h_data->GetXaxis()->SetRangeUser(2.4,3.6);
        h_data->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
        h_data->GetYaxis()->SetTitle("Events / (0.02 GeV)");
        h_data->GetXaxis()->CenterTitle();
        h_data->GetYaxis()->CenterTitle();
        h_data->GetXaxis()->SetTitleOffset(1.3);
        h_data->GetYaxis()->SetTitleOffset(2);
        h_data->GetXaxis()->SetLabelOffset(0.007);
        h_data->GetYaxis()->SetLabelOffset(0.007);
        h_data->GetXaxis()->SetTitleSize(0.045);
        h_data->GetYaxis()->SetTitleSize(0.045);
        h_data->GetXaxis()->SetTitleFont(42);
        h_data->GetYaxis()->SetTitleFont(42);
        h_data->GetXaxis()->SetLabelFont(42);
        h_data->GetYaxis()->SetLabelFont(42);
        h_data->GetXaxis()->SetLabelSize(0.04);
        h_data->GetYaxis()->SetLabelSize(0.04);
        
        h_data->GetXaxis()->SetNoExponent(true);
        ((TGaxis*)h_data->GetXaxis())->SetMaxDigits(7);
        
        h_data->SetMaximum(h_data->GetMaximum()*1.5);
        
        //TH1D* h_pt = (TH1D*)file_v2->Get(Form("PtD0_pt%d",i));
        //TH1D* h_KET = (TH1D*)file_v2->Get(Form("KETD0_pt%d",i));
        //pt[i] = h_pt->GetMean();
        //KET_ncq[i] = h_KET->GetMean()/2.0;

        c[i]->cd(1);
        gPad->SetTicks(-1);
        //The full fitting function is constructed as follow
        // [0] is signal + swap yield;
        // [1] is common mean of double gaussian;
        // [2] is signal gaussian 1 sigma;
        // [3] is signal gaussian 2 sigma;
        // [4] is fractional signal gaussian 1 yield; 1-[4] is fractional signal gaussian 2 yield;
        // [5] is fractional double gaussian signal yield, 1-[5] is fractional swap yield;
        // [6] is a factor to let width of the gaussians to vary in data;
        // [7] is swap gaussian sigma;
        // [8] is swap gaussian mean;
        // [9-12] is 3rd order poly parameters
         
        
        //TF1* f = new TF1(Form("f_%d",i),"[0]*([5]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 +[6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+(1-[5])*TMath::Gaus(x,[8],[7]*(1.0 +[6]))/(sqrt(2*3.14159)*[7]*(1.0 +[6]))) + [9] + [10]*x + [11]*x*x + [12]*x*x*x", fit_range_low, fit_range_high);
        TF1* f = new TF1(Form("f_%d",i),"[0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) + [5]*TMath::Exp([6] + x*[7])", fit_range_low, fit_range_high);
        f->SetLineColor(2);
        f->SetLineWidth(1);

        //first fit MC signal, swap and poly bkg set to 0
        
        f->SetParameter(0,10.);
        f->SetParameter(1,4.0);
        f->SetParameter(2,1.0);
        f->SetParameter(3,0.03);
        f->SetParameter(4,jpsi_mass);

        f->FixParameter(4,jpsi_mass);        

        f->SetParameter(5,100);
        f->SetParameter(6,0.5);
        f->SetParameter(7,-0.1);

        f->SetParLimits(1,0.01,5.0);
        f->SetParLimits(2,0.01,5.0);


//        f->FixParameter(5,1);
//        f->FixParameter(6,0); //always 0 in MC
//        f->FixParameter(7,0.1); //does not really mater here as yield is fix to 0
//        f->FixParameter(8,jpsi_mass); //does not really mater here as yield is fix to 0
//        f->FixParameter(7,0);
//        f->FixParameter(8,0);
//        f->FixParameter(9,0);
//        f->FixParameter(10,0);
        
        ///f->SetParLimits(2,0.01,0.1);
        ///f->SetParLimits(3,0.001,0.05);
        ///f->SetParLimits(4,0,1);
        ///f->SetParLimits(5,0,1);
        
//        f->FixParameter(1,3.096916); //for first few attempt fix mean of gaussian to get reasonable estimation of other pars; later open it up
        //h_mc_match_signal->Fit(Form("f_%d",i),"q","",fit_range_low,fit_range_high);
        //h_mc_match_signal->Fit(Form("f_%d",i),"q","",fit_range_low,fit_range_high);
//        f->ReleaseParameter(1); //now let gaussian mean float
        //h_mc_match_signal->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        //h_mc_match_signal->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        //h_mc_match_signal->Fit(Form("f_%d",i),"L m","",fit_range_low,fit_range_high);
        
        //now fix signal double gaussian mean, sigma and gaus1,gaus2 yield ratio
//        f->FixParameter(1,f->GetParameter(1));
//        f->FixParameter(2,f->GetParameter(2));
//        f->FixParameter(3,f->GetParameter(3));
//        f->FixParameter(4,f->GetParameter(4));
        
        //now release swap bkg parameters to fit signal+swap MC
//        f->ReleaseParameter(5);
//        f->ReleaseParameter(7);
//        f->ReleaseParameter(8);
        
//        f->SetParameter(7,0.1);
//        f->SetParameter(8,jpsi_mass);
        
        //fit signal+swap MC
        //h_mc_match_all->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        //h_mc_match_all->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        //h_mc_match_all->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        //h_mc_match_all->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        //h_mc_match_all->Fit(Form("f_%d",i),"L m","",fit_range_low,fit_range_high);
        
        //now fix swap bkg parameters to fit data
//        f->FixParameter(5,f->GetParameter(5));
//        f->FixParameter(7,f->GetParameter(7));
//        f->FixParameter(8,f->GetParameter(8));
        
        //now release poly bkg pars
//        f->ReleaseParameter(9);
//        f->ReleaseParameter(10);
//        f->ReleaseParameter(11);
//        f->ReleaseParameter(12);
        
        //now fit data
//        h_data->Fit(Form("f_%d",i),"q","",fit_range_low,fit_range_high);
//        h_data->Fit(Form("f_%d",i),"q","",fit_range_low,fit_range_high);
//        f->ReleaseParameter(1); //allow data to have different mass peak mean than MC
//        f->ReleaseParameter(6); //allow data to have different peak width than MC
//        f->SetParameter(6,0);
//        f->SetParLimits(6,-1,1);
        //f->FixParameter(5,1);
//        h_data->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
//        h_data->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        h_data->Fit(Form("f_%d",i),"L q","",fit_range_low,fit_range_high);
        h_data->Fit(Form("f_%d",i),"L m","",fit_range_low,fit_range_high);


 
        //draw D0 signal separately
//        TF1* f1 = new TF1(Form("f_sig_%d",i),"[0]*([5]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 +[6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6]))))", fit_range_low, fit_range_high);
        TF1* f1 = new TF1(Form("f_sig_%d",i),"[0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4])", fit_range_low, fit_range_high);
        f1->SetLineColor(kOrange-3);
        f1->SetLineWidth(1);
        f1->SetLineStyle(2);
        f1->SetFillColorAlpha(kOrange-3,0.3);
        f1->SetFillStyle(1001);
        f1->FixParameter(0,f->GetParameter(0));
        f1->FixParameter(1,f->GetParameter(1));
        f1->FixParameter(2,f->GetParameter(2));
        f1->FixParameter(3,f->GetParameter(3));
        f1->FixParameter(4,f->GetParameter(4));
        //f1->FixParameter(5,f->GetParameter(5));
        //f1->FixParameter(6,f->GetParameter(6));
        
        fmasssig[i] = (TF1*)f1->Clone();
        fmasssig[i]->SetName(Form("masssigfcn_pt%d",i));
        fmasssig[i]->Write();
        
        f1->Draw("LSAME");
        

        //draw poly bkg separately
        //TF1* f3 = new TF1(Form("f_bkg_%d",i),"[9] + [10]*x + [11]*x*x + [12]*x*x*x+0*[0]*[1]*[2]*[3]*[4]*[5]*[6]*[7]*[8]", fit_range_low, fit_range_high);
        TF1* f3 = new TF1(Form("f_bkg_%d",i),"[5]*TMath::Exp([6] + x*[7]) +0*[0]*[1]*[2]*[3]*[4]", fit_range_low, fit_range_high);
        f3->SetLineColor(4);
        f3->SetLineWidth(1);
        f3->SetLineStyle(2);
        //f3->FixParameter(4,f->GetParameter(4));
        f3->FixParameter(5,f->GetParameter(5));
        f3->FixParameter(6,f->GetParameter(6));
        f3->FixParameter(7,f->GetParameter(7));
        
        fmassbkg[i] = (TF1*)f3->Clone();
        fmassbkg[i]->SetName(Form("massbkgfcn_pt%d",i));
        fmassbkg[i]->Write();
        
        f3->Draw("LSAME");

        
        tex->DrawLatex(0.22,0.86,"100 #leq N_{trk}^{offline}");
        tex->DrawLatex(0.22,0.80,Form("%.1f < p_{T} < %.1f GeV/c",ptbin[i],ptbin[i+1]));
        tex->DrawLatex(0.22,0.74,"1.4 < |y| < 2.4");
        
        texCMS->DrawLatex(.18,.97,"#font[61]{CMS} #it{Preliminary}");
        texCMS->DrawLatex(0.62,0.97, "#scale[0.8]{pp #sqrt{s} = 13 TeV}");
        
        TLegend* leg = new TLegend(0.67,0.68,0.83,0.92,NULL,"brNDC");
        leg->SetBorderSize(0);
        leg->SetTextSize(0.045);
        leg->SetTextFont(42);
        leg->SetFillStyle(0);
        leg->AddEntry(h_data,"Data","pl");
        leg->AddEntry(f,"Fit","L");
        leg->AddEntry(f1,"J/#psi Signal","f");
        //leg->AddEntry(f2,"K-#pi swap","f");
        leg->AddEntry(f3,"Background","l");
        leg->Draw("SAME");
        
        //sigfrac[i] = (f1->Integral(3.067,3.127) + f2->Integral(3.067,3.127))/f->Integral(3.067,3.127);
        sigfrac[i] = (f1->Integral(3.067,3.127) + 0)/f->Integral(3.067,3.127);

        cout<<"sigfrac[i] = "<<sigfrac[i]<<endl;


 
        //fit vn
        //[13] is vn_sig
        //[14-15] is vn bkg, const + linear vn(pT)
        //TGraphErrors* vn_data = (TGraphErrors*)file_v2->Get(Form("g_v2_DCA_pt%d_dca0",i));
        TGraphErrors* vn_data = (TGraphErrors*)file_v2->Get(Form("gFlowpT18-30"));
        ///###change error of v2###///        
        for(int k=0;k<vn_data->GetN();k++){
          vn_data->SetPointError(k,0,vn_data->GetErrorY(k)*200); //Check the error of v2
        }

        c[i]->cd(2);
        gPad->SetTicks(-1);
        
        hist->Draw();
        
        TF1* fmass_combinemassvnfit = new TF1(Form("fmass_combinemassvnfit_%d",i),"[0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) + [5]*TMath::Exp([6] + x*[7])", fit_range_low, fit_range_high);
        //v2^(S+B) = alpha*v2^S + (1-alpha)*v2^B
        TF1* fvn_combinemassvnfit = new TF1(Form("fvn_combinemassvnfit_%d",i), "( ( [0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) ) / ( [0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) + [5]*TMath::Exp([6] + x*[7]) ) ) * [8] + ( 1.0 - ( ( [0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) ) / ( [0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) + [5]*TMath::Exp([6] + x*[7]) ) ) ) * ( [9]*TMath::Exp([10] + x*[11]) )", fit_range_low, fit_range_high);
        
        fmass_combinemassvnfit->SetLineColor(2);
        fmass_combinemassvnfit->SetLineWidth(1);
        
        fvn_combinemassvnfit->SetLineColor(2);
        fvn_combinemassvnfit->SetLineWidth(1);

        ROOT::Math::WrappedMultiTF1 wfmass_combinemassvnfit(*fmass_combinemassvnfit,1);
        ROOT::Math::WrappedMultiTF1 wfvn_combinemassvnfit(*fvn_combinemassvnfit,1);
        
        ROOT::Fit::DataOptions opt;
        ROOT::Fit::DataRange range_massfit;

        range_massfit.SetRange(fit_range_low,fit_range_high);
        ROOT::Fit::BinData datamass(opt,range_massfit);
        ROOT::Fit::FillData(datamass, h_data);
        
        ROOT::Fit::DataRange range_vnfit;
        range_vnfit.SetRange(fit_range_low,fit_range_high);
        ROOT::Fit::BinData datavn(opt,range_vnfit);
        ROOT::Fit::FillData(datavn, vn_data);
        
        ROOT::Fit::Chi2Function chi2_B(datamass, wfmass_combinemassvnfit);
        ROOT::Fit::Chi2Function chi2_SB(datavn, wfvn_combinemassvnfit);
        
        GlobalChi2_poly3bkg_floatwidth globalChi2(chi2_B, chi2_SB);

        ROOT::Fit::Fitter fitter;
        
        const int Npar = 12;//16
        double par0[Npar];
        for( int ipar = 0; ipar < f->GetNpar(); ipar++ ) par0[ipar] = f->GetParameter(ipar);
        par0[8] = 0.05;
        par0[9] = 0.10;
        par0[10] = 0.05;
        par0[11] = 0.02;
        
        
        fitter.Config().SetParamsSettings(Npar,par0);
        // fix parameter
        fitter.Config().ParSettings(1).Fix();
        fitter.Config().ParSettings(2).Fix();
        fitter.Config().ParSettings(3).Fix();
        fitter.Config().ParSettings(4).Fix();
        fitter.Config().ParSettings(5).Fix();
        fitter.Config().ParSettings(6).Fix();
        fitter.Config().ParSettings(7).Fix();
        //fitter.Config().ParSettings(8).Fix();

        //fitter.Config().ParSettings(1).SetLimits(3.0, 3.2);

        fitter.Config().MinimizerOptions().SetPrintLevel(0);
        fitter.Config().SetMinimizer("Minuit2","Migrad");

        fitter.FitFCN(Npar,globalChi2,0,datamass.Size()+datavn.Size(),true);
        ROOT::Fit::FitResult result = fitter.Result();
        result.Print(std::cout);
        
        fmass_combinemassvnfit->SetFitResult( result, iparmassfit_poly3bkg_floatwidth);
        fmass_combinemassvnfit->SetRange(range_massfit().first, range_massfit().second);
        fmass_combinemassvnfit->SetLineColor(kRed);
        h_data->GetListOfFunctions()->Add(fmass_combinemassvnfit);
        
        fvn_combinemassvnfit->SetFitResult( result, iparvnfit_poly3bkg_floatwidth);
        fvn_combinemassvnfit->SetRange(range_vnfit().first, range_vnfit().second);
        fvn_combinemassvnfit->SetLineColor(2);
        //fvn_combinemassvnfit->SetLineStyle(2);
        //vn_data->GetListOfFunctions()->Add(fvn_combinemassvnfit);
        vn_data->SetTitle("");
        vn_data->SetMarkerSize(1.);
        vn_data->SetMarkerStyle(20);
        vn_data->SetMarkerColor(1);
        vn_data->SetLineWidth(1);
        vn_data->Draw("PESAME z");
        
        fvn[i] = (TF1*)fvn_combinemassvnfit->Clone();
        fvn[i]->SetName(Form("vnfit_pt%d",i));
        fvn[i]->Draw("same");
        fvn[i]->Write();
        
        fmasstotal[i] = (TF1*)fmass_combinemassvnfit->Clone();
        fmasstotal[i]->SetName(Form("masstotalfcn_pt%d",i));
        fmasstotal[i]->Write();
        
        tex->DrawLatex(0.22,0.86,"100 #leq N_{trk}^{offline}");
        tex->DrawLatex(0.22,0.80,Form("%.1f < p_{T} < %.1f GeV/c",ptbin[i],ptbin[i+1]));
        tex->DrawLatex(0.22,0.74,"1.4 < |y| < 2.4");
        //tex->DrawLatex(0.22,0.68,"|#Delta#eta| > 2");

        
        texCMS->DrawLatex(.18,.97,"#font[61]{CMS} #it{Preliminary}");
        texCMS->DrawLatex(0.62,0.97, "#scale[0.8]{pp #sqrt{s} = 13 TeV}");
        
        v2[i] = fvn_combinemassvnfit->GetParameter(8);
        v2e[i] = fvn_combinemassvnfit->GetParError(8);
        v2_bkg[i] = fvn_combinemassvnfit->GetParameter(9)*TMath::Exp(fvn_combinemassvnfit->GetParameter(10) + fvn_combinemassvnfit->GetParameter(11) * 3.096916); 
        v2_ncq[i] = v2[i]/2.0;
        v2e_ncq[i] = v2e[i]/2.0;
        a[i] = fvn_combinemassvnfit->GetParameter(9);
        b[i] = fvn_combinemassvnfit->GetParameter(10);
        
        TF1* fvnbkg = new TF1(Form("fvnbkg_%d",1),"( [0]*TMath::Exp([1] + x*[2]) )", fit_range_low, fit_range_high);
        fvnbkg->FixParameter(0,fvn_combinemassvnfit->GetParameter(9));
        fvnbkg->FixParameter(1,fvn_combinemassvnfit->GetParameter(10));
        fvnbkg->FixParameter(2,fvn_combinemassvnfit->GetParameter(11));
        
        fvnbkg->SetName(Form("fvnbkg_fcn_pt%d",i));
        fvnbkg->Write();
        
        fvnbkg->SetLineStyle(7);
        //fvnbkg->Draw("LSAME");
        
        TLegend* leg1 = new TLegend(0.67,0.78,0.83,0.9,NULL,"brNDC");
        leg1->SetBorderSize(0);
        leg1->SetTextSize(0.045);
        leg1->SetTextFont(42);
        leg1->SetFillStyle(0);
        leg1->AddEntry(vn_data,"Data","pl");
        //leg1->AddEntry(fvnbkg,"v_{2}^{bkg}","L");
//        leg1->AddEntry(f1,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
//        leg1->AddEntry(f2,"K-#pi swap","f");
        leg1->AddEntry(fvn_combinemassvnfit,"Fit","l");
        leg1->Draw("SAME");

        
        //TF1* falpha = new TF1(Form("falpha_%d",1),"( [0]*([5]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 +[6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+(1-[5])*TMath::Gaus(x,[8],[7]*(1.0 +[6]))/(sqrt(2*3.14159)*[7]*(1.0 +[6]))) )/( [0]*([5]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 +[6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+(1-[5])*TMath::Gaus(x,[8],[7]*(1.0 +[6]))/(sqrt(2*3.14159)*[7]*(1.0 +[6]))) + [9] + [10]*x + [11]*x*x + [12]*x*x*x )", fit_range_low,fit_range_high);
        TF1* falpha = new TF1(Form("falpha_%d",i), "( [0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) ) / ( [0]*ROOT::Math::crystalball_function(x, [1], [2], [3], [4]) + [5]*TMath::Exp([6] + x*[7]) )", fit_range_low, fit_range_high);

        
        for(int j=0;j<8;j++)
        {
            falpha->FixParameter(j,fmass_combinemassvnfit->GetParameter(j));
        }
        
        falpha->SetName(Form("sigfrac_fcn_pt%d",i));
        falpha->Write();
        
        double xmass[200];
        double pullmass[200];
        
        float Chi2=0;
        int ndf = 1.2/0.02 - 8; //double check for jpsi
        
        for(int k=0;k<h_data->GetNbinsX();k++)
        {
            xmass[k] = h_data->GetBinCenter(k);
            pullmass[k] = (h_data->GetBinContent(k) - fmass_combinemassvnfit->Eval(xmass[k]))/h_data->GetBinError(k);
            if(fabs(pullmass[k])<5)
            {
                //cout<<pullmass[k]<<endl;
                Chi2 += pullmass[k]*pullmass[k];
            }
        }

        c[i]->cd(1);
        tex->DrawLatex(0.22,0.68,Form("Chi2/ndf = %.0f/%d",Chi2,ndf));
        
        double xv2[200];
        double pullv2[200];
        double v2y[200];
        
        float Chi2v2=0;
        int ndfv2 = 11 - 2; //double check for jpsi
        

        for(int k=0;k<vn_data->GetN();k++)
        {
            vn_data->GetPoint(k,xv2[k],v2y[k]);
            //xv2[k] = vn_dara->GetBinCenter(k);
            pullv2[k] = (v2y[k] - fvn_combinemassvnfit->Eval(xv2[k]))/vn_data->GetErrorY(k);
            //cout<<pullv2[k]<<endl;
            if(fabs(pullv2[k])<100)
            {
                //cout<<pullmass[k]<<endl;
                Chi2v2 += pullv2[k]*pullv2[k];
            }
        }

        c[i]->cd(2);
        tex->DrawLatex(0.22,0.68,Form("Chi2/ndf = %.0f/%d",Chi2v2,ndfv2));
        
    }

    
    for(int i=0;i<1;i++)//8
    {
     //   c[i]->Print(Form("plots/jpsi_mass_vnfit_combine_pt%d.pdf",i));
        c[i]->Print(Form("plot_jpsi_mass_vnfit_combine_pt%d.png",i));
        c[i]->Print(Form("plot_jpsi_mass_vnfit_combine_pt%d.pdf",i));
        c[i]->Print(Form("plot_jpsi_mass_vnfit_combine_pt%d.C",i));
    }

    for(int ipt=0; ipt<1; ipt++){ //8
       pt[ipt] = (ptbin[ipt]+ptbin[ipt+1])/2.0;
    }
    
    TGraphErrors* v2plot = new TGraphErrors(1,pt,v2,0,v2e); //8
    //TGraphErrors* v2ncqplot = new TGraphErrors(9,KET_ncq,v2_ncq,0,v2e_ncq);
    //TGraphErrors* v2bkgplot = new TGraphErrors(9,pt,v2_bkg,0,0);
    
    v2plot->SetName("v2vspt");
    //v2ncqplot->SetName("v2vsKET_ncq");
    //v2bkgplot->SetName("v2bkgvspt");
    
    v2plot->Write();



    /*
    v2ncqplot->Write();
    v2bkgplot->Write();
    */
}
