/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/
#include <stdio.h>
#include "hw4_lib.h"

/* the result is calculated by the basic integral formula. like the sum of the rectangles remaining under the graph.*/
double integral(double f(double x), double xs, double xe, double delta)
{
	double h, i, sum=0;
	for(i=1 ; h<=xe ; i++)
	{
		h = xs + delta*i;
		sum = sum + delta*f(h);
	}
	return sum;
}

/* the result is calculated by the basic double integral formula. like the sum of the rectangles remaining under the graph. */
double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta)
{
	double range1, range2, h1, h2, i, j, sum=0;
	range1=(xe-xs)/delta;
	range2=(ye-ys)/delta;
	for(j=1 ; j<=range2 ; j++)
	{
		for(i=1 ; i<=range1 ; i++)
		{
			h1 = xs + delta*i;
			h2 = ys + delta*j;
			sum = sum + delta*delta*f(h1,h2);
		}
	}
	return sum;
}

/* Calculated using numeric derivative formula. if eps is 0 , will return -1 , If eps is 0, function returns -1 if it is not 0, return 1.*/
int derivatives(double f(double a), double x, double eps, double * d1, double * d2)
{
	int i=1;
	*d1 = ( f(x+eps) - f(x-eps) ) / (2 * eps);
	*d2 = ( f(x+eps) - 2*f(x) + f(x-eps) ) / (eps * eps);
	if(eps == 0)
	{
		i = -1;
	}
	return i;
}

/* Numeric derivative calculated using numeric derivative formula and actuals derivative calculated. The absolute difference between them is returned. */
int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2)
{
	*e1 = ( f(x+eps) - f(x-eps) ) / (2 * eps) - d1(x);
	*e2 = ( f(x+eps) - 2*f(x) + f(x-eps) ) / (eps * eps) - d2(x);
	if(*e1<0)
	{
		*e1=*e1 * -1;
	}
	if(*e2<0)
	{
		*e2=*e2 * -1;
	}
	return 0;
}


int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4)
{
	/* Newton Raphson Rule's */
	int index=0;
	double eps=0.0001,d1,x,temp,tempx,range1,range2;
	double array[4]={0};
	printf("\n Enter the range where the roots are located. [range1,range2]: ");
	scanf("%lf%lf",&range1,&range2);
	/* User enter the range after will find the roots. */
	for(x=range1; x<=range2 ; x+=eps)
	{
		/* If delta = - f(Xo) / f'(Xo) , Xo is root */ 
		d1 = ( f(x+eps) - f(x-eps) ) / (2 * eps);
		temp = eps * d1 + f(x);
		/* The eps*10 was taken as a margin of error because that very small values would not be calculated. */
		if(temp <=eps*10 && temp >= -eps*10)
		{
			array[index]=x;
			index++;
			x += 0.0011;
		}
	}
	*x1 = array[0];
	*x2 = array[1];
	*x3 = array[2];
	*x4 = array[3];
	return index; /* Number of roots */
}
