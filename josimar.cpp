#include<iostream>
#include"cga.h"
#include<fstream>
#include<string>

using namespace std;

int main(void)
{
	float a=0.0;
	float b=0.0;
	string function="./schaffers_f6.exe";
//	for(;a<=1;a+=0.1)
//		for(;b<=1;b+=0.1)
			cout<<cga(function,-10.0,10.0,20,100,a,b,1);
//double cga(char function[100],float V_MIN, float V_MAX, int T_POB, int N_GEN, float P_MUT, float P_CRU, float T_CRU)

	return 0;
}
