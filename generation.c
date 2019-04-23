#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include "headers.h"
#define random(x) (rand()%x)
#define N 50
#define lchrom 7
#define LEN sizeof(struct Geti)
#define pcross 0.85

double objfunc(double outflow[], double shice);
//void swmm_process(struct Gene geti);
void swmm_process(struct Gene geti, char* f1, char* f2, char* f3);
FILE  *fp1, *fp2;
struct Gene
{
	double canshu[12];
	double shiyingdu;
};
void generation(struct Gene geti[], double min[], double max[], double outflow[], double var, char* f1, char* f2, char* f3)
{
	char msg[100];
	FILE *fp;
	srand((int)time(0));
	struct Gene fubei[N];
	unsigned int i, j, k, m, l, n, g, h;
	double b, c, d, e;
	for (i = 0, h = 0, k = 0, c = geti[i].shiyingdu; i < N; i++)//记录适应度里最大值
	{
		fubei[i] = geti[i];
		b = geti[i].shiyingdu;
		if (b>c)
		{
			c = b;
			h = i;
		}
	}
	for (i = 0; i < N; i = i + 2)//用位运算进行交叉
	{
		e = random(10000) / 10000.0;
		if (e < pcross)
		{
			for (j = 0; j < 12; j++)
			{
				k = (int)((fubei[i].canshu[j] - min[j]) / (max[j] - min[j])*(pow(2, lchrom) - 1));
				m = (int)((fubei[i + 1].canshu[j] - min[j]) / (max[j] - min[j])*(pow(2, lchrom) - 1));
				n = k;
				g = m;
				l = random(lchrom);//确定交叉位置
				n = (n >> l);
				n = ((n << l) & 127);
				g = ((g << (lchrom - l)) & 127);
				g = (g >> (lchrom - l));
				n = n + g;
				m = (m >> l);
				m = ((m << l) & 127);
				k = ((k << (lchrom - l)) & 127);
				k = (k >> (lchrom - l));
				m = m + k;
				k = n;
				fubei[i].canshu[j] = k / (pow(2, lchrom) - 1)*(max[j] - min[j]) + min[j];
				fubei[i + 1].canshu[j] = m / (pow(2, lchrom) - 1)*(max[j] - min[j]) + min[j];
			}
		}
		swmm_process(geti[i],f1,f2,f3);
		geti[i].shiyingdu = objfunc(outflow, var);
	}
	for (i = 0, j = 0, k = 0, m = 0, e = fubei[i].shiyingdu; i < N; i++)//记录适应度里最小值
	{

		b = fubei[i].shiyingdu;
		if (b <e)
		{
			m = i;
			e = b;
		}
	}
	if (c>e)
		fubei[m] = geti[h];//将父辈最大值替换子倍最小


}
