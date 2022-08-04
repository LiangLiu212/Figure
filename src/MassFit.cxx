/*
 * =====================================================================================
 *
 *       Filename:  MassFit.cxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2022 11:19:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "MassFit.h"

MassFit::MassFit(){
	cout << "====== Start MassFit() ======" << endl;
}

MassFit::~MassFit(){
	cout << "====== End MassFit() ======" << endl;
}

void MassFit::Fit(){
	RooRealVar mn("mn", "M_{n} (GeV/c^{2})",0.90,0.985);
	RooDataSet signal("signal", "signal", mn);
	RooDataSet data("data", "data", mn);
	RooDataSet bkg("bkg", "bkg", mn);

	const TString XiXiArea = getenv("XiXiArea");
	TString infile = XiXiArea + "/files/files/" + m_year + "/" + m_channel+ "/" + m_version + "/data/histogram.root";
	TFile *f1 = new TFile(infile, "read");
	TTree *t1 = (TTree*)f1->Get("massfit");
	double m_mn, m_angle_gam1, m_angle_gam2;
	t1->SetBranchAddress("mn", &m_mn);
	t1->SetBranchAddress("angle_gam1", &m_angle_gam1);
	t1->SetBranchAddress("angle_gam2", &m_angle_gam2);
	for(int i = 0; i < t1->GetEntries(); i++){
		t1->GetEntry(i);
		mn = m_mn;
		data.add(mn);
	}

	infile  = XiXiArea + "/files/files/" + m_year + "/" + m_channel+ "/" + m_version + "/mdiy/histogram.root";
	TFile *f2 = new TFile(infile, "read");
	TTree *t2 = (TTree*)f2->Get("massfit");
	int yield = 0;

	t2->SetBranchAddress("mn", &m_mn);
	t2->SetBranchAddress("angle_gam1", &m_angle_gam1);
	t2->SetBranchAddress("angle_gam2", &m_angle_gam2);
	for(int i = 0; i < t2->GetEntries(); i++){
		t2->GetEntry(i);
		if(m_angle_gam1 < 0.3 && m_angle_gam2 < 0.3){
			mn = m_mn;
			signal.add(mn);
			yield++;
		}
		else {
			mn = m_mn;
			bkg.add(mn);
		}
	}

	cout << "kernel estimation p.d.f of background......" << endl;
//	RooKeysPdf keysbkg("keysbkg", "keysbkg", mn, bkg, RooKeysPdf::MirrorLeft, 1);
	cout << "kernel estimation p.d.f of signal......" << endl;
	RooKeysPdf keysshape("keysshape", "keysshape", mn, signal, RooKeysPdf::MirrorLeft, 3);




        RooRealVar mean2("mean2", "mean2", 0.001, -0.05, 0.05);
        RooRealVar sigma2("sigma2", "sigma2",0.001, 0, 0.05);
        RooGaussian ga1("ga1", "ga1", mn, mean2, sigma2);
        mn.setBins(10000, "cache");
        RooFFTConvPdf shape("shape", "shape", mn, keysshape, ga1);


        RooRealVar p0("p0", "poly 0", 0.5, -50., 50.);
        RooRealVar p1("p1", "poly 1", 0.5, -50., 50.);
        RooRealVar p2("p2", "poly 2", -1.5, -10., 10.);
        RooRealVar p3("p3", "poly 3", 0.5, -50., 50.);
        RooRealVar p4("p4", "poly 4", 0, -900000., 900000.);
        RooRealVar m01("m01", "m01", 0.981);
        RooRealVar k1("k1", "k1", -5, -50, -0.0);
        RooRealVar pp1("pp1", "pp1", 0.5, 0, 10);
        RooArgusBG argus1("argus1", "argus1", mn, m01, k1);
        RooRealVar mean3("mean3", "mean3", 0.935, 0, 2);
        RooRealVar sigma3("sigma3", "sigma3",0.2, 0, 50);
        RooGaussian ga3("ga3", "ga3", mn, mean3, sigma3);

        RooArgusPoly argus3("argus3", "argus3", mn, m01, k1, pp1, p0, p1, p2, p3);

        RooRealVar fra1("fra1", "fra1", 1000000, 0, 20000000);
        RooRealVar fra2("fra2", "fra2", 160000, 0, 20000000);
        RooAddPdf sum("sum", "sig+bak", RooArgList(shape, argus3), RooArgList(fra1, fra2));
//#define bkg
#ifndef bkg

        RooFitResult *resbkg = argus3.fitTo(bkg);
        k1.setConstant(kTRUE);
        pp1.setConstant(kTRUE);
        p0.setConstant(kTRUE);
        p1.setConstant(kTRUE);
        p2.setConstant(kTRUE);
        p3.setConstant(kTRUE);
        TCanvas *cbkg = new TCanvas("bkg", "bkg", 800, 600);
        RooPlot *bkgframe = mn.frame(Title("Mass Fit p.d.f."));
        bkg.plotOn(bkgframe);
        argus3.plotOn(bkgframe);
	cbkg->cd();
	bkgframe->Draw();
	TString outfile = XiXiArea + "/files/files/" + m_year + "/" + m_channel+ "/" + m_version + "/plot/modelbkg.eps";;
	cbkg->SaveAs(outfile);
#endif
	RooFitResult *res = sum.fitTo(data, "r", Extended(), Save(1));
	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
        c1->cd();
        RooPlot *xframe = mn.frame(Title("Mass Fit p.d.f."));
        data.plotOn(xframe);
        sum.plotOn(xframe, LineColor(4));
        sum.plotOn(xframe, Components("shape"), LineColor(2), LineStyle(2));
        sum.plotOn(xframe, Components("argus3"), LineColor(6), LineStyle(3));
        xframe->Draw();
	outfile = XiXiArea + "/files/files/" + m_year + "/" + m_channel+ "/" + m_version + "/plot/massfit.eps";;
	c1->SaveAs(outfile);
	cout << yield << endl;

}
