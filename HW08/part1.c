/*****
		FURKAN ÖZEV
		161044036
					*****/


#include <stdio.h>
#include <stdlib.h>			/* The srand(); function was used. */
#include <time.h>

typedef enum{P, S, M, B, T, N} types;
/* P = Penalty , S = Snake , M = Stair , B = Boost , T = Trap , N = Normal */

typedef struct
{
	char text[10];
	int data;
	types type;
	int pos_x;
	int pos_y;
	int jump_x;
	int jump_y;
} block;

void initialize(block board[10][10]);
void print_board(block board[10][10]);
int move(block board[10][10], int x, int y, int counter);
void single_play(block board[10][10]);
void double_play(block board[10][10]);

int main()
{
	srand(time(NULL));
	block board[10][10];
	
	initialize(board);
	print_board(board);
	single_play(board);
	double_play(board);
	
}

void initialize(block board[10][10])
{
	/* The arr[0][0] point is the upper left corner of the table.
		The arr[9][9] point is the downer right corner of the table. */
	int x,y,temp;
	/* First, I fill all the blocks like a regular (normal) block. */
	/* The initializing started from the top of the table. */
	for(y = 0 ; y < 10 ; y++)
	{
		for(x = 0 ; x < 10 ; x++)
		{
			/* lines from left to right. */
			if(y % 2 == 0)
			{
				temp = (9-y)*10+x+1; 	/* Calculate data for the position */ 
				sprintf(board[y][x].text,"%d", temp);
				board[y][x].data = temp;
				board[y][x].type = N;
				board[y][x].pos_x = x;
				board[y][x].pos_y = y;
				board[y][x].jump_x = 0;
				board[y][x].jump_y = 0;
			}
			/* lines from right to left. */
			else
			{
				temp = (9-y)*10+x+1; 	/* Calculate data for the position */ 
				sprintf(board[y][9-x].text,"%d", temp);
				board[y][9-x].data = temp;
				board[y][9-x].type = N;
				board[y][9-x].pos_x = 9-x;
				board[y][9-x].pos_y = y;
				board[y][9-x].jump_x = 0;
				board[y][9-x].jump_y = 0;
			}
		}
	}
	
	/* Then replace the unusual (unnormal same P, B, S, T, M) blocks in the table. */
	
	for(y = 0 ; y < 10; y++)
	{
		for(x = 0 ; x < 10 ; x++)
		{
			if(x==1 && y==1)
			{
				sprintf(board[y][x].text,"M{94}");
				board[y][x].type = M;
				board[y][x].jump_x = 3;
				board[y][x].jump_y = 0;
			}
			else if(x==5 && y==2)
			{
				sprintf(board[y][x].text,"M{83}");
				board[y][x].type = M;
				board[y][x].jump_x = 7;
				board[y][x].jump_y = 1;
			}
			else if(x==1 && y==3)
			{
				sprintf(board[y][x].text,"M{77}");
				board[y][x].type = M;
				board[y][x].jump_x = 6;
				board[y][x].jump_y = 2;
			}
			else if(x==6 && y==4)
			{
				sprintf(board[y][x].text,"M{77}");
				board[y][x].type = M;
				board[y][x].jump_x = 6;
				board[y][x].jump_y = 2;
			}
			else if(x==1 && y==6)
			{
				sprintf(board[y][x].text,"M{52}");
				board[y][x].type = M;
				board[y][x].jump_x = 1;
				board[y][x].jump_y = 4;
			}
			else if(x==6 && y==8)
			{
				sprintf(board[y][x].text,"M{28}");
				board[y][x].type = M;
				board[y][x].jump_x = 2;
				board[y][x].jump_y = 7;
			}
			else if(x==3 && y==9)
			{
				sprintf(board[y][x].text,"M{11}");
				board[y][x].type = M;
				board[y][x].jump_x = 0;
				board[y][x].jump_y = 8;
			}
			else if(x==7 && y==0)
			{
				sprintf(board[y][x].text,"S{72}");
				board[y][x].type = S;
				board[y][x].jump_x = 1;
				board[y][x].jump_y = 2;
			}
			else if(x==8 && y==0)
			{
				sprintf(board[y][x].text,"S{56}");
				board[y][x].type = S;
				board[y][x].jump_x = 5;
				board[y][x].jump_y = 4;
			}
			else if(x==2 && y==2)
			{
				sprintf(board[y][x].text,"S{68}");
				board[y][x].type = S;
				board[y][x].jump_x = 2;
				board[y][x].jump_y = 3;
			}
			else if(x==7 && y==3)
			{
				sprintf(board[y][x].text,"S{52}");
				board[y][x].type = S;
				board[y][x].jump_x = 1;
				board[y][x].jump_y = 4;
			}
			else if(x==9 && y==4)
			{
				sprintf(board[y][x].text,"S{44}");
				board[y][x].type = S;
				board[y][x].jump_x = 6;
				board[y][x].jump_y = 5;
			}
			else if(x==5 && y==5)
			{
				sprintf(board[y][x].text,"S{22}");
				board[y][x].type = S;
				board[y][x].jump_x = 8;
				board[y][x].jump_y = 7;
			}
			else if(x==5 && y==7)
			{
				sprintf(board[y][x].text,"S{12}");
				board[y][x].type = S;
				board[y][x].jump_x = 1;
				board[y][x].jump_y = 8;
			}
			else if(x==4 && y==9)
			{
				sprintf(board[y][x].text,"S{1}");
				board[y][x].type = S;
				board[y][x].jump_x = 9;
				board[y][x].jump_y = 9;
			}
			else if(x==8 && y==1)
			{
				sprintf(board[y][x].text,"B");
				board[y][x].type = B;
				board[y][x].jump_x = 3;
				board[y][x].jump_y = 1;
			}
			else if(x==4 && y==3)
			{
				sprintf(board[y][x].text,"B");
				board[y][x].type = B;
				board[y][x].jump_x = 0;
				board[y][x].jump_y = 2;
			}
			else if(x==0 && y==5)
			{
				sprintf(board[y][x].text,"B");
				board[y][x].type = B;
				board[y][x].jump_x = 4;
				board[y][x].jump_y = 4;
			}
			else if(x==5 && y==6)
			{
				sprintf(board[y][x].text,"B");
				board[y][x].type = B;
				board[y][x].jump_x = 9;
				board[y][x].jump_y = 5;
			}
			else if(x==1 && y==7)
			{
				sprintf(board[y][x].text,"B");
				board[y][x].type = B;
				board[y][x].jump_x = 3;
				board[y][x].jump_y = 6;
			}
			else if(x==2 && y==0)
			{
				sprintf(board[y][x].text,"T");
				board[y][x].type = T;
				board[y][x].jump_x = 2;
				board[y][x].jump_y = 1;
			}
			else if(x==8 && y==2)
			{
				sprintf(board[y][x].text,"T");
				board[y][x].type = T;
				board[y][x].jump_x = 3;
				board[y][x].jump_y = 2;
			}
			else if(x==3 && y==4)
			{
				sprintf(board[y][x].text,"T");
				board[y][x].type = T;
				board[y][x].jump_x = 1;
				board[y][x].jump_y = 5;
			}
			else if(x==9 && y==6)
			{
				sprintf(board[y][x].text,"T");
				board[y][x].type = T;
				board[y][x].jump_x = 4;
				board[y][x].jump_y = 6;
			}
			else if(x==5 && y==1)
			{
				sprintf(board[y][x].text,"P");
				board[y][x].type = P;
				board[y][x].jump_x = 0;
				board[y][x].jump_y = 0;
			}
			else if(x==2 && y==5)
			{
				sprintf(board[y][x].text,"P");
				board[y][x].type = P;
				board[y][x].jump_x = 0;
				board[y][x].jump_y = 0;
			}
			else if(x==2 && y==8)
			{
				sprintf(board[y][x].text,"P");
				board[y][x].type = P;
				board[y][x].jump_x = 0;
				board[y][x].jump_y = 0;
			}
			else if(x==9 && y==0)
			{
				sprintf(board[y][x].text,"100(Finish)");
			}
			else if(x==9 && y==9)
			{
				sprintf(board[y][x].text,"1(Start)");
			}
		}
	} 
}

