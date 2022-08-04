/*
 * =====================================================================================
 *
 *       Filename:  main.cxx
 *
 *    Description:  plot all figure for XIXI memo
 *
 *        Version:  1.0
 *        Created:  06/10/2022 10:53:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "XiXi.h"
#include "TRint.h"
#include <cstdlib>
#include <getopt.h>
#include "Angle.h"
#include "RealData.h"
#include "MassFit.h"
#include "TApplication.h"
#include <iostream>
using namespace std;
static int verbose_flag;
int main(int argc, char** argv){
	int c;
	TString m_infile[10];
	TString m_outfile[10];
	std::vector<TString> m_plotArg;
	m_plotArg.clear();
	Int_t 	m_type;
	TString m_path;
	TString m_channel;
	TString m_year;
	TString m_version;
	TString m_sample;
	int m_command;
	int 	m_idx = 0;
	const TString XiXiArea = getenv("XiXiArea");
	//TApplication app("app", &argc, argv);
	
	while(1){
		static struct option long_options[] = {
			/* These options set a flag. */
			{"compare", no_argument, 0, 0},
			{"massfit", no_argument, 0, 1},
			/* These options don’t set a flag.
			 * We distinguish them by their indices. */
			{"version", required_argument, 0, 'v'},
			{"sample", required_argument, 0, 's'},
			{"channel", required_argument, 0, 'c'},
			{"year", required_argument, 0, 'y'},
			{0, 0, 0, 0}

		};
		/* getopt_long stores the option index here. */
		int option_index = 0;
		c = getopt_long (argc, argv, "v:s:c:y:",
				long_options, &option_index);
		/* Detect the end of the options. */
		if (c == -1)
			break;
		switch (c)
		{
			case 'y': 
                                m_year = optarg;
                                if(m_year.CompareTo("2009") && m_year.CompareTo("2012") && m_year.CompareTo("2018") && m_year.CompareTo("2019")){
                                        exit(1);
                                }
                                break;
                        case 'v':
                                m_version = optarg;
                                break;
                        case 's':
                                m_sample =  optarg;
                                break;
                        case 'c':
                                m_channel = optarg;
                                break;
                        case 0:
                                m_command = 0;
                                break;
                        case 1:
                                m_command = 1;
                                break;
			case '?':
				cout << "???" << endl;
				break;
			default:
				abort();

		}
	}
	if (verbose_flag)
		puts ("verbose flag is set");
	if (optind < argc){
		printf ("non-option ARGV-elements: ");
                while (optind < argc)
                        printf ("%s ", argv[optind++]);
                putchar ('\n');
        }
	cout << "OK : " << m_command << endl;
	switch(m_command){
		case 0:{
			       cout << "Hello world!" << endl;
			       cout << "======== execute " << argv[0] << endl;
			       cout << "======== case : " << 0 << endl;
			       RealData *real = new RealData();
			       real->setyear(m_year);
			       real->setversion(m_version);
			       real->setchannel(m_channel);
			       real->FillData();
			       real->FillmDIY();
			       real->Plot();
			      // app.Run();
			       delete real;
			       break;
		       }
		case 1:{
			       cout << "Hello world!" << endl;
			       cout << "======== execute " << argv[0] << endl;
			       cout << "======== case : " << 1 << endl;
			       MassFit *mf = new MassFit();
			       mf->setyear(m_year);
			       mf->setversion(m_version);
			       mf->setchannel(m_channel);
			       mf->Fit();
			      // app.Run();
			       delete mf;
			       break;
		       }
	}
	return 0;
}

