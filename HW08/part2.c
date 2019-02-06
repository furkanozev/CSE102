/*****
		FURKAN ÖZEV
		161044036
					*****/
					
					
#include <stdio.h>

char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int current);

int main()
{
	/* The cursor variable to hold the sequence number of the operator. */
	/* The current variable to keep the current value after the calculations using the operators. */
	int cursor = 0, current = 0, i;
	/* The * result_op variable to return the operators found by the find_operations function and assign a string. */
	char *result_op;
	
	/* arr_len is the size of the array in which the numbers are located. */
	size_t arr_len = 6;
	/* The expected_val variable is the value you want to achieve as a result of calculations using all numbers. */
	int expected_val = 44;
	/* The numbers you want to use */
	int arr[6] = {25, 12, 6, 10, 32, 8};
	/* arr is the array of characters the operators hold. If there are n digits, n-1 operators will be used.
		I created an n-dimensional array of characters to show that the character array is finished.
		operations[n] should be '\0'. */
	char operations[6];
	
	
	result_op = find_operations(arr, expected_val, operations, arr_len, cursor, current);
	
	/* Printing {+,-,*,-,...} or { , , , ,...} format */
	printf("{");
	for(i = 0; i < arr_len-1 ; i++)			/* There are arr_len-1 operators. */
	{
		printf("%c",result_op[i]);
		if(i != arr_len-2) printf(",");		/* There will be no comma after the last character. */
	}
	printf("}");
	
	return 0;
}

char* find_operations(int arr[], int expected_val, char operations[], size_t arr_len, int cursor, int current)
{

	if(cursor == 0) /* It is the starting point of the recursive function. */
	{
		int i;
		/* The * op variant will be used to hold and return the character string returned by the function. */
		char *op;
		
		/* First, the first value in the array is assigned to the current variable. */
		current = arr[0];
		/* It then invokes its own function to make calculations using operators. */
		op = find_operations(arr, expected_val, operations, arr_len, cursor+1, current);
		
		/* If the resulting character array is the last character space, then there is no valid result. 
			Then replace the elements of array with spaces. */
		if(op[arr_len-2] == ' ')
		{
			for(i = 0; i < arr_len-1; i++)
			{
				op[i] = ' ';
			}
		}
	}
	
	else if(cursor < arr_len)
	{
		int i;
		/* I have defined 3 different variables to hold the result of each different process. */
		int current1 = current, current2 = current, current3 = current;

		/* Used to hold applied operators. */
		char *op1, *op2, *op3;
		
		/* According to the base condition , if the last element of the array returned by the function is not empty, 
			it returns the result. The result is found and return it. Please check base condition.*/
		
		/* Calculate using '+' operators. Get new total number(current1) by adding new number with previous total number(current).*/
		operations[cursor-1] = '+';
		current1 = current + arr[cursor];
		op1 = find_operations(arr, expected_val, operations, arr_len, cursor+1, current1);		/* RECURSIVE */
		if(op1[arr_len-2] != ' ') return op1;
		
		/* Calculate using '-' operators. Get new total number(current2) by substracting new number with previous total number(current).*/
		operations[cursor-1] = '-';
		current2 = current - arr[cursor];		
		op2 = find_operations(arr, expected_val, operations, arr_len, cursor+1, current2);		/* RECURSIVE */
		if(op2[arr_len-2] != ' ') return op2;
		
		/* Calculate using '*' operators. Get new total number(current3) by multiplying new number with previous total number(current).*/
		operations[cursor-1] = '*';
		current3 = current * arr[cursor];
		op3 = find_operations(arr, expected_val, operations, arr_len, cursor+1, current3);		/* RECURSIVE */
		if(op3[arr_len-2] != ' ') return op3;
		
	}
	/* Base condition. 
		Check that you have reached the expected_number once you have done the last calculation.*/
	else if(cursor == arr_len)
	{
		/* If it has not reached the number, change the last element of character array to space.
		/* If the target number is reached, the last element of the character array will not be empty. 
			The last operator will be found. */
		if(current != expected_val)
		{
			operations[arr_len-2] = ' ';
		}
		operations[arr_len-1] = '\0';
	}
	/* Return the operators it has applied so far. */
	return operations;
}
