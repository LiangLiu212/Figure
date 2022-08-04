/*
 * =====================================================================================
 *
 *       Filename:  PlotBase.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2022 11:46:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#ifndef PLOT_BASE_H
#define PLOT_BASE_H
#include "TCanvas.h"
#include "TH1D.h"
#include "TROOT.h"
#include "TSystem.h"
class PlotBase {
	public:
		PlotBase();
		~PlotBase();
		virtual void plot2x2(TCanvas *c1, TH1D *h1[4]);
		virtual void plot2x1(TCanvas *c1, TH1D *h1[2]);
		virtual void plot3x3(TCanvas *c1, TH1D *h1[9]);
		virtual void plot3x2(TCanvas *c1, TH1D *h1[6]);
		virtual void plot3x1(TCanvas *c1, TH1D *h1[3]);
		virtual void plot4x4(TCanvas *c1, TH1D *h1[16]);
		virtual void plot4x3(TCanvas *c1, TH1D *h1[12]);
		virtual void plot4x2(TCanvas *c1, TH1D *h1[8]);
		virtual void plot4x1(TCanvas *c1, TH1D *h1[4]);
		virtual void formatComparePlot(TCanvas *can, TH1D *h1, TH1D *h2, const TString str);
	private:

	protected:
};

#endif
