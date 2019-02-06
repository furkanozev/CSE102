#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* I added stdlib.h and time.h libraries to generate random numbers. */

void menu();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);
void horseRacingGame();
void countOccurrence();
void triangleOfSequences();

int main()
{	
	srand(time(NULL));
	menu();
	
	return 0;
}

void menu()
{
	int selection;
	do
	{
		/* I printed the menu and the user will make a choice. */
		printf("\n 1. Horse Racing Game");	
		printf("\n 2. Occurrence Counter");	
		printf("\n 3. Triangle of Sequences");	
		printf("\n 0. Exit");
		printf("\n Selection: ");
		scanf("%d", &selection);
		
		switch(selection)
		{
			case 1:
				horseRacingGame();
				break;
			case 2:
				countOccurrence();
				break;
			case 3:
				triangleOfSequences();
				break;
			case 0:
				printf("\n You were successfully exited.");
				break;
			/* If the user's choice is wrong, he will choose again.*/
			default:
				printf("You entered the wrong value. Please enter again.\n");
				break;
		}	
	}
	/* The menu will be displayed as long as the user does not enter 0. If the user enters 0, the program will be terminated. */
	while(selection != 0);	
}

int getInt(int mini, int maxi)
{
	/* I asked the user to enter a number and then checked whether the number entered was within the specified range. */
	int number;
	scanf("%d", &number);
	/* If the number is not in the specified range, I want the user to enter a new number. */
	while(number < mini || number > maxi)
	{
		printf("\n You entered the wrong value. Please enter again.");
		scanf("%d", &number);	
	}
	return number;	
}

/* I used this function to generate a random number in the user-specified range. */
int numberGeneratorBetweenRange(int min, int max)
{
	int random = 0;
	/* I check to if the generated number is in range, if not in range, I generate new number. */
	while(random < min || random > max)
	{
		/* I get the mod randomly generated numbers according to a bigger number than the maximum number 
			so that the count can be generated more quickly in the desired range. */
		random = rand()%(max+1);	
	}	
		
	return random;
}


void horseRacingGame()
{
	int i, x, index = 0, time = 0, winner_index = 0, winner2_index = 0, check = 0;
	int number_horses = 0, num_horse = 0;
	
	/* I use the random number generating function to determine the number of horses to compete. 
		The number of horses can be at least 3 and at most 5. 
		I assign the number generated randomly in the specified range to number_horses variable. */
	number_horses = numberGeneratorBetweenRange(3, 5);
	printf("\n Number of Horse: %d", number_horses);
	
	/* I used the getInt function to let the user select any horse from within the existing number of horses.
		 I have assigned the user-selected horse number to the variable num_horse. */
	printf("\n Horse Number: ");
	num_horse = getInt(1, number_horses);
	printf("\n Racing starts...");
	
	/* Horses that specified random number will compete and random speeds will be determined for these horses. */
	for(i = 1 ; i <= number_horses ; i++)
	{
		/* I randomly specified the speeds and print "-" as much as speed. */
		printf("\n Horse %d: ", i);
		time = numberGeneratorBetweenRange(10, 20);
		for(x = 0 ; x < time ; x++)
		{
			printf("-");	
		}
		
		/* If the new horse is faster than the previous one, I keep the new horse's speed and number in the variables. */
		if(time < check || i==1)
		{
			check = time;
			winner_index = i;
			winner2_index = i;	
		}
		
		/* If the new horse's speed equals the previous horse's speed, I keep both the old horse and the new horse's numbers.
			If there is a faster horse than these horse, the values of the variables will be changed. */
		else if(time == check)
		{
			winner2_index = i;
		}	
	}
	
	/* The speed of the fastest horses is checked to see if they are equal.
		If the speeds of these horses are equal, the index values in the variables winner_index and winner2_index will be different. */
	if(winner_index == winner2_index)
	{
		/* If the selected horse is the fastest horse, the user wins the race. */
		if(num_horse == winner_index)
		{
			printf("\n You win!\n");	
		}
		
		/* If the selected horse is not the fastest horse, the user lose the race. */
		else
		{
			printf("\n You Lose! Winner is Horse %d.\n", winner_index);	
		}	
	}
	
	/* If the speeds of the two fastest horses are equal, there is no winner. */
	else
	{
		printf("\n No winner!\n");
	}		
}

void countOccurrence()
{
	int x = 1, counter = 0, mod = 0 , number_digits = 1, temp = 0;
	int bigNumber, searchNumber;
	
	/* The user enters a bigger number. */
	printf("\n Big Number: ");
	scanf("%d", &bigNumber);
	
	/* I used the getInt function to get a number that is equal to or smaller than the big number that the user has entered. */
	printf(" Search Number: ");
	searchNumber = getInt(0, bigNumber);
	temp = searchNumber;
	
	/* Determine the number of digits searchNumber. */
	while(temp >= 10)
	{
		temp = temp / 10;
		number_digits += 1;
	}
	
	/* According to the number of digits searchNumber, I determine prime of 10.
		Because I will use this number when I get the mode. */
	/* For example bigNumber = 28378396 and searchNumber = 83 so searchNumber has a 2 digits then I must get the modula to 100. */
	while(number_digits > 0)
	{
		x = x * 10;
		number_digits -= 1;	
	}	
	
	/* I check if the number of bigNumber is equal to the number of searchNumber by taking the mode according to x. */
	while(bigNumber >= searchNumber)
	{
		mod = bigNumber % x;
		/* If the numbers are equal, increase the counter by 1. */
		if(mod == searchNumber)
		{
			counter++;
		}
		/* I divide by 10 to compare with the next group of numbers. */
		bigNumber = bigNumber / 10;
	}
	
	printf(" Occurrence: %d\n", counter);
}


void triangleOfSequences()
{
	int lenght = 0, i, x;
	
	/* I used this function to set the edge length as a random number between 2 and 10. */
	lenght = numberGeneratorBetweenRange(2, 10);
	printf("\n Output (for %d):\n",lenght);
	/* There will be as many lines as the length, and each line will have as many as the line number. */
	for(i = 1 ; i <= lenght ; i++)
	{
		/* The numbers to be printed will be multiples of the line number. */
		for(x = i ; x <= i*i ; x += i)
		{
			printf("%d ", x);
		}
		printf("\n");
	}	
}
