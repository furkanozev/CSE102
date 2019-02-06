#include <stdio.h>
#include <stdlib.h>							/* I added the <stdlib.h> library to generate a random number. */


/* I created Grade_check function to determine the letter notation of the most successful and the most unsuccessful students. */
char Grade_check(int x)
{
	/* [100,90] = A , (90,80] = B , (80,70] = C , (70,60] = D , (60,50] = F */
	char letter;
	if( x <= 100 && x >= 90)
	{
		letter = 'A';
	}
		
	if( x < 90 && x >= 80)
	{
		letter = 'B';
	}
		
	if( x < 80 && x >= 70)
	{
		letter = 'C';
	}
		
	if( x < 70 && x >= 60)
	{
		letter = 'D';
	}
		
	if( x < 60 && x >= 0)
	{
		letter = 'F';
	}
	return letter;
}

int main()
{
	int count_student=0,count_grade,i,temple,suc_std=0,index_suc=0,unsuc_std=0,index_unsuc=0,selection;
	int count_A=0, count_B=0, count_C=0, count_D=0, count_F=0;
	double average,sum=0;
	int y=0;
	while(y!=-1)
	{
		printf("\n Enter student count: ");
		scanf("%d", &count_student);
		if(count_student < 3 || count_student > 50)
		{
			printf("\n Not in Range!!!\n");
		}
		else
		{
			y=-1;
		}
	}
	count_grade = count_student;
	srand(40);
	/* I have equaled the number of students to the number of grades. I used the srand(40) function for random numbers. */
	
	for(i = 1 ; i <= count_grade; i++)
	{
		temple = rand()%101;			/* I get the modulo according to 101 for numbers between 0 and 100 [0,100]. */
		sum = sum + temple;			/* Every number randomly assigned is assigned to the variable temple, and these numbers are added in variable sum. */
		
		/* Each assigned number is printed one by one. I printed spaces according to the number of digits so that the numbers are regular. */
		if(temple < 10) printf("  %d  ",temple);
		else if(temple < 100) printf(" %d  ",temple);
		else printf("%d  ",temple);
		/* I printed 10 numbers per line to make the screen image look good. */
		if(i % 10 == 0)
		{
			printf("\n");
		}
		
		/* If the new number is greater than the previous number, the new number will be assigned to variable suc_std, 
			Otherwise the old number will be kept in variable suc_std. The order of the large number will be assigned to the variable index_suc. */
		if(temple > suc_std)
		{
			suc_std = temple;
			index_suc = i;
		}
		
		/* If the new number is less than the previous number, the new number will be assigned to variable unsuc_std, 
			Otherwise the old number will be kept in variable unsuc_std. The order of the small number will be assigned to the variable index_suc. */
		if(temple < unsuc_std || i == 1)
		{
			unsuc_std = temple;
			index_unsuc = i;	
		}
		
		/* I check every numbers' grade that is randomly assigned, and I increase the letter grade counter by 1. */
		if(temple <= 100 && temple >= 90)
		{
			count_A++;
		}
		
		if(temple < 90 && temple >= 80)
		{
			count_B++;
		}
		
		if(temple < 80 && temple >= 70)
		{
			count_C++;
		}
		
		if(temple < 70 && temple >= 60)
		{
			count_D++;
		}
		
		if(temple < 60 && temple >= 0)
		{
			count_F++;
		}	
	}
	
	/* I divide the sum of the numbers by the number of the numbers to calculate the average. */
	average = sum / count_student;
	int x=0;
	/* I got into the while loop so that the user can see the menu until the -1 is entered. */
	while(x!=-1)
	{
		printf("\n-----------------------------------------------------\n");
		printf("Student Score Calculator Menu for %d Student\n\n",count_student);
		printf("1) Most Successful Student\n");
		printf("2) Most Unsuccessful Student\n");
		printf("3) Letter Grade Statistics\n");
		printf("4) Calculate Average\n");
		printf("5) Show all Data\n");
		printf("\t\t Make Selection: ");
		scanf("%d", &selection);
		
		switch(selection)
		{
			case 1:
				printf("\nMost Succesfully student: \n");
				printf("Index: %d\n", index_suc );
				printf("Score: %d\n", suc_std );
				printf("Letter grade: %c \n", Grade_check(suc_std) );
				break;
				
			case 2:
				printf(" \nMost Unsuccesfully student: \n");
				printf("Index: %d\n", index_unsuc );
				printf("Score: %d\n", unsuc_std );
				printf("Letter grade: %c \n", Grade_check(unsuc_std) );
				break;
				
			case 3:
				printf("\n%d student got letter grade 'A' \n", count_A );
				printf("%d student got letter grade 'B' \n", count_B );
				printf("%d student got letter grade 'C' \n", count_C );
				printf("%d student got letter grade 'D' \n", count_D );
				printf("%d student got letter grade 'F' \n", count_F );
				break;
				
			case 4:
				printf("\nThe avearage Score of %d Student is %lf\n", count_student, average );
				break;
				
			case 5:
				printf("\nMost Succesfully student: \n");
				printf("Index: %d\n", index_suc );
				printf("Score: %d\n", suc_std );
				printf("Letter grade: %c \n", Grade_check(suc_std) );
				
				printf("\nMost Unsuccesfully student: \n");
				printf("Index: %d\n", index_unsuc );
				printf("Score: %d\n", unsuc_std );
				printf("Letter grade: %c \n", Grade_check(unsuc_std) );
				
				printf("\n%d student got letter grade 'A' \n", count_A );
				printf("%d student got letter grade 'B' \n", count_B );
				printf("%d student got letter grade 'C' \n", count_C );
				printf("%d student got letter grade 'D' \n", count_D );
				printf("%d student got letter grade 'F' \n", count_F );
			
				printf("\nThe avearage Score of %d Student is %lf\n", count_student, average );
				break;
				
			/* If the user entered -1, the program will be terminated. */
			case -1:
				printf("\nYou were successfully exited.\n");
				x=-1;
				break;	
			
			default:
				printf("\nFalse Selection !!!\n");
				break;
		}
	}
	
	return 0;
}

