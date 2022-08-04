/*
 * =====================================================================================
 *
 *       Filename:  MassFit.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2022 11:15:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#ifndef MASS_FIT_H
#define MASS_FIT_H

#include "XiXi.h"
#include "PlotBase.h"
#include "RooArgusPoly.h"
#include "RooRealVar.h"
#include "RooAbsReal.h"
#include "RooProduct.h"
#include "RooFormulaVar.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooChebychev.h"
#include "RooGaussian.h"
#include "RooHistPdf.h"
#include "RooDataSet.h"
#include "RooKeysPdf.h"
#include "RooFFTConvPdf.h"
#include "RooArgusBG.h"
#include "RooArgusGauss.h"
#include "RooCmdArg.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooFit.h"
#include "RooArgusPoly.h"
#include "RooEffProd.h"
#include "RooDataHist.h"
using namespace RooFit;
class MassFit : public XiXi, public PlotBase {
	public:
		MassFit();
		~MassFit();
		virtual void Fit();
	private:

};

#endif 
