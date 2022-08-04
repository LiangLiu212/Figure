/*
 * =====================================================================================
 *
 *       Filename:  Angle.cxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2022 12:06:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "Angle.h"
#include "TROOT.h"
using namespace std;
Angle::Angle(){
	cout << "start Angle() " << endl;
	gROOT->ProcessLine(".L ~/.rootlogon.C");
}

Angle::~Angle(){
	cout << "End Angle()" << endl;
}

void Angle::Draw(){
	const TString XiXiArea = getenv("XiXiArea");
	cout << "Draw Angle " << endl;
	TString path = "/Users/liang/Documents/XiXi/Analysis/Figure/rootfile/2019/xixipp/histv3/mdiy/mdiy30x.root";
	TFile *f1 = new TFile(path, "read");
	TH1D *h1[12];
	TH1D *h2[12];
	TH1D *h3[12];
	TH1D *h2x1[2];
	TH1D *hmn[4];
	TH1D *hmn1[4];
	TH1D *hangle[3][4];
	hmn[0]=(TH1D*)f1->Get("total/variable/mXi1");
	hmn[1]=(TH1D*)f1->Get("total/variable/mXi2");
	hmn[2]=(TH1D*)f1->Get("total/variable/mlambda1");
	hmn[3]=(TH1D*)f1->Get("total/variable/mn");
	hmn1[0]=(TH1D*)f1->Get("background/variable/mXi1");
	hmn1[1]=(TH1D*)f1->Get("background/variable/mXi2");
	hmn1[2]=(TH1D*)f1->Get("background/variable/mlambda1");
	hmn1[3]=(TH1D*)f1->Get("background/variable/mn");

	for(int i = 0; i < 12; i++){
		TString str_angle = Form("total/angle/totalcangle%d", i+1);
		h1[i] = (TH1D*)f1->Get(str_angle);
	}
	for(int i = 0; i < 12; i++){
		TString str_angle = Form("signal/angle/signalcangle%d", i+1);
		h2[i] = (TH1D*)f1->Get(str_angle);
	}
	for(int i = 0; i < 12; i++){
		TString str_angle = Form("background/angle/backgroundcangle%d", i+1);
		h3[i] = (TH1D*)f1->Get(str_angle);
	}
	for(int i = 0; i < 4; i++){
		hangle[0][i] = h1[i+2];
		hangle[1][i] = h2[i+2];
		hangle[2][i] = h3[i+2];
	}
	h1[10]->SetTitle("; #theta^{1}_{match}; Events");
	h1[10]->GetXaxis()->CenterTitle(true);
	h1[10]->GetYaxis()->CenterTitle(true);
	h1[10]->SetLineColor(2);
	h1[11]->SetTitle("; #theta^{2}_{match}; Events");
	h1[11]->GetXaxis()->CenterTitle(true);
	h1[11]->GetYaxis()->CenterTitle(true);
	h1[11]->SetLineColor(2);
	TString massname[4] = {"M(#Xi^{-}) GeV/#font[52]{c}^{2}", 
		"M(#bar{#Xi^{+}}) GeV/#font[52]{c}^{2}",
		"M(#Lambda) GeV/#font[52]{c}^{2}", 
		"M(#bar{n}) GeV/#font[52]{c}^{2}"};
	TString anglename[4] = {"#Lambda matched angle (rad)",
		"#bar{#Lambda} matched angle (rad)",
		"Proton matched angle (rad)",
		"Anti-neutron matched angle (rad)"};
	for(int i =0; i < 4; i++){
		TString title = "; " + massname[i] + "; Events"; 
		hmn[i]->SetTitle(title);
		hmn[i]->GetXaxis()->CenterTitle(true);
		hmn[i]->GetYaxis()->CenterTitle(true);
		hmn[i]->SetLineColor(2);
		hmn1[i]->SetTitle(title);
		hmn1[i]->GetXaxis()->CenterTitle(true);
		hmn1[i]->GetYaxis()->CenterTitle(true);
		hmn1[i]->SetLineColor(4);
		TString angtitle = "; " + anglename[i] + "; Events";
		hangle[0][i]->SetTitle(angtitle);
		hangle[0][i]->GetXaxis()->CenterTitle(true);
		hangle[0][i]->GetYaxis()->CenterTitle(true);
		hangle[0][i]->SetLineColor(2);
		hangle[1][i]->SetTitle(angtitle);
		hangle[1][i]->GetXaxis()->CenterTitle(true);
		hangle[1][i]->GetYaxis()->CenterTitle(true);
		hangle[1][i]->SetLineColor(6);
		hangle[2][i]->SetTitle(angtitle);
		hangle[2][i]->GetXaxis()->CenterTitle(true);
		hangle[2][i]->GetYaxis()->CenterTitle(true);
		hangle[2][i]->SetLineColor(4);
	}
	h2x1[0] = h1[10];
	h2x1[1] = h1[11];


	TCanvas *c4 = new TCanvas("can4", "can4", 1200, 675);
	c4->Divide(4,3);
	plot4x3(c4, h1);
	TCanvas *c2x1 = new TCanvas("c2x1", "c2x1", 1200, 450);
	c2x1->Divide(2,1);
	plot2x1(c2x1, h2x1);
	TString o_gamangle = XiXiArea + "/Figure/outfile/gamangle.eps";
	c2x1->SaveAs(o_gamangle);
	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
	c1->Divide(2, 2);
	plot2x2(c1, hmn, hmn1);
	TString o_mass = XiXiArea + "/Figure/outfile/recmass.eps";
	c1->SaveAs(o_mass);
	TCanvas *cang2x2 = new TCanvas("cang2x2", "cang2x2", 1200, 900);
	cang2x2->Divide(2,2);
	plot2x2(cang2x2, hangle);
	TString o_angle = XiXiArea + "/Figure/outfile/baryonangle.eps";
	cang2x2->SaveAs(o_angle);
}


void Angle::plot2x2(TCanvas *c1, TH1D *h1[4], TH1D *h2[4]){
	for(int i =0; i < 4; i++){
		c1->cd(i+1);
		h1[i]->Draw();
		c1->Update();
		h2[i]->Draw("same");
	}
}


void Angle::plot2x2(TCanvas *c1, TH1D *h1[3][4]){
	for(int i =0; i < 4; i++){
		c1->cd(i+1);
		h1[0][i]->Draw();
		c1->Update();
		h1[1][i]->Draw("same");
		c1->Update();
		h1[2][i]->Draw("same");
	}
}

