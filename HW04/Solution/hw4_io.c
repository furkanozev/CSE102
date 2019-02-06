/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include <stdio.h>
#include "hw4_io.h"

/* I got the coefficients of the function from the user using the scanf function. */
int read_polynomial3(double * a0, double * a1, double * a2, double * a3)
{
	printf("\nEnter the coefficients of a degree-3: ");
	scanf("%lf", &*a3);
	printf("\nEnter the coefficients of a degree-2: ");
	scanf("%lf", &*a2);
	printf("\nEnter the coefficients of a degree-1: ");
	scanf("%lf", &*a1);
	printf("\nEnter the coefficients of a degree-0: ");
	scanf("%lf", &*a0);
	return  0;
}

/* I got the coefficients of the function from the user using the scanf function. */
int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4)
{
	printf("\nEnter the coefficients of a degree-4: ");
	scanf("%lf", &*a4);
	printf("\nEnter the coefficients of a degree-3: ");
	scanf("%lf", &*a3);
	printf("\nEnter the coefficients of a degree-2: ");
	scanf("%lf", &*a2);
	printf("\nEnter the coefficients of a degree-1: ");
	scanf("%lf", &*a1);
	printf("\nEnter the coefficients of a degree-0: ");
	scanf("%lf", &*a0);
	return  0;
}

void write_polynomial3(double a0, double a1, double a2, double a3)
{
	double array[4]={a0,a1,a2,a3};
	int i;
	for(i=3 ; i>1 ; i--)
	{
		/* If the value is 1 or -1 in the coefficients up to degree 1, it will be printed as +x or -x. */
		if(array[i]==1.0 || array[i]==-1.0 )
		{
			if(array[i]==1.0)
			{
				printf("+x^%d",i);
			}
			else
			{
				printf("-x^%d",i);
			}
		}
		else
		{
			/* in the coefficients up to degree 1, if the value is greater than 0 , +number will be printed or is less than 0, the number will be printed. */
			if(array[i]>0)
			{
				printf("+%gx^%d", array[i],i);
			}
			else if(array[i]<0)
			{
				printf("%gx^%d", array[i],i);
			}
		}
	}
	/* X for degree 1 will be printed instead of x ^ 1. */
	if(array[i]>0)
	{
		printf("+%gx", array[i]);
	}
	else if(array[i]<0)
	{
		printf("%gx", array[i]);
	}
	i--;
	/* Only numbers for degree 0 will be printed. */
	if(array[i]>0)
	{
		printf("+%g", array[i]);
	}
	else if(array[i]<0)
	{
		printf("%g", array[i]);
	}
	printf("\n");
}

void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
	double array[5]={a0,a1,a2,a3,a4};
	int i;
	for(i=4 ; i>1 ; i--)
	{
		/* If the value is 1 or -1 in the coefficients up to degree 1, it will be printed as +x or -x. */
		if(array[i]==1.0 || array[i]==-1.0)
		{
			if(array[i]==1.0)
			{
				printf("+x^%d",i);
			}
			else
			{
				printf("-x^%d",i);
			}
		}
		else
		{
			/* in the coefficients up to degree 1, if the value is greater than 0 , +number will be printed or is less than 0, the number will be printed. */
			if(array[i]>0)
			{
				printf("+%gx^%d", array[i],i);
			}
			else if(array[i]<0)
			{
				printf("%gx^%d", array[i],i);
			}
		}
	}
	/* X for degree 1 will be printed instead of x ^ 1. */
	if(array[i]>0)
	{
		printf("+%gx", array[i]);
	}
	else if(array[i]<0)
	{
		printf("%gx", array[i]);
	}
	i--;
	/* Only numbers for degree 0 will be printed. */
	if(array[i]>0)
	{
		printf("+%g", array[i]);
	}
	else if(array[i]<0)
	{
		printf("%g", array[i]);
	}
	printf("\n");
}
