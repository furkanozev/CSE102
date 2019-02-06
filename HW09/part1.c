/**------------------------***/
/***-----FURKAN ÖZEV-----****/
/****-----161044036-----****/
/***--------------------***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>			/* to generate random values. */

/* Structers is defined like pdf. */

typedef struct Forest
{
	char** Map;				/* Pointer to pointer. To create a 2D dynamic character array. */
	int Width;
	int Height;
	int Flower_X;
	int Flower_Y;
} Forest;

typedef struct Botanist
{
	int Coord_X;
	int Coord_Y;
	int Water_Bottle_Size;
} Botanist;

void init_game (Forest *forest, Botanist *botanist);
void print_map (Forest forest);
void search(Forest *forest, Botanist *botanist);

int main()
{
	Forest forest;
	Botanist botanist;
	srand(time(NULL));						/* to generate random values.*/
	init_game(&forest, &botanist);			/* initilaze */
	print_map(forest);						/* print */
	search(&forest, &botanist);				/* random move recursion function */
	
	/* Release memory allocated with calloc. to 2 Dimensional array*/
	int i;
	for(i = 0; i < forest.Height; i++)
	{
		free(forest.Map[i]);
	}
	free(forest.Map);
	
}

void init_game (Forest *forest, Botanist *botanist)
{
	int i,x,y;
	FILE *finput = fopen("init.txt","rt");						/* Open file to read */ 
	char temp_ch;												/* to hold characters that read from the file. */
	
	fscanf(finput, "%d", &botanist->Water_Bottle_Size);			/* Get Water_Bottle_Size from first row. */
	fscanf(finput, "%d %c %d", &forest->Height, &temp_ch, &forest->Width); 		/* Get height, comma , width from second row. */
	
	/* Free space is allocated in memory by using calloc for 2D character array. */
	/* Like this => array[height][width] , dimensions will be taken from the file.(dynamic array) */
	forest->Map = (char **)calloc(forest->Height , sizeof(char*));
	for(i = 0; i < forest->Height; i++)
	{
		forest->Map[i] = (char *)calloc(forest->Width , sizeof(char));
	}
	
	/* Read the characters in the file one by one. */
	for(y=0; y<forest->Height; y++)
	{
		for(x=0; x<forest->Width; x)			/* If the correct character (like '#' or space(' ') and not comma(',')) is found, the x update will be done. */
		{
			fscanf(finput,"%c", &temp_ch);				/* Get character one by one. */
			/* Determines the botanist's starting position. */
			if(temp_ch == 'B')
			{
				botanist->Coord_X = x;
				botanist->Coord_Y = y;
			}
			/* Determines the flower position. */
			if(temp_ch == 'F')
			{
				forest->Flower_X = x;
				forest->Flower_Y = y;
			}
			/* Determine and initilaze correct characters. new line '\n' and comma ',' musnt be in map, '#' , space ' ', Flower 'F' and Botanist 'B' must be in map. */
			if((temp_ch == ' ' || temp_ch == '#' || temp_ch == 'F' || temp_ch == 'B'))
			{
				forest->Map[y][x] = temp_ch;
				x++;
			}
		}
	}
	
	fclose(finput);		/* Close file */
}

void print_map (Forest forest)
{
	int x, y;			/* y rows, x columns */
	printf("\n");
	for(y=0; y<forest.Height; y++)
	{
		for(x=0; x<forest.Width; x++)
		{
			printf("%c ", forest.Map[y][x]);		/* print character with 1 space like pdf.*/
		}
		printf("\n");	/* Next row */
	}
}