void print_board(block board[10][10])
{
	/* Applications have been made for the number of spaces between blocks. */
	int x,y,temp;
	printf("\n");
	for(y=0 ; y<10; y++)
	{
		printf("   ");
		for(x=0 ; x<10; x++)
		{
			printf("%s", board[y][x].text);
			if(board[y][x].type == N)
			{
				if(board[y][x].data > 9) printf("     ");
				else printf("      ");
			}
			else if(board[y][x].type == B || board[y][x].type == T || board[y][x].type == P)
			{
				printf("      ");
			}
			else if(board[y][x].type == M || board[y][x].type == S)
			{
				if(board[y][x].data > 9) printf("  ");
				else if(board[y][x].pos_x == 3 && board[y][x].pos_y == 9) printf("  ");
				else printf("   ");
			}
		}
		printf("\n\n");
	}	
}

void single_play(block board[10][10])
{
	int counter = 0;
	int x = 9, y = 9; /* Starting point */
	printf("\n-------------SINGLE PLAY-------------\n\n");
	counter = move(board,x,y,counter);
	printf("\n Total Move Counts: %d\n", counter);
}

void double_play(block board[10][10])
{
	int counter1 = 0, counter2 = 0; /* counter1 for player 1 and counter2 for player 2 */
	int x = 9, y = 9; /* Starting point */
	printf("\n-------------DOUBLE PLAY-------------\n");
	printf("\n   ///////////PLAYER 1///////////\n\n");
	counter1 = move(board,x,y,counter1);
	printf("\n Total Move Counts: %d\n\n", counter1);
	printf("\n   ///////////PLAYER 2///////////\n\n");
	counter2 = move(board,x,y,counter2);
	printf("\n Total Move Counts: %d\n\n", counter2);
	
	if(counter1 < counter2) printf("\n   ---> Winner is player 1 !!! <---\n");
	else if(counter1 > counter2) printf("\n   ---> Winner is player 2 !!! <---\n");
	else printf("\n   --> No winner !!! <---\n");
}

