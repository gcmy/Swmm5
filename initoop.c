#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#define random(x) (rand()%x)
#define N 50
#define lchrom 7
double objfunc(double outflow[], double var);
void swmm_process(struct Gene geti);
int i, j, k, d, e;
double b, c, leijishiyingdu = 0;//�����ۼ���Ӧ�ȱ���
double dc1;
struct Gene
{
	double canshu[5];
	double shiyingdu;
};
struct Gene fubei[N];
void initpoop(struct Gene geti[], double min[], double max[], double outflow[], double var)
{
	
	srand((int)time(0));

	for (i = 0; i < N; i++)//������������
	{

		for (k = 0; k < 5 ; k++)
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
		swmm_process(geti[i]);
		dc1 = objfunc(outflow, var);
		geti[i].shiyingdu = pow(1 / (1 - dc1 ), 2);//������ѧ��ʽ��Ч��ϵ��ת��Ϊ��Ӧ�Ⱥ���
		leijishiyingdu += geti[i].shiyingdu;
	}
	for (i = 0; i < N; i++)//���ð�������Ӧ�ȷ���ѡȡ��ʼ����
	{
		e = random(10000);
		b = (double)e / 10000.0;
		for (j = 0, c = 0; j < N; j++)
		{
			c += geti[j].shiyingdu;
			if (b>((c - geti[j].shiyingdu) / leijishiyingdu) && b < (c / leijishiyingdu))
				fubei[i] = geti[j];
		}
	}
	for (i = 0; i < N; i++)
		geti[i] = fubei[i];
}
