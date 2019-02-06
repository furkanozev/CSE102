/***
	FURKAN ÖZEV
			161044036
					***/


#include <stdio.h>
typedef enum {white_man, black_man, white_king, black_king, empty} piece;

typedef enum {white = 10, black = 20} player;

void init_board(piece board[][8])
{
	/* 1. 4. 5. 8. lines are empty, 2. ve 3. lines are black stone, 6. and 7. lines are reserved for white stone. */
	int i,j;
	for(i = 0 ; i < 8 ; i++)
	{
		for(j = 0 ; j < 8 ; j++)
		{
			if(i == 0 || i == 3 || i == 4 || i == 7)
			{
				board[i][j] = empty;
			}
			else if(i == 1 || i == 2)
			{
				board[i][j] = black_man;	
			}
			else if(i == 5 || i == 6)
			{
				board[i][j] = white_man;
			}	
		}	
	} 
}

void display_board(piece board[][8])
{
	/*	white_man => w		black_man => b		white_king => W		black_king => B		empty => -	*/
	int i,j;
	printf("\n\n");
	for( i = 0 ; i < 8 ; i++)
	{
		for( j = 0 ; j < 8 ; j++)
		{
			if(board[i][j] == white_man) printf("w");
			else if(board[i][j] == black_man) printf("b");
			else if(board[i][j] == white_king) printf("W");
			else if(board[i][j] == black_king) printf("B");
			else if(board[i][j] == empty) printf("-");
		}
		printf("\n");
	}
}

