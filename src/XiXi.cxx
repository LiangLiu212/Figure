/*
 * =====================================================================================
 *
 *       Filename:  XiXi.cxx
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  06/10/2022 11:22:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "XiXi.h"

XiXi::XiXi(){
	cout << "Hello World!" << endl;
}
XiXi::~XiXi(){
	cout << "End XiXi!" << endl;
}

void XiXi::setyear(const TString str){
	m_year = str;
}
void XiXi::setversion(const TString str){
	m_version = str;
}
void XiXi::setsample(const TString str){
	m_sample = str;
}
void XiXi::setchannel(const TString str){
	m_channel = str;
}

TString XiXi::year() const {
	return m_year;
}

TString XiXi::version() const {
	return m_version;
}

TString XiXi::sample() const {
	return m_sample;
}
TString XiXi::channel() const {
	return m_channel;
}
