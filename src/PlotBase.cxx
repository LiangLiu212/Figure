/*
 * =====================================================================================
 *
 *       Filename:  PlotBase.cxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2022 11:50:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "PlotBase.h"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;
PlotBase::PlotBase(){
	cout << "Plot base" << endl;
	gROOT->ProcessLine(".L ~/.rootlogon.C");
}
PlotBase::~PlotBase(){
	cout << "Plot base" << endl;
}

void PlotBase::plot2x1(TCanvas *c1, TH1D *h1[2]){
	for(int i = 0; i < 2; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}


void PlotBase::plot2x2(TCanvas *c1, TH1D *h1[4]){
	for(int i = 0; i < 4; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}

void PlotBase::plot3x1(TCanvas *c1, TH1D *h1[3]){
	for(int i = 0; i < 3; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}
void PlotBase::plot3x2(TCanvas *c1, TH1D *h1[6]){
	for(int i = 0; i < 6; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}

void PlotBase::plot3x3(TCanvas *c1, TH1D *h1[9]){
	for(int i = 0; i < 9; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}
void PlotBase::plot4x1(TCanvas *c1, TH1D *h1[4]){
	for(int i = 0; i < 4; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}

void PlotBase::plot4x2(TCanvas *c1, TH1D *h1[8]){
	for(int i = 0; i < 8; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}


void PlotBase::plot4x3(TCanvas *c1, TH1D *h1[12]){
	for(int i = 0; i < 12; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}

void PlotBase::plot4x4(TCanvas *c1, TH1D *h1[16]){
	for(int i = 0; i < 16; i++){
		c1->cd(i+1);
		h1[i]->Draw();
	}
}


void PlotBase::formatComparePlot(TCanvas *can, TH1D *h1, TH1D *h2, const TString str){
        h2->Scale(h1->Integral()/h2->Integral());
        can->cd();
        TPad *pad1 = new TPad("pad1", "Fit part",0,0.3,1,1);
        pad1->SetBottomMargin(0);
        pad1->SetTopMargin(-1);
        pad1->Draw();
        pad1->cd();
        pad1->Range(0.05128203,0.6,2.102564,1.231579);
//      h1->SetLineColor(2);
        h1->SetMarkerStyle(20);
        h2->SetLineColor(2);
        h1->GetYaxis()->CenterTitle(true);
        h1->GetYaxis()->SetLabelFont(42);
        //      h1->GetYaxis()->SetLabelOffset(0.01);
        h1->GetYaxis()->SetLabelSize(0.07);
        h1->GetYaxis()->SetTitleSize(0.1);
        h1->GetYaxis()->SetTitleOffset(0.8);
        h1->GetYaxis()->SetTitleFont(42);
        h1->GetYaxis()->SetTitle("Events");

        h1->Draw("E");
        pad1->Update();
        h2->Draw("same hist");
        can->cd();

        h1->Sumw2();
        h2->Sumw2();
        TH1D *h3 = (TH1D*)h1->Clone("hnew") ;
        h3->Add(h1, h2, 1, -1);
        h3->Divide(h1);
        TPad *pad2 = new TPad("pad2", "Comparison part",0,0.05,1,0.3);
        pad2->Draw();
        pad2->cd();
        pad2->SetGridy();
        pad2->Range(0.05128203,-4.333333,2.102564,2.333333);
        pad2->SetBottomMargin(0.35);
	h3->SetMaximum(0.5);
	h3->SetMinimum(-0.5);
        h3->GetXaxis()->CenterTitle(true);
        h3->GetXaxis()->SetLabelFont(42);
        h3->GetXaxis()->SetLabelOffset(0.01);
        h3->GetXaxis()->SetLabelSize(0.15);
        h3->GetXaxis()->SetTitleSize(0.25);
        h3->GetXaxis()->SetTitleOffset(0.60);
        h3->GetXaxis()->SetTitleFont(42);
        h3->GetYaxis()->SetNdivisions(505);
        h3->GetYaxis()->SetLabelSize(0.16);
        h3->GetYaxis()->SetTitle("#chi");
        h3->GetXaxis()->SetTitle(str);
        h3->GetYaxis()->SetTitleSize(0.3);
        h3->GetYaxis()->SetTitleOffset(0.26);
        h3->GetYaxis()->CenterTitle(true);
        h3->Draw();
}




