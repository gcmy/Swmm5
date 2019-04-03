#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include <string.h>
#include "headers.h"
#define N 1061
#define REAL4 float
extern REAL4* NodeResults;
struct Gene
{
	double canshu[5];
	double shiyingdu;
};
int     period, k;
DateTime days;
char     theDate[20];
char     theTime[20];
double wucha = 0, DC;
double sum = 0.0, mean1 = 0.0;
double mean(double flow[],int Number)
{
	
	for (int i = 0; i < Number; i++)
		sum += flow[i];
	mean1 = sum / Number;
	return mean1;
}
double var(double flow[],int Number)
{
	double mean1 = mean(flow, Number);
	double sum = 0;
	for (int i = 0; i < Number; i++)
		sum += pow(flow[i] - mean1,2);	
	return sum;
}

double objfunc(double outflow[],double shice)
{	
	/// outflow 是实际输出的流量
	///shice为nash效应系数的分母
	///
	double wucha = 0.0;
	for (period = 1; period <= Nperiods; period++)
	{
		output_readDateTime(period, &days);
		datetime_dateToStr(days, theDate);
		datetime_timeToStr(days, theTime);
		output_readNodeResults(period, Nobjects[NODE]-1);
		wucha += pow(NodeResults[NODE_INFLOW] - outflow[period-1], 2);
	}
	DC = 1 - wucha / shice;
	return DC;

}


