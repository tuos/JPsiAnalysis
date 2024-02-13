#ifdef __CLING__
#pragma cling optimize(0)
#endif
void plot_jpsi_mass_vnfit_combine_pt0()
{
//=========Macro generated from canvas: c_0/c_0
//=========  (Tue Feb 13 15:55:27 2024) by ROOT version 6.26/11
   TCanvas *c_0 = new TCanvas("c_0", "c_0",0,23,800,400);
   gStyle->SetOptStat(0);
   c_0->Range(0,0,1,1);
   c_0->SetFillColor(0);
   c_0->SetBorderMode(0);
   c_0->SetBorderSize(2);
   c_0->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c_0_1
   TPad *c_0_1 = new TPad("c_0_1", "c_0_1",0.01,0.01,0.49,0.99);
   c_0_1->Draw();
   c_0_1->cd();
   c_0_1->Range(2.122008,-62.37736,3.666409,367.8113);
   c_0_1->SetFillColor(0);
   c_0_1->SetBorderMode(0);
   c_0_1->SetBorderSize(2);
   c_0_1->SetTickx(-1);
   c_0_1->SetTicky(1);
   c_0_1->SetLeftMargin(0.18);
   c_0_1->SetRightMargin(0.043);
   c_0_1->SetTopMargin(0.06);
   c_0_1->SetBottomMargin(0.145);
   c_0_1->SetFrameBorderMode(0);
   c_0_1->SetFrameBorderMode(0);
   
   TH1D *hJpsiMass_mult1__1 = new TH1D("hJpsiMass_mult1__1","",50,2.4,3.6);
   hJpsiMass_mult1__1->SetBinContent(1,189);
   hJpsiMass_mult1__1->SetBinContent(2,129);
   hJpsiMass_mult1__1->SetBinContent(3,141);
   hJpsiMass_mult1__1->SetBinContent(4,163);
   hJpsiMass_mult1__1->SetBinContent(5,133);
   hJpsiMass_mult1__1->SetBinContent(6,165);
   hJpsiMass_mult1__1->SetBinContent(7,141);
   hJpsiMass_mult1__1->SetBinContent(8,144);
   hJpsiMass_mult1__1->SetBinContent(9,130);
   hJpsiMass_mult1__1->SetBinContent(10,137);
   hJpsiMass_mult1__1->SetBinContent(11,132);
   hJpsiMass_mult1__1->SetBinContent(12,157);
   hJpsiMass_mult1__1->SetBinContent(13,128);
   hJpsiMass_mult1__1->SetBinContent(14,127);
   hJpsiMass_mult1__1->SetBinContent(15,116);
   hJpsiMass_mult1__1->SetBinContent(16,130);
   hJpsiMass_mult1__1->SetBinContent(17,124);
   hJpsiMass_mult1__1->SetBinContent(18,113);
   hJpsiMass_mult1__1->SetBinContent(19,137);
   hJpsiMass_mult1__1->SetBinContent(20,120);
   hJpsiMass_mult1__1->SetBinContent(21,143);
   hJpsiMass_mult1__1->SetBinContent(22,103);
   hJpsiMass_mult1__1->SetBinContent(23,99);
   hJpsiMass_mult1__1->SetBinContent(24,140);
   hJpsiMass_mult1__1->SetBinContent(25,137);
   hJpsiMass_mult1__1->SetBinContent(26,148);
   hJpsiMass_mult1__1->SetBinContent(27,168);
   hJpsiMass_mult1__1->SetBinContent(28,216);
   hJpsiMass_mult1__1->SetBinContent(29,226);
   hJpsiMass_mult1__1->SetBinContent(30,228);
   hJpsiMass_mult1__1->SetBinContent(31,201);
   hJpsiMass_mult1__1->SetBinContent(32,150);
   hJpsiMass_mult1__1->SetBinContent(33,149);
   hJpsiMass_mult1__1->SetBinContent(34,148);
   hJpsiMass_mult1__1->SetBinContent(35,137);
   hJpsiMass_mult1__1->SetBinContent(36,141);
   hJpsiMass_mult1__1->SetBinContent(37,130);
   hJpsiMass_mult1__1->SetBinContent(38,121);
   hJpsiMass_mult1__1->SetBinContent(39,126);
   hJpsiMass_mult1__1->SetBinContent(40,116);
   hJpsiMass_mult1__1->SetBinContent(41,131);
   hJpsiMass_mult1__1->SetBinContent(42,124);
   hJpsiMass_mult1__1->SetBinContent(43,132);
   hJpsiMass_mult1__1->SetBinContent(44,121);
   hJpsiMass_mult1__1->SetBinContent(45,134);
   hJpsiMass_mult1__1->SetBinContent(46,111);
   hJpsiMass_mult1__1->SetBinContent(47,129);
   hJpsiMass_mult1__1->SetBinContent(48,119);
   hJpsiMass_mult1__1->SetBinContent(49,130);
   hJpsiMass_mult1__1->SetBinContent(50,125);
   hJpsiMass_mult1__1->SetMinimum(0);
   hJpsiMass_mult1__1->SetMaximum(342);
   hJpsiMass_mult1__1->SetEntries(7039);
   hJpsiMass_mult1__1->SetOption("e");
   
   TF1 *f_01 = new TF1("f_0","[0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3]))) + [4] + [5]*x + [6]*x*x + [7]*x*x*x",2.4,3.6, TF1::EAddToList::kNo);
   f_01->SetFillColor(19);
   f_01->SetFillStyle(0);
   f_01->SetLineColor(2);
   f_01->SetLineWidth(1);
   f_01->SetChisquare(96.41305);
   f_01->SetNDF(43);
   f_01->GetXaxis()->SetLabelFont(42);
   f_01->GetXaxis()->SetTitleOffset(1);
   f_01->GetXaxis()->SetTitleFont(42);
   f_01->GetYaxis()->SetLabelFont(42);
   f_01->GetYaxis()->SetTitleFont(42);
   f_01->SetParameter(0,9.372403);
   f_01->SetParError(0,1.026635);
   f_01->SetParLimits(0,0,0);
   f_01->SetParameter(1,3.096916);
   f_01->SetParError(1,0);
   f_01->SetParLimits(1,3.096916,3.096916);
   f_01->SetParameter(2,0.03840709);
   f_01->SetParError(2,0.05892115);
   f_01->SetParLimits(2,0.01,0.1);
   f_01->SetParameter(3,0.002923523);
   f_01->SetParError(3,0.03841535);
   f_01->SetParLimits(3,0.001,0.05);
   f_01->SetParameter(4,0.9999999);
   f_01->SetParError(4,0.8859388);
   f_01->SetParLimits(4,0,1);
   f_01->SetParameter(5,1);
   f_01->SetParError(5,0.8667556);
   f_01->SetParLimits(5,0,1);
   f_01->SetParameter(6,48.64182);
   f_01->SetParError(6,1.208996);
   f_01->SetParLimits(6,0,0);
   f_01->SetParameter(7,-11.20543);
   f_01->SetParError(7,0.3769861);
   f_01->SetParLimits(7,0,0);
   f_01->SetParent(hJpsiMass_mult1__1);
   hJpsiMass_mult1__1->GetListOfFunctions()->Add(f_01);
   
   TF1 *fmass_combinemassvnfit_02 = new TF1("fmass_combinemassvnfit_0","[0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3]))) + [4] + [5]*x + [6]*x*x + [7]*x*x*x",2.4,3.6, TF1::EAddToList::kDefault);
   fmass_combinemassvnfit_02->SetFillColor(19);
   fmass_combinemassvnfit_02->SetFillStyle(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   fmass_combinemassvnfit_02->SetLineColor(ci);
   fmass_combinemassvnfit_02->SetLineWidth(1);
   fmass_combinemassvnfit_02->SetChisquare(170.1147);
   fmass_combinemassvnfit_02->SetNDF(58);
   fmass_combinemassvnfit_02->GetXaxis()->SetLabelFont(42);
   fmass_combinemassvnfit_02->GetXaxis()->SetTitleOffset(1);
   fmass_combinemassvnfit_02->GetXaxis()->SetTitleFont(42);
   fmass_combinemassvnfit_02->GetYaxis()->SetLabelFont(42);
   fmass_combinemassvnfit_02->GetYaxis()->SetTitleFont(42);
   fmass_combinemassvnfit_02->SetParameter(0,9.310737);
   fmass_combinemassvnfit_02->SetParError(0,0.8387596);
   fmass_combinemassvnfit_02->SetParLimits(0,0,0);
   fmass_combinemassvnfit_02->SetParameter(1,3.096916);
   fmass_combinemassvnfit_02->SetParError(1,0);
   fmass_combinemassvnfit_02->SetParLimits(1,0,0);
   fmass_combinemassvnfit_02->SetParameter(2,0.03840709);
   fmass_combinemassvnfit_02->SetParError(2,0);
   fmass_combinemassvnfit_02->SetParLimits(2,0,0);
   fmass_combinemassvnfit_02->SetParameter(3,0.002923523);
   fmass_combinemassvnfit_02->SetParError(3,0);
   fmass_combinemassvnfit_02->SetParLimits(3,0,0);
   fmass_combinemassvnfit_02->SetParameter(4,0.9999999);
   fmass_combinemassvnfit_02->SetParError(4,0);
   fmass_combinemassvnfit_02->SetParLimits(4,0,0);
   fmass_combinemassvnfit_02->SetParameter(5,1);
   fmass_combinemassvnfit_02->SetParError(5,0);
   fmass_combinemassvnfit_02->SetParLimits(5,0,0);
   fmass_combinemassvnfit_02->SetParameter(6,48.64182);
   fmass_combinemassvnfit_02->SetParError(6,0);
   fmass_combinemassvnfit_02->SetParLimits(6,0,0);
   fmass_combinemassvnfit_02->SetParameter(7,-11.20543);
   fmass_combinemassvnfit_02->SetParError(7,0);
   fmass_combinemassvnfit_02->SetParLimits(7,0,0);
   fmass_combinemassvnfit_02->SetParent(hJpsiMass_mult1__1);
   hJpsiMass_mult1__1->GetListOfFunctions()->Add(fmass_combinemassvnfit_02);

   ci = TColor::GetColor("#000099");
   hJpsiMass_mult1__1->SetLineColor(ci);
   hJpsiMass_mult1__1->SetMarkerStyle(20);
   hJpsiMass_mult1__1->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
   hJpsiMass_mult1__1->GetXaxis()->SetRange(1,50);
   hJpsiMass_mult1__1->GetXaxis()->CenterTitle(true);
   hJpsiMass_mult1__1->GetXaxis()->SetNoExponent();
   hJpsiMass_mult1__1->GetXaxis()->SetLabelFont(42);
   hJpsiMass_mult1__1->GetXaxis()->SetLabelOffset(0.007);
   hJpsiMass_mult1__1->GetXaxis()->SetLabelSize(0.04);
   hJpsiMass_mult1__1->GetXaxis()->SetTitleSize(0.045);
   hJpsiMass_mult1__1->GetXaxis()->SetTitleOffset(1.3);
   hJpsiMass_mult1__1->GetXaxis()->SetTitleFont(42);
   hJpsiMass_mult1__1->GetYaxis()->SetTitle("Events / (0.02 GeV)");
   hJpsiMass_mult1__1->GetYaxis()->CenterTitle(true);
   hJpsiMass_mult1__1->GetYaxis()->SetLabelFont(42);
   hJpsiMass_mult1__1->GetYaxis()->SetLabelOffset(0.007);
   hJpsiMass_mult1__1->GetYaxis()->SetLabelSize(0.04);
   hJpsiMass_mult1__1->GetYaxis()->SetTitleSize(0.045);
   hJpsiMass_mult1__1->GetYaxis()->SetTitleOffset(2);
   hJpsiMass_mult1__1->GetYaxis()->SetTitleFont(42);
   hJpsiMass_mult1__1->GetZaxis()->SetLabelFont(42);
   hJpsiMass_mult1__1->GetZaxis()->SetTitleOffset(1);
   hJpsiMass_mult1__1->GetZaxis()->SetTitleFont(42);
   hJpsiMass_mult1__1->Draw("");
   
   TF1 *f_sig_03 = new TF1("f_sig_0","[0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3])))",2.4,3.6, TF1::EAddToList::kDefault);

   ci = 1179;
   color = new TColor(ci, 1, 0.6, 0, " ", 0.3);
   f_sig_03->SetFillColor(ci);

   ci = TColor::GetColor("#ff9900");
   f_sig_03->SetLineColor(ci);
   f_sig_03->SetLineWidth(1);
   f_sig_03->SetLineStyle(2);
   f_sig_03->GetXaxis()->SetLabelFont(42);
   f_sig_03->GetXaxis()->SetTitleOffset(1);
   f_sig_03->GetXaxis()->SetTitleFont(42);
   f_sig_03->GetYaxis()->SetLabelFont(42);
   f_sig_03->GetYaxis()->SetTitleFont(42);
   f_sig_03->SetParameter(0,9.372403);
   f_sig_03->SetParError(0,0);
   f_sig_03->SetParLimits(0,9.372403,9.372403);
   f_sig_03->SetParameter(1,3.096916);
   f_sig_03->SetParError(1,0);
   f_sig_03->SetParLimits(1,3.096916,3.096916);
   f_sig_03->SetParameter(2,0.03840709);
   f_sig_03->SetParError(2,0);
   f_sig_03->SetParLimits(2,0.03840709,0.03840709);
   f_sig_03->SetParameter(3,0.002923523);
   f_sig_03->SetParError(3,0);
   f_sig_03->SetParLimits(3,0.002923523,0.002923523);
   f_sig_03->Draw("LSAME");
   
   TF1 *f_bkg_04 = new TF1("f_bkg_0","[4] + [5]*x + [6]*x*x + [7]*x*x*x +0*[0]*[1]*[2]*[3]",2.4,3.6, TF1::EAddToList::kDefault);
   f_bkg_04->SetFillColor(19);
   f_bkg_04->SetFillStyle(0);
   f_bkg_04->SetLineColor(4);
   f_bkg_04->SetLineWidth(1);
   f_bkg_04->SetLineStyle(2);
   f_bkg_04->GetXaxis()->SetLabelFont(42);
   f_bkg_04->GetXaxis()->SetTitleOffset(1);
   f_bkg_04->GetXaxis()->SetTitleFont(42);
   f_bkg_04->GetYaxis()->SetLabelFont(42);
   f_bkg_04->GetYaxis()->SetTitleFont(42);
   f_bkg_04->SetParameter(0,0);
   f_bkg_04->SetParError(0,0);
   f_bkg_04->SetParLimits(0,0,0);
   f_bkg_04->SetParameter(1,0);
   f_bkg_04->SetParError(1,0);
   f_bkg_04->SetParLimits(1,0,0);
   f_bkg_04->SetParameter(2,0);
   f_bkg_04->SetParError(2,0);
   f_bkg_04->SetParLimits(2,0,0);
   f_bkg_04->SetParameter(3,0);
   f_bkg_04->SetParError(3,0);
   f_bkg_04->SetParLimits(3,0,0);
   f_bkg_04->SetParameter(4,0.9999999);
   f_bkg_04->SetParError(4,0);
   f_bkg_04->SetParLimits(4,0.9999999,0.9999999);
   f_bkg_04->SetParameter(5,1);
   f_bkg_04->SetParError(5,0);
   f_bkg_04->SetParLimits(5,1,1);
   f_bkg_04->SetParameter(6,48.64182);
   f_bkg_04->SetParError(6,0);
   f_bkg_04->SetParLimits(6,48.64182,48.64182);
   f_bkg_04->SetParameter(7,-11.20543);
   f_bkg_04->SetParError(7,0);
   f_bkg_04->SetParLimits(7,-11.20543,-11.20543);
   f_bkg_04->Draw("LSAME");
   TLatex *   tex = new TLatex(0.22,0.86,"100 #leq N_{trk}^{offline}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.8,"1.8 < p_{T} < 3.0 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.74,"1.4 < |y| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.97,"#font[61]{CMS} #it{Preliminary}");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.97,"#scale[0.8]{pp #sqrt{s} = 13 TeV}");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.67,0.68,0.83,0.92,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("hJpsiMass_mult1","Data","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("f_0","Fit","L");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("f_sig_0","J/#psi Signal","f");

   ci = 1179;
   color = new TColor(ci, 1, 0.6, 0, " ", 0.3);
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff9900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("f_bkg_0","Background","l");
   entry->SetLineColor(4);
   entry->SetLineStyle(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
      tex = new TLatex(0.22,0.68,"Chi2/ndf = 95/52");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c_0_1->Modified();
   c_0->cd();
  
// ------------>Primitives in pad: c_0_2
   TPad *c_0_2 = new TPad("c_0_2", "c_0_2",0.51,0.01,0.99,0.99);
   c_0_2->Draw();
   c_0_2->cd();
   c_0_2->Range(2.122008,-0.0172956,3.666409,0.03301887);
   c_0_2->SetFillColor(0);
   c_0_2->SetBorderMode(0);
   c_0_2->SetBorderSize(2);
   c_0_2->SetTickx(-1);
   c_0_2->SetTicky(1);
   c_0_2->SetLeftMargin(0.18);
   c_0_2->SetRightMargin(0.043);
   c_0_2->SetTopMargin(0.06);
   c_0_2->SetBottomMargin(0.145);
   c_0_2->SetFrameBorderMode(0);
   c_0_2->SetFrameBorderMode(0);
   
   TH1D *hist__2 = new TH1D("hist__2","",10,2.4,3.6);
   hist__2->SetMinimum(-0.01);
   hist__2->SetMaximum(0.03);
   hist__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   hist__2->SetLineColor(ci);
   hist__2->SetLineWidth(0);
   hist__2->GetXaxis()->SetTitle("m_{#mu#mu} (GeV/c^{2})");
   hist__2->GetXaxis()->CenterTitle(true);
   hist__2->GetXaxis()->SetLabelFont(42);
   hist__2->GetXaxis()->SetLabelOffset(0.007);
   hist__2->GetXaxis()->SetLabelSize(0.04);
   hist__2->GetXaxis()->SetTitleSize(0.045);
   hist__2->GetXaxis()->SetTitleOffset(1.3);
   hist__2->GetXaxis()->SetTitleFont(42);
   hist__2->GetYaxis()->SetTitle("v_{2}^{S+B}");
   hist__2->GetYaxis()->CenterTitle(true);
   hist__2->GetYaxis()->SetLabelFont(42);
   hist__2->GetYaxis()->SetLabelOffset(0.007);
   hist__2->GetYaxis()->SetLabelSize(0.04);
   hist__2->GetYaxis()->SetTitleSize(0.045);
   hist__2->GetYaxis()->SetTitleOffset(2);
   hist__2->GetYaxis()->SetTitleFont(42);
   hist__2->GetZaxis()->SetLabelFont(42);
   hist__2->GetZaxis()->SetTitleOffset(1);
   hist__2->GetZaxis()->SetTitleFont(42);
   hist__2->Draw("");
   
   Double_t gFlowpT18-30_fx1001[12] = {
   2.45,
   2.55,
   2.65,
   2.75,
   2.85,
   2.95,
   3.05,
   3.15,
   3.25,
   3.35,
   3.45,
   3.55};
   Double_t gFlowpT18-30_fy1001[12] = {
   0.005587991,
   0.005668723,
   0.007806636,
   -0.0004787284,
   -0.01320923,
   -0.006615672,
   -0.001959191,
   0.004726317,
   -0.001012578,
   0.002794128,
   0.006224002,
   0.008156885};
   Double_t gFlowpT18-30_fex1001[12] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t gFlowpT18-30_fey1001[12] = {
   0.002168513,
   0.002205396,
   0.003087155,
   5.560894e-05,
   0.00544994,
   0.002667491,
   0.0006154116,
   0.001546529,
   0.0003964401,
   0.001136985,
   0.002450697,
   0.003247779};
   TGraphErrors *gre = new TGraphErrors(12,gFlowpT18-30_fx1001,gFlowpT18-30_fy1001,gFlowpT18-30_fex1001,gFlowpT18-30_fey1001);
   gre->SetName("gFlowpT18-30");
   gre->SetTitle("");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_gFlowpT18mI301001 = new TH1F("Graph_gFlowpT18mI301001","",100,2.4,3.6);
   Graph_gFlowpT18mI301001->SetMinimum(-0.1);
   Graph_gFlowpT18mI301001->SetMaximum(0.5);
   Graph_gFlowpT18mI301001->SetDirectory(0);
   Graph_gFlowpT18mI301001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gFlowpT18mI301001->SetLineColor(ci);
   Graph_gFlowpT18mI301001->GetXaxis()->SetTitle(" mass #mu#mu [GeV]");
   Graph_gFlowpT18mI301001->GetXaxis()->SetLabelFont(42);
   Graph_gFlowpT18mI301001->GetXaxis()->SetTitleOffset(1);
   Graph_gFlowpT18mI301001->GetXaxis()->SetTitleFont(42);
   Graph_gFlowpT18mI301001->GetYaxis()->SetTitle(" v_{2}");
   Graph_gFlowpT18mI301001->GetYaxis()->SetLabelFont(42);
   Graph_gFlowpT18mI301001->GetYaxis()->SetTitleFont(42);
   Graph_gFlowpT18mI301001->GetZaxis()->SetLabelFont(42);
   Graph_gFlowpT18mI301001->GetZaxis()->SetTitleOffset(1);
   Graph_gFlowpT18mI301001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gFlowpT18-301001);
   
   gre->Draw("pe z");
   
   TF1 *vnfit_pt05 = new TF1("vnfit_pt0","( ( [0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3]))) ) / ( [0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3]))) + [4] + [5]*x + [6]*x*x + [7]*x*x*x ) ) * [8] + ( 1.0 - ( ( [0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3]))) ) / ( [0]*(TMath::Gaus(x,[1],[2]*(1.0 +[3]))/(sqrt(2*3.14159)*[2]*(1.0 +[3]))) + [4] + [5]*x + [6]*x*x + [7]*x*x*x ) ) ) * ( [9] + [10] * x)",2.4,3.6, TF1::EAddToList::kDefault);
   vnfit_pt05->SetFillColor(19);
   vnfit_pt05->SetFillStyle(0);
   vnfit_pt05->SetLineColor(2);
   vnfit_pt05->SetLineWidth(1);
   vnfit_pt05->SetChisquare(170.1147);
   vnfit_pt05->SetNDF(58);
   vnfit_pt05->GetXaxis()->SetLabelFont(42);
   vnfit_pt05->GetXaxis()->SetTitleOffset(1);
   vnfit_pt05->GetXaxis()->SetTitleFont(42);
   vnfit_pt05->GetYaxis()->SetLabelFont(42);
   vnfit_pt05->GetYaxis()->SetTitleFont(42);
   vnfit_pt05->SetParameter(0,9.310737);
   vnfit_pt05->SetParError(0,0.8387596);
   vnfit_pt05->SetParLimits(0,0,0);
   vnfit_pt05->SetParameter(1,3.096916);
   vnfit_pt05->SetParError(1,0);
   vnfit_pt05->SetParLimits(1,0,0);
   vnfit_pt05->SetParameter(2,0.03840709);
   vnfit_pt05->SetParError(2,0);
   vnfit_pt05->SetParLimits(2,0,0);
   vnfit_pt05->SetParameter(3,0.002923523);
   vnfit_pt05->SetParError(3,0);
   vnfit_pt05->SetParLimits(3,0,0);
   vnfit_pt05->SetParameter(4,0.9999999);
   vnfit_pt05->SetParError(4,0);
   vnfit_pt05->SetParLimits(4,0,0);
   vnfit_pt05->SetParameter(5,1);
   vnfit_pt05->SetParError(5,0);
   vnfit_pt05->SetParLimits(5,0,0);
   vnfit_pt05->SetParameter(6,48.64182);
   vnfit_pt05->SetParError(6,0);
   vnfit_pt05->SetParLimits(6,0,0);
   vnfit_pt05->SetParameter(7,-11.20543);
   vnfit_pt05->SetParError(7,0);
   vnfit_pt05->SetParLimits(7,0,0);
   vnfit_pt05->SetParameter(8,-0.003551365);
   vnfit_pt05->SetParError(8,0.002446441);
   vnfit_pt05->SetParLimits(8,0,0);
   vnfit_pt05->SetParameter(9,-0.001251709);
   vnfit_pt05->SetParError(9,0.001950359);
   vnfit_pt05->SetParLimits(9,0,0);
   vnfit_pt05->SetParameter(10,0.0002838058);
   vnfit_pt05->SetParError(10,0.0007060325);
   vnfit_pt05->SetParLimits(10,0,0);
   vnfit_pt05->Draw("same");
      tex = new TLatex(0.22,0.86,"100 #leq N_{trk}^{offline}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.8,"1.8 < p_{T} < 3.0 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.22,0.74,"1.4 < |y| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.97,"#font[61]{CMS} #it{Preliminary}");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.62,0.97,"#scale[0.8]{pp #sqrt{s} = 13 TeV}");
tex->SetNDC();
   tex->SetTextAlign(12);
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.67,0.78,0.83,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("gFlowpT18-30","Data","pl");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("fvn_combinemassvnfit_0","Fit","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
      tex = new TLatex(0.22,0.68,"Chi2/ndf = 74/9");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c_0_2->Modified();
   c_0->cd();
   c_0->Modified();
   c_0->cd();
   c_0->SetSelected(c_0);
}