int check_end_of_game(piece board[][8])
{
	/* The player who has no stones to move will lose it. The player of the stones remaining on the board wins. */
	player winner;
	int i,j,white_count=0,black_count=0;
	for( i = 0 ; i < 8 ; i++)
	{
		for( j = 0 ; j < 8 ; j++)
		{
			if(board[i][j] == white_man || board[i][j] == white_king)
			{
				white_count++;
			}
			else if(board[i][j] == black_man || board[i][j] == black_king)
			{
				black_count++;
			}
		}
	}
	if(white_count != 0 && black_count != 0)
	{
		return -1;				/* The game continues. */
	}
	else
	{
		if(white_count == 0)		/* Winner is black */
		{
			winner = black;
		}
		else						/* Winner is white */
		{
			winner = white;
		}
	}
	return winner;
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p)
{
	if(p==10) printf("\nPlayer is White");			/* who is the player */
	else if(p==20) printf("\nPlayer is Black");
	printf("\nFrom_x = %d    from_y = %d    to_x = %d   to_y = %d",from_x,from_y,to_x,to_y);			/* movements */
	
	int n=0,i,flag=0;
	/* n is the number of stones to be eaten.*/
	/* I subtracted 1 to easily use values in the array. */
	from_x -= 1, from_y -=1, to_x -=1, to_y -=1;

	/*I checked whether or not the player move his own stone.*/
	if( (p == white && (board[from_x][from_y] == black_man || board[from_x][from_y] == black_king)) || (p == black && (board[from_x][from_y] == white_man || board[from_x][from_y] == white_king)) )
	{
		return -1;
	}
	
	/* The point of choice must not be empty, it must be its own stone, and the point where the stone moves must be empty. */
	if(board[from_x][from_y] == empty || board[to_x][to_y] != empty)
	{
		return -2;
	}
	
	/* The stone can not move diagonally. */
	if(to_x - from_x != 0 && to_y - from_y != 0)
	{
		return -2;
	}
	
	/* the player can not choose another point on the 8x8 board. */
	if(from_x < 0 || from_x > 7 || from_y < 0 || from_y > 7 || to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7)
	{
		return -2;
	}
	
	/* Motion rules of normal stones: */
	if(board[from_x][from_y] == white_man || board[from_x][from_y] == black_man)
	{
		/* Move of white stones */
		if( p == white )
		{
			/* the white stones do not go back so these stone can not go down. */
			if(to_x - from_x > 0)
			{
				return -2;
			}
			
			/* Obligation to eat stone */
			/* If there is a stone to be eaten, the player must eat the stone. If there is a black stone in the next part and the back part of the black stone is empty, there is a stone that can be eaten. */
			if(((board[from_x][from_y+1] == black_man || board[from_x][from_y+1] == black_king) && board[from_x][from_y+2] == empty && from_y+2 <= 7) || ((board[from_x][from_y-1] == black_man || board[from_x][from_y-1] == black_king) && board[from_x][from_y-2] == empty && from_y-2 >= 0) || ((board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king) && board[from_x-2][from_y] == empty && from_x-2 >= 0))
			{
				/* The player must make the right move and eat the stone. */
				if(from_x - to_x == 2 || from_y - to_y == 2 || from_y - to_y == - 2)
				{
					/* check to whether or not player eat rocks. */
					if(board[(from_x + to_x)/2][(from_y+to_y)/2] == black_man || board[(from_x + to_x)/2][(from_y+to_y)/2] == black_king)
					{
						board[to_x][to_y] = board[from_x][from_y];				/* stone moved to new location */
						board[from_x][from_y] = empty;							/* the first part where the stone was found was reset. */
						board[(from_x + to_x)/2][(from_y+to_y)/2] = empty; 		/* the part where the eaten stone was found was reset. */
						from_x = to_x;
						from_y = to_y;
						n++;
					}
					else return -2;				/* wrong move was made / the player did not eat stone when he could. */
				}
				else return -2;					/* wrong move was made / He tried to move more than 2 steps.*/
			}
			
			/* there is not a stone to be eaten. the player can only change the location of the piece by 1 part. */
			else if(from_x - to_x == 1 || from_y - to_y == 1 || from_y - to_y == -1)
			{
				board[to_x][to_y] = board[from_x][from_y];		/* stone moved to new location */
				board[from_x][from_y] = empty;					/* the first part where the stone was found was reset. */
				from_x = to_x;
				from_y = to_y;
				flag = -1;				/* It should not check if there are any rocks to be eaten. */
			}
			else
			{
				return -2;				/* wrong move was made / He tried to move more than 1 step.*/
			}
			
			/* Being King */
			/* Being a king. If the stone comes to any one place in the 1st row, it becomes a king. */
			if(from_x == 0)
			{
				board[from_x][from_y] = white_king;
				flag = -1;
				printf("\n141\n");
			}
			
			/* Automation stone eating */
			/* It checks whether or not there are rocks to be eaten. */
			while(flag != -1)
			{
				/* It checks the right, left, and front to see if there are any stones that can be eaten. */
				flag = -1; /* If there is no stone to eat, it comes out of the loop. */
				if((board[from_x][from_y+1] == black_man || board[from_x][from_y+1] == black_king) && board[from_x][from_y+2] == empty && from_y+2 <= 7)
				{	/* For the stone on the right. */
					board[from_x][from_y+2] = board[from_x][from_y];		/* stone moved to new location */
					board[from_x][from_y] = empty;							/* the first part where the stone was found was reset. */
					board[from_x][from_y+1] = empty;						/* the part where the eaten stone was found was reset. */
					from_y += 2;
					n++;													/* the number of stones eated has been increased. */
					flag = 0;
				}
				if((board[from_x][from_y-1] == black_man || board[from_x][from_y-1] == black_king) && board[from_x][from_y-2] == empty && from_y-2 >= 0 )
				{	/* For the stone on the left. */
					board[from_x][from_y-2] = board[from_x][from_y];		/* stone moved to new location */
					board[from_x][from_y] = empty;							/* the first part where the stone was found was reset. */
					board[from_x][from_y-1] = empty;						/* the part where the eaten stone was found was reset. */
					from_y -= 2;
					n++;													/* the number of stones eated has been increased. */
					flag = 0;	
				}
				if((board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king) && board[from_x-2][from_y] == empty && from_x-2 >= 0)
				{	/* For the stone on the down. */
					board[from_x-2][from_y] = board[from_x][from_y];		/* stone moved to new location */
					board[from_x][from_y] = empty;							/* the first part where the stone was found was reset. */
					board[from_x-1][from_y] = empty;						/* the part where the eaten stone was found was reset. */
					from_x -= 2;
					n++;													/* the number of stones eated has been increased. */
					flag = 0;
				}	
			}
			
			/* Being King */
			/* After eating stones can be the king. If the stone comes to any one place in the 1st row, it becomes a king. */
			if(from_x == 0)
			{
				board[from_x][from_y] = white_king;
			}
		}
		
		/* Move of black stones */
		else if( p == black )
		{
			/* the black stones do not go back so these stone can not go up. */
			if(from_x - to_x > 0)
			{
				return -2;
			}
			
			/* Obligation to eat stone */
			/* If there is a stone to be eaten, the player must eat the stone. If there is a white stone in the next part and the back part of the white stone is empty, there is a stone that can be eaten. */
			if(((board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king) && board[from_x][from_y+2] == empty) || ((board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king) && board[from_x][from_y-2] == empty) || ((board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king) && board[from_x+2][from_y] == empty))
			{
				/* The player must make the right move and eat the stone. */
				if(from_x - to_x == -2 || from_y - to_y == 2 || from_y - to_y == -2)
				{
					/* check to whether or not player eat rocks. */
					if(board[(from_x + to_x)/2][(from_y+to_y)/2] == white_man || board[(from_x + to_x)/2][(from_y+to_y)/2] == white_king)
					{
						board[to_x][to_y] = board[from_x][from_y];						/* stone moved to new location */
						board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
						board[(from_x + to_x)/2][(from_y+to_y)/2] = empty;				/* the part where the eaten stone was found was reset. */
						from_x = to_x;
						from_y = to_y;
						n++;
					}
					else return -2;					/* wrong move was made / the player did not eat stone when he could.*/
				}
				else return -2;						/* wrong move was made / He tried to move more than 2 steps. */
			}
			
			/* there is not a stone to be eaten. the player can only change the location of the piece by 1 part. */
			else if(from_x - to_x == -1 || from_y - to_y == 1 || from_y - to_y == -1)
			{
				board[to_x][to_y] = board[from_x][from_y];						/* stone moved to new location */
				board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
				from_x = to_x;
				from_y = to_y;
				flag = -1;														/* It should not check if there are any rocks to be eaten. */
			}
			else
			{
				return -2;				/* wrong move was made / He tried to move more than 1 step. */
			}
			
			/* Being King */
			/* Being a king. If the stone comes to any one place in the 8th row, it becomes a king. */
			if(from_x == 7)
			{
				board[from_x][from_y] = black_king;
				flag = -1;
			}
			
			/* Automation stone eating */
			/* It checks whether or not there are rocks to be eaten. */
			while(flag != -1)
			{
				/* It checks the right, left, and front to see if there are any stones that can be eaten. */
				flag = -1;		/* If there is no stone to eat, it comes out of the loop. */
				if((board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king) && board[from_x][from_y+2] == empty && from_y+2 <= 7 )
				{	/* For the stone on the right. */
					board[from_x][from_y+2] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					board[from_x][from_y+1] = empty;							/* the part where the eaten stone was found was reset. */
					from_y += 2;
					n++;
					flag = 0;
				}
				if((board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king) && board[from_x][from_y-2] == empty && from_y-2 >= 0)
				{	/* For the stone on the left. */
					board[from_x][from_y-2] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					board[from_x][from_y-1] = empty;							/* the part where the eaten stone was found was reset. */
					from_y -= 2;
					n++;
					flag = 0;	
				}
				if((board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king) && board[from_x+2][from_y] == empty && from_x+2 <= 7)
				{	/* For the stone on the up. */
					board[from_x+2][from_y] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					board[from_x+1][from_y] = empty;							/* the part where the eaten stone was found was reset. */
					from_x += 2;
					n++;
					flag = 0;
				}	
			}
			
			/* Being King */
			/* After eating stones can be the king. If the stone comes to any one place in the 8th row, it becomes a king. */
			if(from_x == 7)
			{
				board[from_x][from_y] = black_king;
			}	
		}
	}
	
	/* Rules of movements of the kingdoms : */
	else if(board[from_x][from_y] == white_king || board[from_x][from_y] == black_king)
	{
		if(to_y - from_y > 0)
		{	/* If it is moving to the right. */
			while(from_y < to_y)			/* Check until the entered position is reached. */
			{
				/* It checks whether there is any stone up to the location where it will move. */
				for(i = 1; from_y+i < to_y && board[from_x][from_y+i] == empty; i++);
				
				/* If there is not a stone to eat change the location so make move. */
				if(from_y+i == to_y)
				{
					board[from_x][from_y+i] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					from_y = to_y;
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i+1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i+1] == empty)) && from_y+i+1 <= 7)
				{
					board[from_x][from_y+i+1] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y+i] = empty;							/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					from_y = from_y+i+1;
					n++;
				}	
				else return -2;													/* wrong move was made */
			}
		}
		else if(to_y - from_y < 0)
		{	/* If it is moving to the left. */
			while(from_y > to_y)			/* Check until the entered position is reached. */
			{
				/* It checks whether there is any stone up to the location where it will move. */
				for(i = -1; from_y+i > to_y && board[from_x][from_y+i] == 4; i--);
				
				/* If there is not a stone to eat change the location so make move. */
				if(from_y+i == to_y)
				{
					board[from_x][from_y+i] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					from_x = to_x;
					from_y = to_y;
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i-1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i-1] == empty)) && from_y+i-1 >= 0)
				{
					board[from_x][from_y+i-1] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y+i] = empty;							/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					from_y = from_y+i-1;
					n++;
				}
				else return -2;													/* wrong move was made */
			}
		}
		else if(to_x - from_x > 0)
		{	/* If it is moving to the up. */
			while(from_x < to_x)			/* Check until the entered position is reached. */
			{
				/* It checks whether there is any stone up to the location where it will move. */
				for(i = 1; from_x+i < to_x && board[from_x+i][from_y] == empty; i++);
				
				/* If there is not a stone to eat change the location so make move. */
				if(from_x+i == to_x)
				{
					board[from_x+i][from_y] = board[from_x][from_y];				/* stone moved to new location */
					board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
					from_x = to_x;
					from_y = to_y;
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i+1][from_y] == empty) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i+1][from_y] == empty)) && from_x+i+1 <= 7)
				{
					board[from_x+i+1][from_y] = board[from_x][from_y];				/* stone moved to new location */
					board[from_x+i][from_y] = empty;								/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
					from_x = from_x+i+1;
					n++;
				}
				else return -2;														/* wrong move was made */
			}
		}
		else if(to_x - from_x < 0)
		{	/* If it is moving to the down. */
			while(from_x > to_x)
			{								/* Check until the entered position is reached. */
			
				/* It checks whether there is any stone up to the location where it will move. */
				for(i = -1; from_x+i > to_x && board[from_x+i][from_y] == empty; i--);
				
				/* If there is not a stone to eat change the location so make move. */
				if(from_x+i == to_x)
				{
					board[from_x+i][from_y] = board[from_x][from_y];				/* stone moved to new location */
					board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
					from_x = to_x;
					from_y = to_y;
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i-1][from_y] == empty) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i-1][from_y] == empty)) && from_x+i-1 >= 0)
				{
					board[from_x+i-1][from_y] = board[from_x][from_y];				/* stone moved to new location */
					board[from_x+i][from_y] = empty;								/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
					from_x = from_x+i-1;
					n++;
				}
				else return -2;														/* wrong move was made */
			}
		}
		
		/* It checks whether or not there are rocks to be eaten for kings. */
		while(flag != -1)
		{
			flag = -1;
			/* It checks the right, left, back, and front to see if there are any stones that can be eaten. */
			
			/* It checks to the up until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
			for(i=1; board[from_x+i][from_y] == empty && from_x+i <= 7; i++);
			if(((p == white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i+1][from_y] == empty ) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i+1][from_y] == empty)) && from_x+i+1 <= 7 )
			{
				board[from_x+i][from_y] = empty;										/* the part where the eaten stone was found was reset. */
				board[from_x+i+1][from_y] = board[from_x][from_y];						/* stone moved to new location */
				board[from_x][from_y] = empty;											/* the first part where the stone was found was reset. */
				from_x = from_x+i+1;
				n++;
				flag=0;
			}
			
			/* It checks to the down until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
			for(i=-1; board[from_x+i][from_y] == empty && from_x+i >= 0; i--);
			if(((p==white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i-1][from_y] == empty) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i-1][from_y] == empty))&& from_x+i-1 >= 0)
			{
				board[from_x+i][from_y] = empty;										/* the part where the eaten stone was found was reset. */
				board[from_x+i-1][from_y] = board[from_x][from_y];						/* stone moved to new location */
				board[from_x][from_y] = empty;											/* the first part where the stone was found was reset. */
				from_x = from_x+i-1;
				n++;
				flag=0;
			}
			
			/* It checks to the right until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
			for(i=1; board[from_x][from_y+i] == empty && from_y+i <= 7; i++);
			if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i+1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i+1] == empty)) && from_y+i+1 <= 7)
			{
				board[from_x][from_y+i] = empty;										/* the part where the eaten stone was found was reset. */
				board[from_x][from_y+i+1] = board[from_x][from_y];						/* stone moved to new location */
				board[from_x][from_y] = empty;											/* the first part where the stone was found was reset. */
				from_y = from_y+i+1;
				n++;
				flag=0;
			}
			
			/* It checks to the left until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
			for(i=-1; board[from_x][from_y+i] == empty && from_y+i >= 0; i--);
			if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i-1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i-1] == empty)) && from_y+i-1 >= 0)
			{
				board[from_x][from_y+i] = empty;										/* the part where the eaten stone was found was reset. */
				board[from_x][from_y+i-1] = board[from_x][from_y];						/* stone moved to new location */
				board[from_x][from_y] = empty;											/* the first part where the stone was found was reset. */
				from_y = from_y+i-1;
				n++;
				flag=0;
			}
		}	
	}
	printf("\n%d opponent pieces have been eaten.", n);			/* how many stones he ate */
	if(n != 0)	printf("\nAfter eat pieces or stones\t End position x: %d    End position y: %d", from_x+1, from_y+1);			/* new location after auto-eat stones */
	return n;							/* total number of eaten stones */
}


