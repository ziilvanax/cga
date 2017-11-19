/*ISRAEL CHAPARRO
Practica: Algoritmo Genetico Canonico
Catedratico: Yvan Jesus Tupac Valdivia
MAIS102-UNJBG*/

//#include <iostream.h>

#define V_PI	3.141592
#define L_CRO	62
#define	V_MIN	10
#define V_MAX	60

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

double funcion(double x1,double x2);

// estructura del individuo
class ind
{
	public:
		unsigned int cro[L_CRO]; //cromosoma
		double x1,x2,fit,fit_nor,fit_ac; //valores x1 y x2 de f(x1,x2), fit=aptitud y fit_nor=aptitud normalizada, fit_ac=aptitud acumulada para la selección por ruleta
	public:
		double read_x(int var);
		void read_cro();
		void inicializacion();
		void mutacion(float P_MUT);
		void evaluacion();
		void normalizacion();
};

void ind::mutacion(float P_MUT)
{
	float ale=(float)rand()/RAND_MAX;
	if(ale<P_MUT)
	{
		int pos=rand()%L_CRO;
		if(cro[pos]==0)
			cro[pos]=1;
		else
			cro[pos]=0;
	}
}

double ind::read_x(int var) //var=1 si x1 y var=2 si x2
{
	var--; //artificio
   	int left=-100,right=100;
	double x,a;
	double sum=0;
	for(int i=0+(var*31);i<L_CRO/2+(var*31);i++) //artificio para seleccionar la 1ra mitad si var=0 y 2da mitad si var=1
	{
		sum+=pow(2,i-(var*31))*cro[i];
	}
	a=(right-left)/(pow(2,L_CRO/2)-1);
	x=left+sum*a;
	return x;
}

void ind::read_cro() //funcion para verificacion en pruebas - no se utiliza
{
	for(int i=0;i<L_CRO;i++)
		cout<<cro[i];
}

void ind::inicializacion()
{
	for(int i=0;i<L_CRO;i++)
		cro[i]=rand()%2;
}

void ind::evaluacion()
{
	x1=read_x(1);
	x2=read_x(2);
	fit=funcion(x1,x2);
}

/*
	//t=0
	//inicializar Gt
	//decodificar Gt->Xt y evaluar Xt
	//aplicar normalizacion lineal
	mientras t<MaxGEN hacer
		t=t+1
		seleccionar Gt de Gt-1
		guardar bbest=gbest € Gt-1
		operar gt, formando Gt //cruce mutacion
		aplicar elitismo bbest->Gt
		evaluar Gt
		ajustar aptitud
	fin mientras

	selecion: ruleta y elitismo
	aptitud: normalizacion lineal con valores min max definidos

	--parte de experimentos omitida

*/

void cruce(ind &padre,ind &madre, int T_CRU);

