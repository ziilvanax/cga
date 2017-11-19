#include<iostream>
#include<math.h>

using namespace std;

int main(int argc,char **argv)
{
	if(argc==1)
		cout<<"\n\n\tWelcome to Schaffer F6, Use: "<<argv[0]<<" [x1] [x2] ...\n\n";
	else
	{
	    double *x = new double[argc];
	    cout<<"schaffer ";
	    for(int i=1;i<argc;i++)
	    {
	    	x[i-1]=strtod(argv[i],NULL);
			cout<<x[i-1]<<" ";
		}
	    double power=0;
	    for(int i=0;i<argc-1;i++)
	    	power+=pow(x[i],2);
		double a=pow(sin(sqrt(power)),argc-1)-0.5;
		double b=pow(1.0+0.001*(power),argc-1);
		double c=0.5-(a/b);
		printf("%9.7f",c);
		return 0;
	}
}
