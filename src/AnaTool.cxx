/*
 * =====================================================================================
 *
 *       Filename:  AnaTool.cxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2022 11:29:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Liu Liang (LL), liangzy@mail.ustc.edu.cn
 *   Organization:  USTC
 *
 * =====================================================================================
 */

#include "AnaTool.h"
void progress_bar(int i, int N){
	int step = N/100;
	int idx = i/step;
	char buf[51] = {0};
	for(int j = 0; j < 50; j++){
		buf[j]=' ';
	}
	if(i%step == 0 && idx <= 100){
		for(int j = 0; j < idx/2; j++){
			buf[j]='#';
		}
		printf("[%s][%d%%]\r", buf, idx);
		fflush(stdout);
	}
	if(idx == 100 && i%step == 0){
		printf("\n");
	}
}
