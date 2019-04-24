#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include "headers.h"
#define random(x) (rand()%x)
#define N 50
#define lchrom 7
#define LEN sizeof(struct Geti)
#define pmutation 0.18
double objfunc(double outflow[], double shice);
void swmm_process(struct Gene geti, char* f1, char* f2, char* f3);
struct Gene
{
	double canshu[12];
	double shiyingdu;
};
void mutation(struct Gene geti[],double min[], double max[],double outflow[],double var,  char* f1, char* f2, char* f3)
{
	FILE *fp;

	srand((int)time(0));
	struct Gene fubei[N];
	int i, j, k, m, l, n, g, h;
	double b, c, d, e;	
	//用位运算进行变异操作
	for (i = 0; i < N; i++)
	{
		fubei[i] = geti[i];
		for (j = 0; j < 12; j++)
		{		
		e  = random(10000) / 10000.0;
		if (e < pmutation)
		{
			k = (int)((fubei[i].canshu[j] - min[j]) / (max[j] - min[j])*(pow(2, lchrom) - 1));
			l = random(lchrom);
			if (l = 0)
			{
				if (k >= 64)k = k - 64;
				else k = k + 64;
			}
			else
			{
				m = (k&((int)pow(2, l-1)));
				if ((k << (lchrom - l)) & 127 >= 64)
					k = k - m;
				else k = k + m;
			}
			double a = (pow(2, lchrom) - 1);
			geti[i].canshu[j] = k / (pow(2, lchrom) - 1)*(max[j] - min[j]) + min[j];
		}
	}
		swmm_process(geti[i],f1,f2,f3);
 		geti[i].shiyingdu = objfunc(outflow, var);
		/*if (fubei[i].shiyingdu>geti[i].shiyingdu)
		geti[i] = fubei[i];*/
	}
	
}