void search(Forest *forest, Botanist *botanist)
{	
	/* First base condition. the status of the botanist reaching the flower. */ 
	if((botanist->Coord_X == forest->Flower_X) && (botanist->Coord_Y == forest->Flower_Y))
	{
		printf("\nSearching...\n");
		/* According to the pdf, If the botanist reaches the flower, then 'F' ( Not 'B' ) will print in that position. */
		forest->Map[botanist->Coord_Y][botanist->Coord_X] = 'F';
		/* Recall print funciton */
		print_map(*forest);
		/* print coordinate */
		printf("\n I have found it on (%d,%d)!", botanist->Coord_X, botanist->Coord_Y);
	}
	
	/* Second base condition. the status of the botanist's water is finished. */ 
	else if(botanist->Water_Bottle_Size == 0)
	{
		printf("\nSearching...\n");
		/* Recall print funciton */
		print_map(*forest);
		/* print coordinate */
		printf("\nHelp! I am on (%d,%d)", botanist->Coord_X, botanist->Coord_Y);
	}
	
	else
	{
		int a=0, b=0, c=0, d=0, x;
		
	/* Determine the possibilities of motion that it can do. */
		
		/* Check if it can move to the right. If it can move to the right, the random movement may be to the right. */
		if((botanist->Coord_X+1 < forest->Width) && (forest->Map[botanist->Coord_Y][botanist->Coord_X+1] == ' ' || forest->Map[botanist->Coord_Y][botanist->Coord_X+1] == 'F'))
		{
			a=1;	/* random number can be 1 that mean can move right */
		}
		/* Check if it can move to the left. If it can move to the left, the random movement may be to the left. */
		if((botanist->Coord_X-1 >= 0) && (forest->Map[botanist->Coord_Y][botanist->Coord_X-1] == ' ' || forest->Map[botanist->Coord_Y][botanist->Coord_X-1] == 'F'))
		{
			b=2;	/* random number can be 2 that mean can move left */
		}
		/* Check if it can move to the down. If it can move to the down, the random movement may be to the down. */
		if((botanist->Coord_Y+1 < forest->Height) && (forest->Map[botanist->Coord_Y+1][botanist->Coord_X] == ' ' || forest->Map[botanist->Coord_Y+1][botanist->Coord_X] == 'F'))
		{
			c=3;	/* random number can be 3 that mean can move down */
		}
		/* Check if it can move to the up. If it can move to the up, the random movement may be to the up. */
		if((botanist->Coord_Y-1 >= 0) && (forest->Map[botanist->Coord_Y-1][botanist->Coord_X] == ' ' || forest->Map[botanist->Coord_Y-1][botanist->Coord_X] == 'F'))
		{
			d=4;	/* random number can be 4 that mean can move up */
		}
		
		do
		{
			x = (rand()%4)+1;		/* genarate random number between 1 and 4; */
									/* x can not be 0 */
			/* For example it can move just right or down , x can be 1 or 3 , x can not be 2 or 4. Other possibilities are like this. */
		}
		while(!(x == a || x == b || x == c || x == d));			/* x must be the transaction number of one of the possible move numbers. */
		
		switch(x)
		{
			case 1:
					/* Move right, Update map and rotation of Botanist. */
					forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
					forest->Map[botanist->Coord_Y][botanist->Coord_X+1] = 'B';
					botanist->Coord_X += 1;
					break;
					
			case 2:
					/* Move left, Update map and rotation of Botanist.  */
					forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
					forest->Map[botanist->Coord_Y][botanist->Coord_X-1] = 'B';
					botanist->Coord_X -= 1;
					break;
					
			case 3:
					/* Move down, Update map and rotation of Botanist.  */
					forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
					forest->Map[botanist->Coord_Y+1][botanist->Coord_X] = 'B';
					botanist->Coord_Y += 1;
					break;
					
			case 4:
					/* Move up, Update map and rotation of Botanist. */
					forest->Map[botanist->Coord_Y][botanist->Coord_X] = ' ';
					forest->Map[botanist->Coord_Y-1][botanist->Coord_X] = 'B';
					botanist->Coord_Y -= 1;
					break;
		}
		botanist->Water_Bottle_Size -= 1;			/* After the movement , water is reduced by 1 unit. */
		search(&(*forest), &(*botanist));			/* Recursion function. The motion will continue until it reach the end or until the water run out. */
	}
}
