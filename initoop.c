#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#define random(x) (rand()%x)
#define N 50
#define lchrom 7
double objfunc(double outflow[], double var);
void swmm_process(struct Gene geti, char* f1, char* f2, char* f3);
int i, j, k, d, e;
double b, c, leijishiyingdu = 0;//定义累计适应度变量
double dc1;
struct Gene
{
	double canshu[12];
	double shiyingdu;
};
struct Gene fubei[N];
void initpoop(struct Gene geti[], double min[], double max[], double outflow[], double var, char* f1, char* f2, char* f3)
{
	
	srand((int)time(0));

	for (i = 0; i < N; i++)//产生初代参数
	{

		for (k = 0; k < 12 ; k++)
		{
			for (j = 0, geti[i].canshu[k] = 0; j < lchrom; j++)
			{
				c = random(2);
				b = pow(2, j)*c;
				geti[i].canshu[k] += b;
			}
			geti[i].canshu[k] = geti[i].canshu[k] / (pow(2, lchrom ) - 1)*(max[k] - min[k]) + min[k];			
		}
		geti[i].shiyingdu = 0;
		swmm_process(geti[i],f1,f2,f3);

		geti[i].shiyingdu = objfunc(outflow, var);
	
	}
	
	for (i = 0; i < N; i++)
		fubei[i] = geti[i];
}
