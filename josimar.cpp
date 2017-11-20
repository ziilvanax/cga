#include<iostream>
//#include"cga.h"
#include"cga4cga.h"
#include<fstream>
#include<string>

using namespace std;

int main(void)
{
//	for(;a<=1;a+=0.1)
//		for(;b<=1;b+=0.1)
//			cout<<cga(function,-10.0,10.0,20,100,a,b,1);
//
	cga4cga(0,1,100,100,0.5,0.5,2);
	return 0;
}
