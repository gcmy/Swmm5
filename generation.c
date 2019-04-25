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
	for (i = 0; i < N; i++)   //��geti��ֵ������fubei
	{
		fubei[i] = geti[i];
	}
	for (i = 0; i < N; i = i + 2)//��λ������н���,dui geti���н�������
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
				l = random(lchrom);//ȷ������λ��
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
				geti[i].canshu[j] = k / (pow(2, lchrom) - 1)*(max[j] - min[j]) + min[j];
				geti[i + 1].canshu[j] = m / (pow(2, lchrom) - 1)*(max[j] - min[j]) + min[j];
			}
		}
		swmm_process(geti[i],f1,f2,f3);     //�������ɵ�geti��������У�����µ���Ӧ��
		geti[i].shiyingdu = objfunc(outflow, var);
		swmm_close();
		swmm_process(geti[i + 1], f1, f2, f3);
		geti[i+1].shiyingdu = objfunc(outflow, var);
		swmm_close();
	}
	for (i = 0; i < N; i++)    //�������ɵ�geti��ǰһ����fubei���жԱȣ����fubei���ţ��ͽ�fubei����geti���Ӷ������µ�һ��
	{
		if (geti[i].shiyingdu < fubei[i].shiyingdu)
		geti[i] = fubei[i];
	
	}
	


}
