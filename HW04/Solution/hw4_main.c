/*
** main.c:
**
** The test program for the homework.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.14
** 
*/


#include <stdio.h>


#include "hw4_lib.h"
#include "hw4_io.h"

void test_polynomial3()
{
	double a0,a1,a2,a3;
	read_polynomial3(&a0,&a1,&a2,&a3);
	printf("\n");
	write_polynomial3(a0,a1,a2,a3);
}

void test_polynomial4()
{
	double a0,a1,a2,a3,a4;
	read_polynomial4(&a0,&a1,&a2,&a3,&a4);
	printf("\n");
	write_polynomial4(a0,a1,a2,a3,a4);
}

void test_integral()
{
	double result;
	double f(double x) { return 4*x*x*x-2*x*x+4; }
	result = integral(f, 2, 5, 0.001);
	printf("\n Result of the integral: %f",result);
}

void test_integral2()
{
	double result;
	double f(double x, double y) { return x*x+2*y; }
	result = integral2(f, 0, 4, 2, 10, 0.001);
	printf("\n Result of the integral2: %f",result);
}

void test_derivatives()
{
	int res;
	double d1, d2;
	double f(double x) { return 4*x*x*x-2*x*x+4; }
	res = derivatives(f, 5, 0.0001, &d1, &d2);
	printf("\n Result of the derivative1: %f \n Result of the derivative2:  %f \n Return= %d",d1,d2,res);
}

void test_compare_derivatives()
{
	double f(double x) { return 4*x*x*x-2*x*x+4; }
	double d1(double x) { return 12*x*x-4*x; }
	double d2(double x) { return 24*x-4; }
	double e1, e2;
	int res = compare_derivatives(f, d1, d2, 1.0, 0.01, &e1, &e2);
	printf("\n Error for derivative1: %f \n Error for derivative2: %f",e1,e2);
}

void test_find_roots()
{
	double x1=0,x2=0,x3=0,x4=0;
	int res;
	double f(double x) { return (x-3)*(x+1)*(x-7)*(x+4); }
	res= find_roots(f, & x1, & x2, & x3, & x4);
	printf("\n Root1 = %.3f \n Root2 = %.3f \n Root3 = %.3f \n Root4 = %.3f \n Number of roots = %d",x1,x2,x3,x4,res);
}

/*
** main function for testing the functions...
**
*/
int main(void) {
	test_polynomial3();
	test_polynomial4();
	test_integral();
	test_integral2();
	test_derivatives();
	test_compare_derivatives();
	test_find_roots();
	return (0);
} /* end main */