int main(void)
{
	int t,T_POB,N_GEN,N_EXP;
	float T_CRU,ale;

	cout<<"Tamano Poblacion: ";
	cin>>T_POB;
	cout<<"Numero Generaciones: ";
	cin>>N_GEN;
	cout<<"Numero Experimentos: ";
//	cin>>N_EXP;
//	cout<<"Probabilidad Mutacion: ";
//	cin>>P_MUT;
//	cout<<"Probabilidad Cruce: ";
//	cin>>P_CRU;
//	cout<<"Tipo de Cruce: 1=un punto, 2=dos puntos, 3=uniforme: ";
//	cin>>T_CRU;
	T_CRU=2;

	ind pob[T_POB],ind_aux,best;
	ind new_pob[T_POB];

	srand(time(NULL));

	//double cap_ant;
	//t=0;

	for(float P_CRU=0.0;P_CRU<1.009;P_CRU+=0.01)
	{

		for(float P_MUT=0.0;P_MUT<1.0009;P_MUT+=0.01)
		{

			///////t=0
			t=0;

			///////inicializacion
			for(int i=0;i<T_POB;i++)
				pob[i].inicializacion();

			///////decodificacion y evaluacion
			for(int i=0;i<T_POB;i++)
				pob[i].evaluacion();

			///////normalizacion lineal
			for(int i=1;i<T_POB;i++) //ordenamiento burbuja
				for(int j=0;j<T_POB-i;j++)
					if(pob[j].fit>pob[j+1].fit)
					{
						ind_aux=pob[j];
						pob[j]=pob[j+1];
						pob[j+1]=ind_aux;
					}

			for(int i=0;i<T_POB;i++)
			{

				pob[i].fit_nor=(float)(V_MIN+(((float)(V_MAX-V_MIN)/(T_POB-1))*i));
			}

			///////mientras t<maxgen
			while(t<N_GEN)
			{
			///////t=t+1
				t++;
				///////seleccionar gt de gt-1
				//pob[0].fit_ac=pob[0].fit; //trabajando con aptitud no normalizada
				pob[0].fit_ac=pob[0].fit_nor; //trabajando con aptitud normalizada
				for(int i=1;i<T_POB;i++)
				{
					//pob[i].fit_ac=pob[i-1].fit_ac+pob[i].fit; //trabajando con aptitud no normalizada
					pob[i].fit_ac=pob[i-1].fit_ac+pob[i].fit_nor; //trabajando con aptitud normalizada
				}
				for(int i=1;i<T_POB;i++) //selecion por ruleta
				{
					int j;
					ale=(float)rand()*pob[T_POB-1].fit_ac/RAND_MAX;
					for(j=0;pob[j].fit_ac<ale&&j<T_POB;j++);
					new_pob[i]=pob[j];
				}
				///////guardar bbest=gbestgt-1
				best=pob[0];
				for(int i=1;i<T_POB;i++)
					if(best.fit<pob[i].fit)
						best=pob[i];

				///////operar gt formando gt
				for(int i=1;i<T_POB;i++)
					pob[i]=new_pob[i];

				int selec[T_POB],cant=-1;

				///////cruce
				for(int i=1;i<T_POB;i++)
				{
					ale=(float)rand()/RAND_MAX;
					if(ale<P_CRU)
					{
						cant++;
						selec[cant]=i;
					}
				}
				if(cant%2) //para asegurar las parejas
					cant--;
				for(int i=0;i<cant/2+1;i++)
					cruce(pob[i],pob[cant/2+1+i],T_CRU);

				///////mutacion
				for(int i=1;i<T_POB;i++)
					pob[i].mutacion(P_MUT);

				///////aplicar elitismo bbest->gt
				pob[0]=best;

				///////decodificacion y evaluacion
				for(int i=0;i<T_POB;i++)
					pob[i].evaluacion();

				///////normalizacion lineal
				for(int i=1;i<T_POB;i++) //ordenamiento burbuja
					for(int j=0;j<T_POB-i;j++)
						if(pob[j].fit>pob[j+1].fit)
						{
							ind_aux=pob[j];
							pob[j]=pob[j+1];
							pob[j+1]=ind_aux;
						}
				for(int i=0;i<T_POB;i++)
					pob[i].fit_nor=(float)(V_MIN+(((float)(V_MAX-V_MIN)/(T_POB-1))*i));
			}
			cout<<P_MUT<<";"<<P_CRU<<";"<<best.fit<<endl;

		}
	}

	return 0;
}

void cruce(ind &padre,ind &madre,int T_CRU)
{
	unsigned int aux;

	if(T_CRU!=3) //cruce de 1 y 2 puntos se parecen
	{
		int punt1;
		punt1=rand()%(L_CRO-1);
		if(T_CRU==1) //cruce de 1 punto
		{
			for(int i=punt1+1;i<L_CRO;i++)
			{
				aux=padre.cro[i];
				padre.cro[i]=madre.cro[i];
				madre.cro[i]=aux;
			}
		}
		else //cruce de 2 puntos
		{
			int punt2;
			punt2=rand()%(L_CRO-1);
			while(punt1==punt2) //mientras los puntos sean iguales, calcular de nuevo
				punt2=rand()%(L_CRO-1);
			if(punt1>punt2)
			{
				aux=punt1;
				punt1=punt2;
				punt2=aux;
			}
			for(int i=punt1+1;i<punt2+1;i++)
			{
				aux=padre.cro[i];
				padre.cro[i]=madre.cro[i];
				madre.cro[i]=aux;
			}
		}
	}
	else //cruce uniforme
	{
		float prob;
		for(int i=0;i<L_CRO;i++)
		{
			if(padre.cro[i]!=madre.cro[i]) //si son iguales, ahorrar calculo
			{
				prob=(float)rand()/RAND_MAX;
				if(prob<0.5)
				{
					aux=padre.cro[i];
					padre.cro[i]=madre.cro[i];
					madre.cro[i]=aux;
				}
			}
		}
	}
}

//calculo de funcion, F6 de Schaffer's
double funcion(double x1,double x2)
{
	double a,b;
	a=pow(sin(sqrt(pow(x1,2)+pow(x2,2))),2)-0.5;
	b=pow(1+0.001*(pow(x1,2)+pow(x2,2)),2);
	return 0.5-(a/b);
}

