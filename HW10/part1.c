/**------------------------***/
/***-----FURKAN ÖZEV-----****/
/****-----161044036-----****/
/***--------------------***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>			/* Using for clock() function */

/* Creating a struct for a linked list. */
typedef struct linked_list{
	double number;
	struct linked_list* next; /* it keeps the next struct's address. */
}linked_list;

void rec_linked_list();
void rec_dynamic_array();
double read(FILE* *filep, int *flag);
int check_prime(double number);

int main()
{
	printf("-------------------PROGRAM STARTED-------------------\n");
	
	printf("\n\t\t=> LINKED LIST <=\n\n");
	rec_linked_list();
	
	printf("\n\n\t\t=> DYNAMIC ARRAY <=\n\n");
	rec_dynamic_array();
	
	printf("\n\nThe program has been successfully completed.\n");
			
	return 0;
}

/* Record linked_list */
void rec_linked_list()
{
	/* Parameters created to hold times. */
	clock_t start_t,end_t, end_t1,end_t2,end_t3,start_print,end_print;
	double total_t1,total_t2,total_t3,total_print=0,total_calc=0;
	
	int counter=0, i, res=0, flag=0;
	double number;
	/* Struct's address pointers */
	linked_list* head;
	linked_list* templist;
	linked_list* newlist;
	
	/* Open data.txt file and creat output_prime_LinkedList.txt file */
	FILE *filedata;
	filedata = fopen("data.txt","rt");
	if(filedata == NULL)
	{
		printf("The file data.txt is not found. \n");
		return;
	}
	
	FILE *fileprime;
	fileprime = fopen("output_prime_LinkedList.txt","wt");
	if(fileprime != NULL)
	{
		printf("output_prime_LinkedList.txt file was created.\n");
	}
	else
	{
		printf("\noutput_prime_LinkedList.txt could not be created.\n");
		return;
	}
	
	printf("\nLinked lists are creating and values read from file are writing to the parameters. \n");


	/* CODE - QUESTION 2 part 1 :  Record all these numbers (data.txt) into Linked-List. */
	
	/* the loop will continue until the end of the file, that is, until the numbers are exhausted. */
	while(flag != -1)
	{
		counter++;		/* number counter */
		number = read(&filedata, &flag);	/* get the number read function. if numbers are exhausted , flag will be -1 and loop will end. */
		if(counter == 1)
		{
			/* First (Head) struct will creat */
			head = malloc(sizeof(linked_list));		/* allocate memory for new struct*/
			head->number = number;					/* initialize number */
			head->next = NULL;						/* initialize next struct's address */
			templist = head;						/* hold new list address */
		}
		else
		{
			newlist = malloc(sizeof(linked_list));	/* allocate memory for new struct*/
			newlist->number = number;				/* initialize number */
			newlist->next = NULL;					/* initialize next struct's address */
			templist->next = newlist;				/* write the address of the new list to the variable holding the address of the previous list. */
			templist = newlist;						/* hold new list address */
		}
	}
	/* The counter value will be 1 more, it should be reduced by 1 . */
	counter--;
	
	printf("\tLinked lists were created and the values read from the file were written to the parameters. \n");
	
	printf("\nThe process of finding prime numbers and writing them to the file started. \n");
	
	/* The controls will start at the head of the list. */
	templist = head;
	start_t = clock();		/* start time for check if number is prime and write in file */
	for(i=1 ; i < counter; i++)
	{
		/* CODE - QUESTION 2 part 2 :  find and show all prime numbers for linked list. */
		
		res = check_prime(templist->number);	/* if check prime function return 1 , number must be prime number */
		if(res == 1)
		{
			/* CODE - QUESTION  4 : Calculate the file written time for output_prime_LinkedList.txt file for data between 1 and 1.000.000. */
			
			/* (start_print - end_print) is used to determine the period of time to write 1 number. */
			start_print = clock();				
			fprintf(fileprime, "%.0lf,00\n",templist->number);		/* Print number in file */
			end_print = clock();
			/* total_print holds the time to write to the file for all number. */ 
			total_print += ((double)(end_print - start_print) / CLOCKS_PER_SEC);
		}
		
		templist = templist->next; 			/* Skip to next list */
		
		/* CODE - QUESTION 3 : Compare the calculation time of linked list according to values of data.txt */
		
		/* Determines the elapsed time for calculation of prime numbers up to 500 thousands. */
		if(templist->number == 500000)
		{
			/* CODE - QUESTION 3 part 1 : for between 1 and 500 thousands. */
			
			end_t1 = clock();
			total_t1 = (double)(end_t1 - start_t) / CLOCKS_PER_SEC;		/* total time to reach this number */
			/* To determine the calculation time, the total number of times to reach that number, the number of times to print the file is subtracted. */
			total_t1 -= total_print;
		}
		/* Determines the elapsed time for calculation of prime numbers up to 750 thousands. */
		else if(templist->number == 750000)
		{
			/* CODE - QUESTION 3 part 2 : for between 1 and 750 thousands. */
			
			end_t2 = clock();
			total_t2 = (double)(end_t2 - start_t) / CLOCKS_PER_SEC; 	/* total time to reach this number */
			/* To determine the calculation time, the total number of times to reach that number, the number of times to print the file is subtracted. */
			total_t2 -= total_print;
		}
		/* Determines the elapsed time for calculation of prime numbers up to 1 million. */
		else if(templist->number == 1000000)
		{
			/* CODE - QUESTION 3 part 3 : for between 1 and 1 million. */
			
			end_t3 = clock();
			total_t3 = (double)(end_t3 - start_t) / CLOCKS_PER_SEC;		/* total time to reach this number */
			/* To determine the calculation time, the total number of times to reach that number, the number of times to print the file is subtracted. */
			total_t3 -= total_print;
		}
	}
	end_t=clock();		/* Process time for all number */
	total_calc = ((double)(end_t - start_t) / CLOCKS_PER_SEC) - total_print;
	/* total_calc => Calculation time for all number.	total_print => Writting time for all number. */
	
	printf("\tThe prime numbers were found and written to the file. \n");
	
	/* CODE - QUESTION 3 part 4 : Write your calculation time results of questions into output_prime_LinkedList.txt */
	
	/* Write in file all calculated times. */
	fprintf(fileprime, "\nBetween 1 and 500.000 calculation time = %.3lf millisecond.",total_t1*1000);
	fprintf(fileprime, "\nBetween 1 and 750.000 calculation time = %.3lf millisecond.",total_t2*1000);
	fprintf(fileprime, "\nBetween 1 and 1.000.000 calculation time = %.3lf millisecond.",total_t3*1000);
	fprintf(fileprime, "\nALL NUMBER calculation time = %.3lf millisecond, writting time = %.3lf millisecond.",total_calc*1000, total_print*1000);
	
	/* Show on screen all calculated times. */
	printf("\nBetween 1 and 500.000 calculation time = %.3lf millisecond.",total_t1*1000);
	printf("\nBetween 1 and 750.000 calculation time = %.3lf millisecond.",total_t2*1000);
	printf("\nBetween 1 and 1.000.000 calculation time = %.3lf millisecond.",total_t3*1000);
	printf("\nALL NUMBER calculation time = %.3lf millisecond, writting time = %.3lf millisecond.",total_calc*1000, total_print*1000);
	
	/* Close file */
	fclose(filedata);
	fclose(fileprime);
	
	/* Free allocated memory for linked list. */
	while(head->next != NULL )
	{
		templist = head;
       	head = head->next;
       	free(templist);
	}
	
	printf("\n\nThe process applied for linked lists have been successfully completed.");
}