void sample_game_1()
{
	/* My sample game Black is winner */
	player p;
	piece board[8][8];
	
	init_board(board);			/* initilaze and after display */
	display_board(board);
	
	/* Movements */
	move(board, 3, 3, 4, 3, black);
	display_board(board);
	
	move(board, 6, 5, 5, 5, white);
	display_board(board);
	
	move(board, 3, 5, 4, 5, black);
	display_board(board);
	
	move(board, 5, 5, 3, 5, white);
	display_board(board);
	
	move(board, 2, 2, 2, 3, black);
	display_board(board);
	
	move(board, 6, 8, 5, 8, white);
	display_board(board);
	
	move(board, 3, 1, 4, 1, black);
	display_board(board);
	
	move(board, 1, 3, 3, 3, white);
	display_board(board);
	
	move(board, 3, 8, 4, 8, black);
	display_board(board);
	
	move(board, 5, 3, 5, 1, white);
	display_board(board);
	
	move(board, 4, 8, 6, 8, black);
	display_board(board);
	
	move(board, 5, 1, 3, 1, white);
	display_board(board);
	
	move(board, 2, 4, 3, 4, black);
	display_board(board);
	
	move(board, 6, 3, 5, 3, white);
	display_board(board);
	
	move(board, 8, 8, 8, 6, black);
	display_board(board);
	
	move(board, 6, 6, 5, 6, white);
	display_board(board);
	
	move(board, 8, 6, 6, 6, black);
	display_board(board);
	
	move(board, 1, 1, 1, 2, white);
	display_board(board);
	
	move(board, 3, 6, 3, 5, black);
	display_board(board);
	
	move(board, 1, 2, 4, 2, white);
	display_board(board);
	
	move(board, 3, 7, 5, 7, black);
	display_board(board);
	
	move(board, 5, 3, 4, 3, white);
	display_board(board);
	
	move(board, 5, 7, 5, 8, black);
	display_board(board);
	
	move(board, 6, 1, 5, 1, white);
	display_board(board);
	
	move(board, 5, 8, 6, 8, black);
	display_board(board);
	
	move(board, 4, 3, 4, 2, white);
	display_board(board);
	
	move(board, 2, 8, 3, 8, black);
	display_board(board);
	
	move(board, 6, 7, 6, 6, white);
	display_board(board);
	
	move(board, 6, 8, 6, 7, black);
	display_board(board);
	
	move(board, 7, 5, 7, 6, white);
	display_board(board);
	
	move(board, 6, 7, 6, 5, black);
	display_board(board);
	
	move(board, 7, 7, 6, 7, white);
	display_board(board);
	
	move(board, 8, 3, 8, 1, black);
	display_board(board);
	
	move(board, 6, 7, 6, 8, white);
	display_board(board);
	
	move(board, 8, 1, 6, 1, black);
	display_board(board);
	
	move(board, 6, 2, 5, 2, white);
	display_board(board);
	
	move(board, 4, 3, 4, 2, black);
	display_board(board);
	
	move(board, 6, 8, 5, 8, white);
	display_board(board);
	
	move(board, 4, 2, 6, 2, black);
	display_board(board);
	
	move(board, 5, 8, 5, 7, white);
	display_board(board);
	
	move(board, 8, 2, 7, 2, black);
	display_board(board);
	
	move(board, 5, 7, 4, 7, white);
	display_board(board);
	
	move(board, 7, 2, 7, 5, black);
	display_board(board);
	
	/* Checking game */
	if(check_end_of_game(board) == white)	printf("\n Winner is White");
	else if(check_end_of_game(board) == black)	printf("\n Winner is Black");
	else printf("\n No Winner!");
	
}
void sample_game_2()
{
	/* The example given in Gif is the same code exacuting. */
	player p;
	/* initilaze same gif */
	piece board[8][8]={{4,4,4,4,4,4,4,4},{4,4,1,1,1,1,4,4},{4,1,1,1,1,4,1,1},{1,1,1,4,4,1,4,1},{4,4,0,0,0,1,0,0},{0,0,0,0,0,4,0,0},{4,4,0,0,0,0,4,4},{4,4,4,4,4,4,4,4}};
	display_board(board);
	
	/* Movements in gif */
	move(board, 6, 2, 5, 2, white);
	display_board(board);
	
	move(board, 4, 2, 6, 2, black);
	display_board(board);
	
	move(board, 5, 4, 4, 4, white);
	display_board(board);
	
	move(board, 5, 6, 5, 4, black);
	display_board(board);
	
	move(board, 4, 4, 4, 2, white);
	display_board(board);
	
	move(board, 2, 3, 2, 1, black);
	display_board(board);
	
	move(board, 6, 4, 5, 4, white);
	display_board(board);
	
	move(board, 6, 2, 6, 4, black);
	display_board(board);
	
	move(board, 5, 4, 4, 4, white);
	display_board(board);
	
	move(board, 3, 4, 5, 4, black);
	display_board(board);
	
	move(board, 6, 7, 6, 6, white);
	display_board(board);
	
	move(board, 8, 6, 5, 6, black);
	display_board(board);
	
	move(board, 5, 7, 5, 5, white);
	display_board(board);
	
	/* Checking game */
	if(check_end_of_game(board) == white)	printf("\n Winner is White");
	else if(check_end_of_game(board) == black)	printf("\n Winner is Black");
	else printf("\n No Winner!");
}

/* If you want to test the code, you can test it by using double_play function. */
void double_play()
{
	player p;
	piece board[8][8];
	int from_x, from_y, to_x, to_y , i=1, result=0,check;
	
	init_board(board);		/* initilaze after display */
	display_board(board);
	
	while(result != 10 && result != 20)
	{
		if(i%2 == 0) { printf("\nPlayer is White"); p = 10; }		/* who is the player */
		else { printf("\nPlayer is Black"); p = 20; }
		
		printf("\nFrom_x from_y: ");
		scanf("%d%d",&from_x,&from_y);
		
		printf("\nTo_x to_y: ");
		scanf("%d%d",&to_x,&to_y);
		
		check = move(board, from_x, from_y, to_x, to_y, p);
		display_board(board);
		
		result = check_end_of_game(board);
		if(check >= 0)i++;
	} 
}

int main()
{
	sample_game_1();
	sample_game_2();
	return 0;
}
