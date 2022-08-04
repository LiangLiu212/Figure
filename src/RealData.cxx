/*
 * =====================================================================================
 *
 *       Filename:  RealData.cxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/2022 19:55:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "RealData.h"
#include "TROOT.h"
#include "TSystem.h"
using namespace std;
RealData::RealData(){
	cout << "start RealData() " << endl;
	gROOT->ProcessLine(".L ~/.rootlogon.C");
}

RealData::~RealData(){
	cout << "End RealData()" << endl;
}

void RealData::FillData(){
	i_type = 0;
	FillHist(h[0], "data");
}

void RealData::FillmDIY(){
	i_type = 1;
	FillHist(h[1], "mdiy");
}

void RealData::initialHist(TString str){
	TString name[38] = {"lambdadecaylength","xidecaylength", 
	"mXi1", "mXi2", "mlambda1", "XiCosTheta", "mn",
	"anglelamgam1", "anglelamgam2", "Xichi2", "Lambdachi2",
	"chi2", 
	"PtXi1", "PtXi2", "PtLambda1", "PtLambda2", "PtProton", "Ptneutron",
	"Ptpion1_1", "Ptpion1_2", "Ptpion2_1", "Ptpion0", "Ptgam1", "Ptgam2",
	"CostXi1", "CostXi2", "CostLambda1", "CostLambda2", "CostProton", "Costneutron",
	"Costpion1_1", "Costpion1_2", "Costpion2_1", "Costpion0", "Costgam1", "Costgam2",
	"mnmatch", "mnunmatch"
	};
	double low[38] = {-20, -20, 1.32171 - 0.033, 1.32171 - 0.033,
		1.115683 - 0.033, -1, 0.90, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		0.90, 0.90
	};
	double high[38] = { 40, 40, 1.32171 + 0.033, 1.32171 + 0.033,
		1.115683 + 0.033, 1, 0.985, TMath::Pi(), TMath::Pi(),
		200, 200, 200, 
		0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0.985, 0.985
	};
	cout << str << endl;
	int type;
	if(!str.CompareTo("data")){
		type = 0;
	}
	else if(!str.CompareTo("mdiy")){
		type = 1;
	}
	for(int i = 0; i < 38; i++){
		name[i] = str + name[i];
		h[type][i] = new TH1D(name[i], name[i], 100, low[i], high[i]); // lambda decay length
	}
}

void RealData::Plot(){
	TString xaxis[36] = {"#Lambda decay length (cm)",
		"#Xi decay length (cm)",
		"M(#Xi 1) GeV/#font[52]{c}^{2}","M(#Xi 2) GeV/#font[52]{c}^{2}",
		"M(#Lambda) GeV/#font[52]{c}^{2}",
		"cos #theta (#Xi)",
		"M(n) GeV/#font[52]{c}^{2}",
		"Angle (#Lambda #gamma 1) rad",
		"Angle (#Lambda #gamma 2) rad",
		"#chi^{2} #Xi Secondary Vertex Fit",
		"#chi^{2} #Lambda Secondary Vertex Fit",
		"#chi^{2} Kinematic Fit",
		"Pt #Xi 1 GeV/#font[4]{c}",
		"Pt #Xi 2 GeV/#font[4]{c}",
		"Pt #Lambda 1 GeV/#font[4]{c}",
		"Pt #Lambda 2 GeV/#font[4]{c}",
		"Pt p 1 GeV/#font[4]{c}",
		"Pt n 2 GeV/#font[4]{c}",
		"Pt #pi 1 GeV/#font[4]{c}",
		"Pt #pi 2 GeV/#font[4]{c}",
		"Pt #pi 3 GeV/#font[4]{c}",
		"P #pi^{0} 2 GeV/#font[4]{c}",
		"E #gamma 1 GeV/#font[4]{c}^{2}",
		"E #gamma 2 GeV/#font[4]{c}^{2}",
		"cos#theta #Xi 1 ",
		"cos#theta #Xi 2 ",
		"cos#theta #Lambda 1 ",
		"cos#theta #Lambda 2 ",
		"cos#theta p 1 ",
		"cos#theta n 2 ",
		"cos#theta #pi 1 ",
		"cos#theta #pi 2 ",
		"cos#theta #pi 3 ",
		"cos#theta #pi^{0} 2 ",
		"cos#theta #gamma 1 ",
		"cos#theta #gamma 2 "
	};
	TCanvas *can[36];
	const TString XiXiArea = getenv("XiXiArea");
	TString outfile = XiXiArea + "/files/files/" + m_year + "/" + m_channel + "/" + m_version + "/plot/"; 
	gSystem->Exec(("mkdir -p " + outfile).Data());
	for(int i = 0; i < 36; i++){
		TString c_name = Form("can%d", i+1);
		TString s_outfile = outfile + c_name + ".eps";
		cout << outfile << endl;
		can[i] = new TCanvas(c_name, c_name, 800, 600);
		formatComparePlot(can[i], h[0][i], h[1][i], xaxis[i]);
		can[i]->SaveAs(s_outfile);
	}
}

void RealData::FillHist(TH1D *h[40], TString sample){
	const TString XiXiArea = getenv("XiXiArea");
	TString infile = XiXiArea + "/files/files/" + m_year + "/" + m_channel + "/" + m_version + "/" + sample + "/skimfile.root"; 
	initialHist(sample);
	initialHist2D(sample);
	cout << infile << endl;
	TFile *f1 = new TFile(infile, "read");
	TTree *t1 = (TTree*)f1->Get("xixi");
	t1->SetBranchAddress("Xi1", Xi1);
	t1->SetBranchAddress("Xi2", Xi2);
	t1->SetBranchAddress("lambda1", lambda1);
	t1->SetBranchAddress("lambda2", lambda2);
	t1->SetBranchAddress("pion1_1", pion1_1);
	t1->SetBranchAddress("pion1_2", pion1_2);
	t1->SetBranchAddress("pion2_1", pion2_1);
	t1->SetBranchAddress("pion0", pion0);
	t1->SetBranchAddress("neutron", neutron);
	t1->SetBranchAddress("proton", proton);
	t1->SetBranchAddress("gam1", gam1);
	t1->SetBranchAddress("gam2", gam2);

	t1->SetBranchAddress("lambda_decayL", &lambda_decayL);
	t1->SetBranchAddress("Xi_decayL", &Xi_decayL);
	t1->SetBranchAddress("lambda_chi2", &lambda_chi2);
	t1->SetBranchAddress("Xi_chi2", &Xi_chi2);
	t1->SetBranchAddress("chi2", &chi2);
	t1->SetBranchAddress("mn", &mn);
	t1->SetBranchAddress("angle_lamgam1", &angle_lamgam1);
	t1->SetBranchAddress("angle_lamgam2", &angle_lamgam2);
	t1->SetBranchAddress("angle_gam1", &angle_gam1);
	t1->SetBranchAddress("angle_gam2", &angle_gam2);
	
	TString outfile = XiXiArea + "/files/files/" + m_year + "/" + m_channel + "/" + m_version + "/" + sample + "/histogram.root"; 
	cout << outfile << endl;
	TFile *outf1 = new TFile(outfile, "recreate");
	TTree *outtree = new TTree("massfit", "neutron mass fit");
	outtree->Branch("mn", &m_mn, "mn/D");
	outtree->Branch("angle_gam1", &m_angle_gam1, "angle_gam1/D");
	outtree->Branch("angle_gam2", &m_angle_gam2, "angle_gam2/D");

	for(int i = 0; i < t1->GetEntries(); i++){
		t1->GetEntry(i);
		progress_bar(i, t1->GetEntries());
		p4Xi1.SetPxPyPzE(Xi1[1], Xi1[2], Xi1[3], Xi1[0]);
		p4Xi2.SetPxPyPzE(Xi2[1], Xi2[2], Xi2[3], Xi2[0]);
		p4lambda1.SetPxPyPzE(lambda1[1], lambda1[2], lambda1[3], lambda1[0]);
		p4lambda2.SetPxPyPzE(lambda2[1], lambda2[2], lambda2[3], lambda2[0]);

		p4proton.SetPxPyPzE(proton[1], proton[2], proton[3], proton[0]);
		p4neutron.SetPxPyPzE(neutron[1], neutron[2], neutron[3], neutron[0]);
		p4pion1_1.SetPxPyPzE(pion1_1[1], pion1_1[2], pion1_1[3], pion1_1[0]);
		p4pion1_2.SetPxPyPzE(pion1_2[1], pion1_2[2], pion1_2[3], pion1_2[0]);
		p4pion2_1.SetPxPyPzE(pion2_1[1], pion2_1[2], pion2_1[3], pion2_1[0]);
		p4pion0.SetPxPyPzE(pion0[1], pion0[2], pion0[3], pion0[0]);

		p4gam1.SetPxPyPzE(gam1[1], gam1[2], gam1[3], gam1[0]);
		p4gam2.SetPxPyPzE(gam2[1], gam2[2], gam2[3], gam2[0]);


		if(fabs(p4Xi1.M() - 1.32171) < 0.011 && fabs(p4Xi2.M() - 1.32171) < 0.011 && fabs(p4lambda1.M() - 1.115683) < 0.011 && lambda_chi2 < 500
				&& Xi_chi2 < 500 && chi2 < 200){
				h[0]->Fill(lambda_decayL);
				h[1]->Fill(Xi_decayL);
		}
		if(fabs(p4Xi1.M() - 1.32171) < 0.055 && fabs(p4Xi2.M() - 1.32171) < 0.055 && fabs(p4lambda1.M() - 1.115683) < 0.011 && lambda_chi2 < 500
				&& Xi_chi2 < 500 && chi2 < 200 && lambda_decayL > 0 && Xi_decayL > 0){
			h2d[i_type][0]->Fill(p4Xi1.M(), p4Xi2.M());
		}
		if(fabs(p4Xi1.M() - 1.32171) < 0.011 && fabs(p4Xi2.M() - 1.32171) < 0.011 && fabs(p4lambda1.M() - 1.115683) < 0.011 && lambda_chi2 < 500
				&& Xi_chi2 < 500 && chi2 < 200 && lambda_decayL > 0 && Xi_decayL > 0){
				h[5]->Fill(p4Xi1.CosTheta());
				h[6]->Fill(mn);
				h[7]->Fill(angle_lamgam1);
				h[8]->Fill(angle_lamgam2);
				h[9]->Fill(Xi_chi2);
				h[10]->Fill(lambda_chi2);
				h[11]->Fill(chi2);
				h[12]->Fill(p4Xi1.Pt());
				h[13]->Fill(p4Xi2.Pt());
				h[14]->Fill(p4lambda1.Pt());
				h[15]->Fill(p4lambda2.Pt());
				h[16]->Fill(p4proton.Pt());
				h[17]->Fill(p4neutron.Pt());
				h[18]->Fill(p4pion1_1.Pt());
				h[19]->Fill(p4pion1_2.Pt());
				h[20]->Fill(p4pion2_1.Pt());
				h[21]->Fill(p4pion0.Rho());
				h[22]->Fill(p4gam1.E());
				h[23]->Fill(p4gam2.E());
				h[24]->Fill(p4Xi1.CosTheta());
				h[25]->Fill(p4Xi2.CosTheta());
				h[26]->Fill(p4lambda1.CosTheta());
				h[27]->Fill(p4lambda2.CosTheta());
				h[28]->Fill(p4proton.CosTheta());
				h[29]->Fill(p4neutron.CosTheta());
				h[30]->Fill(p4pion1_1.CosTheta());
				h[31]->Fill(p4pion1_2.CosTheta());
				h[32]->Fill(p4pion2_1.CosTheta());
				h[33]->Fill(p4pion0.CosTheta());
				h[34]->Fill(p4gam1.CosTheta());
				h[35]->Fill(p4gam2.CosTheta());
				if(!sample.CompareTo("mdiy")){
					if(angle_gam1 < 0.3 && angle_gam2 < 0.3){
						h[36]->Fill(mn);
					}
					else {
						h[37]->Fill(mn);
					}
				}
				else {
						h[36]->Fill(mn);
						h[37]->Fill(mn);
				}
				m_mn = mn;
				m_angle_gam1 = angle_gam1;
				m_angle_gam2 = angle_gam2;
				outtree->Fill();
		}
		if(fabs(p4Xi1.M() - 1.32171) < 0.011 && fabs(p4Xi2.M() - 1.32171) < 0.011 && lambda_chi2 < 500 && Xi_chi2 < 500 && chi2 < 200 && lambda_decayL > 0 && Xi_decayL > 0){
			h[4]->Fill(p4lambda1.M());
		}
		if(fabs(p4Xi1.M() - 1.32171) < 0.011 && fabs(p4lambda1.M() - 1.115683) < 0.011 && lambda_chi2 < 500 && Xi_chi2 < 500 && chi2 < 200 && lambda_decayL > 0 && Xi_decayL > 0){
			h[3]->Fill(p4Xi2.M());
		}
		if(fabs(p4lambda1.M() - 1.115683) < 0.011 && fabs(p4Xi2.M() - 1.32171) < 0.011 && lambda_chi2 < 500 && Xi_chi2 < 500 && chi2 < 200 && lambda_decayL > 0 && Xi_decayL > 0){
			h[2]->Fill(p4Xi1.M());
		}
	}

	for(int i = 0; i < 38; i++){
		h[i]->Write();
	}
	h2d[i_type][0]->Write();
	TCanvas *c1 = new TCanvas(sample, sample, 800, 600);
	formatPlot2D(c1);
	TString outXimass = XiXiArea + "/files/files/" + m_year + "/" + m_channel + "/" + m_version + "/" + "plot/xi2dmass"+ sample +".eps";
	c1->SaveAs(outXimass);
	outtree->Write();
	outf1->Close();
}

void RealData::initialHist2D(TString str){
	TString name[1] = {
		"XiXimass"
	};
	double low1[1] = { 1.32171 - 0.055 };
	double low2[1] = {1.32171 - 0.055};
	double high1[1] = {1.32171 + 0.055};
	double high2[1] = {1.32171 + 0.055};
	int type;
	if(!str.CompareTo("data")){
		type = 0;
	}
	else if(!str.CompareTo("mdiy")){
		type = 1;
	}
	h2d[type][0] = new TH2D(name[0], name[0], 100, low1[0], high1[0],
			100, low2[0], high2[0]);

}

void RealData::formatPlot2D(TCanvas *c1){
	c1->cd();
	h2d[i_type][0]->Draw();
	h2d[i_type][0]->SetTitle("; M(#Xi) GeV/#font[52]{c}^{2}; M(#bar{#Xi}) GeV/#font[52]{c}^{2}");
	double x1 = 1.32171 - 0.038;
	double x2 = 1.32171 - 0.016;
	double x3 = 1.32171 - 0.011;
	double x4 = 1.32171 + 0.011;
	double x5 = 1.32171 + 0.016;
	double x6 = 1.32171 + 0.038;
	TBox *b0  = new TBox(x3, x3, x4, x4);
	b0->SetLineColor(2);
	b0->SetFillStyle(0);
	b0->Draw();

	TBox *b1  = new TBox(x1, x1, x2, x2);
	b1->SetLineColor(4);
	b1->SetFillStyle(0);
	b1->Draw();

	TBox *b2  = new TBox(x1, x5, x2, x6);
	b2->SetLineColor(4);
	b2->SetFillStyle(0);
	b2->Draw();

	TBox *b3  = new TBox(x5, x1, x6, x2);
	b3->SetLineColor(4);
	b3->SetFillStyle(0);
	b3->Draw();

	TBox *b4  = new TBox(x5, x5, x6, x6);
	b4->SetLineColor(4);
	b4->SetFillStyle(0);
	b4->Draw();

}
