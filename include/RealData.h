/*
 * =====================================================================================
 *
 *       Filename:  RealData.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/2022 19:52:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#ifndef REAL_DATA_H
#define REAL_DATA_H

#include "XiXi.h"
#include "PlotBase.h"
#include "TH2D.h"
#include "TBox.h"
#include "TLine.h"
class RealData : public XiXi, public PlotBase {
	public:
		RealData();
		~RealData();
		virtual void FillData();
		virtual void FillmDIY();
		virtual void FillHist(TH1D *h[40], TString sample);
		virtual void Plot();
		virtual void initialHist(TString str);
		virtual void initialHist2D(TString str);
		virtual void formatPlot2D(TCanvas *c1);

	private:
		TH1D *h[2][40];
		TH2D *h2d[2][10];
		TLorentzVector p4Xi1, p4Xi2, p4lambda1, p4lambda2;
		TLorentzVector p4pion1_1, p4pion1_2, p4pion2_1, p4pion0;
		TLorentzVector p4neutron, p4proton, p4gam1, p4gam2;
		double Xi1[4], Xi2[4], lambda1[4];
		double lambda_decayL, Xi_decayL, lambda_chi2, Xi_chi2, chi2, mn;
		double lambda2[4], proton[4], neutron[4], pion1_1[4];
		double pion1_2[4], pion2_1[4], pion0[4], gam1[4], gam2[4];
		double angle_lamgam1, angle_lamgam2, angle_gam1, angle_gam2;
		double m_mn, m_angle_gam1, m_angle_gam2;
		int i_type;

};
#endif