void rec_dynamic_array()
{
	/* Parameters created to hold times. */
	clock_t start_t,end_t, end_t1,end_t2,end_t3,start_print,end_print;
	double total_t1,total_t2,total_t3,total_print=0,total_calc=0;
	
	int counter = 0, i=0, res=0, flag=0;
	/* Creat Dynamic array */
	double* array;
	double number;
	
	/* Open data.txt file and creat output_prime_dynamic_array.txt file */
	FILE *filedata;
	filedata = fopen("data.txt","rt");
	if(filedata == NULL)
	{
		printf("The file data.txt is not found. \n");
		return;
	}
	FILE *fileprime;
	fileprime = fopen("output_prime_dynamic_array.txt","wt");
	if(fileprime != NULL)
	{
		printf("output_prime_dynamic_array.txt file was created.\n");
	}
	else
	{
		printf("output_prime_dynamic_array.txt could not be created.\n");
		return;
	}
	
	printf("\nDynamic array is creating and values read from file are writing to the array.  \n");
	
	/* CODE - QUESTION 2 part 1 :  Record all these numbers (data.txt) into Dynamic array. */
	
	/* Allocate memory for 1 double number for startting. */
	array = (double *) malloc(sizeof(double));
	/* the loop will continue until the end of the file, that is, until the numbers are exhausted. */
	while(flag != -1)
	{
		counter++;
		/* As the number is read from the line, the allocated memory for the array will be incremented. using realloc function.*/
		array = (double *)realloc(array, (counter)*sizeof(double));
		/* The number is added to the array. */
		array[counter-1] = read(&filedata, &flag);
	}
	/* The counter value will be 1 more, it should be reduced by 1 . */
	counter--;

	printf("\tDynamic array was created and the values read from the file were written to the array. \n");

	printf("\nThe process of finding prime numbers and writing them to the file started. \n");

	start_t = clock();		/* start time for check if number is prime and write in file */
	for(i=0; array[i] < counter; i++)
	{
		/* CODE - QUESTION 2 part 2 :  find and show all prime numbers for dynamic array. */
		
		res = check_prime(array[i]);
		if(res == 1)		/* if check prime function return 1 , number must be prime number */
		{
			/* CODE - QUESTION 4 : Calculate the file written time for output_prime_dynamic_array.txt file for data between 1 and 1.000.000. */
			
			/* (start_print - end_print) is used to determine the period of time to write 1 number. */
			start_print = clock();
			fprintf(fileprime, "%.0lf,00\n",array[i]);		/* Print number in file */
			end_print = clock();
			/* total_print holds the time to write to the file for all number. */ 
			total_print += ((double)(end_print - start_print) / CLOCKS_PER_SEC);	
		}
		
		/* CODE - QUESTION 3 : Compare the calculation time of dynamic array according to values of data.txt */
		
		/* Determines the elapsed time for calculation of prime numbers up to 500 thousands. */
		if(array[i+1] == 500000)
		{
			/* CODE - QUESTION 3 part 1 : for between 1 and 500 thousands. */
			
			end_t1 = clock();
			total_t1 = (double)(end_t1 - start_t) / CLOCKS_PER_SEC;		/* total time to reach this number */
			/* To determine the calculation time, the total number of times to reach that number, the number of times to print the file is subtracted. */
			total_t1 -= total_print;
		}
		/* Determines the elapsed time for calculation of prime numbers up to 750 thousands. */
		else if(array[i+1] == 750000)
		{
			/* CODE - QUESTION 3 part 2 : for between 1 and 750 thousands. */
			
			end_t2 = clock();
			total_t2 = (double)(end_t2 - start_t) / CLOCKS_PER_SEC;		/* total time to reach this number */
			/* To determine the calculation time, the total number of times to reach that number, the number of times to print the file is subtracted. */
			total_t2 -= total_print;
		}
		/* Determines the elapsed time for calculation of prime numbers up to 1 million. */
		else if(array[i+1] == 1000000)
		{
			/* CODE - QUESTION 3 part 3 : for between 1 and 1 million. */
			
			end_t3 = clock();
			total_t3 = (double)(end_t3 - start_t) / CLOCKS_PER_SEC;		/* total time to reach this number */
			/* To determine the calculation time, the total number of times to reach that number, the number of times to print the file is subtracted. */
			total_t3 -= total_print;
		}
	}
	end_t=clock();		/* Process time for all number */
	total_calc = ((double)(end_t - start_t) / CLOCKS_PER_SEC) - total_print;
	/* total_calc => Calculation time for all number.	total_print => Writting time for all number. */
	
	printf("\tThe prime numbers were found and written to the file. \n");
	
	/* CODE - QUESTION 3 part 4 : Write your calculation time results of questions into output_prime_dynamic_array.txt */
	
	/* Write in file all calculated times. */
	fprintf(fileprime, "\nBetween 1 and 500.000 calculation time = %.3lf millisecond.",total_t1*1000);
	fprintf(fileprime, "\nBetween 1 and 750.000 calculation time = %.3lf millisecond.",total_t2*1000);
	fprintf(fileprime, "\nBetween 1 and 1.000.000 calculation time = %.3lf millisecond.",total_t3*1000);
	fprintf(fileprime, "\nALL NUMBER calculation time = %.3lf millisecond, writting time = %.3lf millisecond.",total_calc*1000, total_print*1000);
	
	/* Show on screen all calculated times. */
	printf("\nBetween 1 and 500.000 calculation time = %.3lf millisecond.",total_t1*1000);
	printf("\nBetween 1 and 750.000 calculation time = %.3lf millisecond.",total_t2*1000);
	printf("\nBetween 1 and 1.000.000 calculation time = %.3lf millisecond.",total_t3*1000);
	printf("\nALL NUMBER calculation time = %.3lf millisecond, writting time = %.3lf millisecond.",total_calc*1000, total_print*1000);
	
	/* Close file */
	fclose(filedata);
	fclose(fileprime);
	
	/* Free allocated memory for dynamic array */
	free(array);
	
	printf("\n\nThe process applied for dynamic array have been successfully completed.");
}

/* CODE - QUESTION 1 : Write a C programming function which read each line from “data.txt” file. */

/* This function reads the number lines line by line. */
double read(FILE* *filep, int *flag)
{
	char line[20];
	double number;
	if(fgets(line, 1024, *filep) != NULL)	/* 1024 is line buffer */
	{
		/* convert the number from string*/
		sscanf(line,"%lf,00",&number);
	}
	/* If it comes to the end of the file, the numbers are finished. the flag will be -1. */
	else *flag = -1;
	return number;
}

/* Check if the number is prime.*/
int check_prime(double number)
{
	/* If the number can not divided into any number except itself and 1, it is prime. */
	int flag=0, i;
	for(i=2; i<=number/2 && flag == 0; ++i)
	{
    	if((int)number%i==0)
    	{
        	flag=1;
    	}
	}
	if(flag == 0 && number != 1) /* Number is prime */
	{
		return 1;
	}
	else return -1;		/* Number is not prime */
}




