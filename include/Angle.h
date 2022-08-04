/*
 * =====================================================================================
 *
 *       Filename:  Angle.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2022 11:41:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */
#ifndef ANGLE_H
#define ANGLE_H

#include "XiXi.h"
#include "PlotBase.h"

class Angle : public XiXi, public PlotBase {
	public:
		Angle();
		~Angle();
		void Draw();
		virtual void plot2x2(TCanvas *c1, TH1D *h1[4], TH1D *h2[4]);
		virtual void plot2x2(TCanvas *c1, TH1D *h1[3][4]);
};
#endif