int move(block board[10][10], int x, int y, int counter)
{
	int dice, i, x_copy=x, y_copy=y, index = counter;
	dice = rand()%6+1;		/* Get random numbers between 1 and 6. */
	
	/* After the throw dice, the new position is determined. */
	for(i=0 ; i < dice; i++)
	{
		/* For lines from left to right. */
		if(board[y_copy][x_copy].pos_y % 2 != 0)
		{
			x_copy--;
			if(x_copy < 0)		/* For the next line pass. */
			{
				x_copy = 0;
				y_copy--;
			}
		}
		/* For lines from right to left. */
		else
		{
			x_copy++;
			if(x_copy > 9)		/* For the next line pass. */
			{
				x_copy = 9;
				y_copy--;
			}
		}
	}

	/* If the new position after the dice throwed is valid. */
	if(x_copy <= 9 && x_copy >= 0 && y_copy <= 9 && y_copy >= 0)
	{
		/* For B, T, S, M : Replace x and y with new position's jump_x and jump_y. */
		if(board[y_copy][x_copy].type == B || board[y_copy][x_copy].type == T || board[y_copy][x_copy].type == S || board[y_copy][x_copy].type == M)
		{
			x = board[y_copy][x_copy].jump_x;
			y = board[y_copy][x_copy].jump_y;
		}
		/* If block is normal type, Replace x and y with new position. */
		else if(board[y_copy][x_copy].type == N)
		{
			x = x_copy;
			y = y_copy;
		}
		/* If block is P doesn't make any move. Throw dice again. */
	}
	/* If it does not reach the end, the dice will be thrown again. */
	if(board[y][x].data != 100)
	{
		counter = move(board,x,y,counter+1);	 /* RECURSIVE */
	}
	else
	{
		counter++;
	}
	/* Printing data and dice */
	printf("%4d)  Dice: %d \t    New-Data: %d\n",index+1, dice, board[y][x].data);
	if(index == 0) printf("   Starting Point   Data : 1\n");
	return counter;
}
