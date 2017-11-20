#include<iostream>
#include<math.h>

using namespace std;

double schaffer(double x1, double x2)
{
   	double power=pow(x1,2)+pow(x2,2);
	double a=pow(sin(sqrt(power)),2)-0.5;
	double b=pow(1.0+0.001*(power),2);
	return 0.5-(a/b);
}
