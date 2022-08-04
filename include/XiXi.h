/*
 * =====================================================================================
 *
 *       Filename:  XiXi.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2022 10:56:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#ifndef XIXI_H
#define XIXI_H

#include "TRandom.h"
#include "TApplication.h"
#include "TH1F.h"
#include "TString.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TVectorT.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TDirectory.h"
#include <TMinuit.h>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include "AnaTool.h"
using namespace std;

class XiXi{
	public:
		XiXi();
		~XiXi();
		virtual void setyear(const TString str);
		virtual void setversion(const TString str);
		virtual void setsample(const TString str);
		virtual void setchannel(const TString str);
		virtual TString year() const;
		virtual TString version() const;
		virtual TString sample() const;
		virtual TString channel() const;


	protected:
		TString m_year;
		TString m_version;
		TString m_sample;
		TString m_channel;
		TString m_infile;
		TString m_outfile;


};

#endif
