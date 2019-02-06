/***
	FURKAN ÖZEV
			161044036
					***/

/* Recursive functions are used. */


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
	if(winner == white)	printf("\n Winner is White");
	else if(winner == black)	printf("\n Winner is Black");
	return winner;
}

int max_white(piece board[][8], int from_x, int from_y, int n)		/* Recursive function */
{
	/* White stones can move to the right, left, and up. So I made 3 copies: 
		Create 3 copies of the first version of the board. 
		I created 3 copies of from_x, from_y, and n (number of stones to be eaten) in the same way.
		I then call the function again for each direction and hold the number of stones it eat in different variables.
		I find the situation that eat the most stones and apply it. */
	int i,j,x;
	piece board_c1[8][8], board_c2[8][8], board_c3[8][8];
	int from_x_c1 = from_x, from_x_c2 = from_x, from_x_c3 = from_x, from_y_c1 = from_y, from_y_c2 = from_y, from_y_c3 = from_y;
	int n1=n, n2=n, n3=n; 
	for(i=0 ; i < 8 ; i++)
	{
		for(j=0 ; j < 8; j++)
		{
			board_c1[i][j] = board[i][j];
			board_c2[i][j] = board[i][j];
			board_c3[i][j] = board[i][j];
		}
	}
	
	if((board_c1[from_x_c1][from_y_c1+1] == black_man || board_c1[from_x_c1][from_y_c1+1] == black_king) && board_c1[from_x_c1][from_y_c1+2] == empty && from_y_c1+2 <= 7)
	{	/* For the stone on the right. */
		board_c1[from_x_c1][from_y_c1+2] = board_c1[from_x_c1][from_y_c1];		/* stone moved to new location */
		board_c1[from_x_c1][from_y_c1] = empty;									/* the first part where the stone was found was reset. */
		board_c1[from_x_c1][from_y_c1+1] = empty;								/* the part where the eaten stone was found was reset. */
		from_y_c1 += 2;															/* Change new location. */
		n1++;																	/* the number of stones eated has been increased. */
		n1 = max_white(board_c1, from_x_c1, from_y_c1, n1);						/* Recall function again for the next movements after this movement. */
	}
	if((board_c2[from_x_c2][from_y_c2-1] == black_man || board_c2[from_x_c2][from_y_c2-1] == black_king) && board_c2[from_x_c2][from_y_c2-2] == empty && from_y_c2-2 >= 0 )
	{	/* For the stone on the left. */
		board_c2[from_x_c2][from_y_c2-2] = board_c2[from_x_c2][from_y_c2];		/* stone moved to new location */
		board_c2[from_x_c2][from_y_c2] = empty;									/* the first part where the stone was found was reset. */
		board_c2[from_x_c2][from_y_c2-1] = empty;								/* the part where the eaten stone was found was reset. */
		from_y_c2 -= 2;															/* Change new location. */
		n2++;																	/* the number of stones eated has been increased. */
		n2 = max_white(board_c2, from_x_c2, from_y_c2, n2);						/* Recall function again for the next movements after this movement. */	
	}
	if((board_c3[from_x_c3-1][from_y_c3] == black_man || board_c3[from_x_c3-1][from_y_c3] == black_king) && board_c3[from_x_c3-2][from_y_c3] == empty && from_x_c3-2 >= 0)
	{	/* For the stone on the down. */
		board_c3[from_x_c3-2][from_y_c3] = board_c3[from_x_c3][from_y_c3];		/* stone moved to new location */
		board_c3[from_x_c3][from_y_c3] = empty;									/* the first part where the stone was found was reset. */
		board_c3[from_x_c3-1][from_y_c3] = empty;								/* the part where the eaten stone was found was reset. */
		from_x_c3 -= 2;															/* Change new location. */
		n3++;																	/* the number of stones eated has been increased. */
		n3 = max_white(board_c3, from_x_c3, from_y_c3, n3);						/* Recall function again for the next movements after this movement. */	
	}
	
	/* By checking all the possibilities we found the most stone-eating situation.
		We apply what we find. */
		
	if(n1 >= n2 && n1 >= n3)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c1[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c1;
		from_y = from_y_c1;
		x = n1;
	}
	else if(n2 >= n1 && n2 >= n3)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c2[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c2;
		from_y = from_y_c2;
		x = n2;
	}
	else if(n3 >= n1 && n3 >= n2)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c3[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c3;
		from_y = from_y_c3;
		x = n3;
	}
	/* Being White King */
	if(from_x == 0)
	{
		board[from_x][from_y] = white_king;
	}
	return x; 		
}

int max_black(piece board[][8], int from_x, int from_y, int n)		/* Recursive function */
{
	/* Black stones can move to the right, left, and down. So I made 3 copies: 
	Create 3 copies of the first version of the board. 
	I created 3 copies of from_x, from_y, and n (number of stones to be eaten) in the same way.
	I then call the function again for each direction and hold the number of stones it eat in different variables.
	I find the situation that eat the most stones and apply it. */
	int i,j,x;
	piece board_c1[8][8], board_c2[8][8], board_c3[8][8];
	int from_x_c1 = from_x, from_x_c2 = from_x, from_x_c3 = from_x, from_y_c1 = from_y, from_y_c2 = from_y, from_y_c3 = from_y;
	int n1=n, n2=n, n3=n; 
	for(i=0 ; i < 8 ; i++)
	{
		for(j=0 ; j < 8; j++)
		{
			board_c1[i][j] = board[i][j];
			board_c2[i][j] = board[i][j];
			board_c3[i][j] = board[i][j];
		}
	}
	if((board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king) && board[from_x][from_y+2] == empty && from_y+2 <= 7 )
	{	/* For the stone on the right. */
		board_c1[from_x_c1][from_y_c1+2] = board_c1[from_x_c1][from_y_c1];		/* stone moved to new location */
		board_c1[from_x_c1][from_y_c1] = empty;									/* the first part where the stone was found was reset. */
		board_c1[from_x_c1][from_y_c1+1] = empty;								/* the part where the eaten stone was found was reset. */
		from_y_c1 += 2;															/* Change new location. */
		n1++;																	/* the number of stones eated has been increased. */
		n1 = max_black(board_c1, from_x_c1, from_y_c1, n1);						/* Recall function again for the next movements after this movement. */
	}
	if((board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king) && board[from_x][from_y-2] == empty && from_y-2 >= 0)
	{	/* For the stone on the left. */
		board_c2[from_x_c2][from_y_c2-2] = board_c2[from_x_c2][from_y_c2];		/* stone moved to new location */
		board_c2[from_x_c2][from_y_c2] = empty;									/* the first part where the stone was found was reset. */
		board_c2[from_x_c2][from_y_c2-1] = empty;								/* the part where the eaten stone was found was reset. */
		from_y_c2 -= 2;															/* Change new location. */
		n2++;																	/* the number of stones eated has been increased. */
		n2 = max_black(board_c2, from_x_c2, from_y_c2, n2);						/* Recall function again for the next movements after this movement. */
	}
	if((board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king) && board[from_x+2][from_y] == empty && from_x+2 <= 7)
	{	/* For the stone on the down. */
		board_c3[from_x_c3+2][from_y_c3] = board_c3[from_x_c3][from_y_c3];		/* stone moved to new location */
		board_c3[from_x_c3][from_y_c3] = empty;									/* the first part where the stone was found was reset. */
		board_c3[from_x_c3+1][from_y_c3] = empty;								/* the part where the eaten stone was found was reset. */
		from_x_c3 += 2;															/* Change new location. */
		n3++;																	/* the number of stones eated has been increased. */
		n3 = max_black(board_c3, from_x_c3, from_y_c3, n3);						/* Recall function again for the next movements after this movement. */
	}
	
	/* By checking all the possibilities we found the most stone-eating situation.
	We apply what we find. */
		
	if(n1 >= n2 && n1 >= n3)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c1[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c1;
		from_y = from_y_c1;
		x = n1;
	}
	else if(n2 >= n1 && n2 >= n3)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c2[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c1;
		from_y = from_y_c1;
		x = n2;
	}
	else if(n3 >= n1 && n3 >= n2)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c3[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c1;
		from_y = from_y_c1;
		x = n3;
	}
	/* Being Black King */
	if(from_x == 7)
	{
		board[from_x][from_y] = black_king;
	}
	return x; 		
}

int max_king(piece board[8][8], int from_x, int from_y, int n, player p)		/* Recursive function */
{
	/* King stones can move to the right, left, up and down. So I made 4 copies: 
	Create 4 copies of the first version of the board. 
	I created 4 copies of from_x, from_y, and n (number of stones to be eaten) in the same way.
	I then call the function again for each direction and hold the number of stones it eat in different variables.
	I find the situation that eat the most stones and apply it. */
	
	int i,j,x;
	piece board_c1[8][8], board_c2[8][8], board_c3[8][8], board_c4[8][8];
	int from_x_c1 = from_x, from_x_c2 = from_x, from_x_c3 = from_x, from_x_c4 = from_x, from_y_c1 = from_y, from_y_c2 = from_y, from_y_c3 = from_y, from_y_c4 = from_y;
	int n1=n, n2=n, n3=n, n4=n; 
	for(i=0 ; i < 8 ; i++)
	{
		for(j=0 ; j < 8; j++)
		{
			board_c1[i][j] = board[i][j];
			board_c2[i][j] = board[i][j];
			board_c3[i][j] = board[i][j];
		}
	}
	
	/* Move downward until it coincides with any stones. */
	for(i=1; board[from_x+i][from_y] == empty && from_x+i <= 7; i++);
	if(((p == white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i+1][from_y] == empty ) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i+1][from_y] == empty)) && from_x+i+1 <= 7 )
	{
		/* If the stone is going to be eaten, it will. */
		board_c1[from_x_c1+i][from_y_c1] = empty;													/* the part where the eaten stone was found was reset. */
		board_c1[from_x_c1+i+1][from_y_c1] = board_c1[from_x_c1][from_y_c1];						/* stone moved to new location */
		board_c1[from_x_c1][from_y_c1] = empty;														/* the first part where the stone was found was reset. */
		from_x_c1 = from_x_c1+i+1;																	/* Change new location. */
		n1++;																						/* the number of stones eated has been increased. */
		n1 = max_king(board_c1, from_x_c1, from_y_c1, n1, p);										/* Recall function again for the next movements after this movement. */
	}
	
	/* It checks to the up until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
	for(i=-1; board[from_x+i][from_y] == empty && from_x+i >= 0; i--);
	if(((p==white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i-1][from_y] == empty) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i-1][from_y] == empty))&& from_x+i-1 >= 0)
	{
		/* If the stone is going to be eaten, it will. */
		board_c2[from_x_c2+i][from_y_c2] = empty;													/* the part where the eaten stone was found was reset. */
		board_c2[from_x_c2+i-1][from_y_c2] = board_c2[from_x_c2][from_y_c2];						/* stone moved to new location */
		board_c2[from_x_c2][from_y_c2] = empty;														/* the first part where the stone was found was reset. */
		from_x_c2 = from_x_c2+i-1;																	/* Change new location. */
		n2++;																						/* the number of stones eated has been increased. */
		n2 = max_king(board_c2, from_x_c2, from_y_c2, n2, p);										/* Recall function again for the next movements after this movement. */
	}
	
	/* It checks to the right until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
	for(i=1; board[from_x][from_y+i] == empty && from_y+i <= 7; i++);
	if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i+1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i+1] == empty)) && from_y+i+1 <= 7)
	{
		/* If the stone is going to be eaten, it will. */
		board_c3[from_x_c3][from_y_c3+i] = empty;													/* the part where the eaten stone was found was reset. */
		board_c3[from_x_c3][from_y_c3+i+1] = board_c3[from_x_c3][from_y_c3];						/* stone moved to new location */
		board_c3[from_x_c3][from_y_c3] = empty;														/* the first part where the stone was found was reset. */
		from_y_c3 = from_y_c3+i+1;																	/* Change new location. */
		n3++;																						/* the number of stones eated has been increased. */
		n3 = max_king(board_c3, from_x_c3, from_y_c3, n3, p);										/* Recall function again for the next movements after this movement. */
	}
	
	/* It checks to the left until it comes to any stones. if the first stone to reach is the opponent stone and if the stone is empty behind it, then the stone is placed. */
	for(i=-1; board[from_x][from_y+i] == empty && from_y+i >= 0; i--);
	if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i-1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i-1] == empty)) && from_y+i-1 >= 0)
	{
		/* If the stone is going to be eaten, it will. */
		board_c4[from_x_c4][from_y_c4+i] = empty;													/* the part where the eaten stone was found was reset. */
		board_c4[from_x_c4][from_y_c4+i-1] = board_c4[from_x_c4][from_y_c4];						/* stone moved to new location */
		board_c4[from_x_c4][from_y_c4] = empty;														/* the first part where the stone was found was reset. */
		from_y_c4 = from_y_c4+i-1;																	/* Change new location. */
		n4++;																						/* the number of stones eated has been increased. */
		n4 = max_king(board_c4, from_x_c4, from_y_c4, n4, p);										/* Recall function again for the next movements after this movement. */
	}
	
	/* By checking all the possibilities we found the most stone-eating situation.
		We apply what we find. */

	if(n1 >= n2 && n1 >= n3 && n1 >= n4)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c1[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c1;
		from_y = from_y_c1;
		x = n1;
	}
	else if(n2 >= n1 && n2 >= n3 && n2 >= n4)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c2[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c2;
		from_y = from_y_c2;
		x = n2;
	}
	else if(n3 >= n1 && n3 >= n2 && n3 >= n4)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c3[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c3;
		from_y = from_y_c3;
		x = n3;
	}
	else if(n4 >= n1 && n4 >= n2 && n4 >= n3)
	{
		/* Change new board. The situation in which he ate most stones. */
		for(i=0 ; i < 8 ; i++)
		{
			for(j=0 ; j < 8; j++)
			{
				board[i][j] = board_c4[i][j];
			}
		}
		/* Change new location and ate stones */
		from_x = from_x_c4;
		from_y = from_y_c4;
		x = n4;
	}
	return x;	/* The maximum number of stones to eat. */
}


int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p)
{
	printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	if(p==10) printf("\nPlayer is White");			/* who is the player */
	else if(p==20) printf("\nPlayer is Black");
	printf("\nFrom_x = %d    from_y = %d    to_x = %d   to_y = %d",from_x,from_y,to_x,to_y);			/* movements */
	printf("\n----- First Status ------\n");
	display_board(board);
	printf("\n----- After Moves ------\n");
	
	int n=0,i,flag=0,e_n=0;
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
						display_board(board);
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
				display_board(board);
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
				display_board(board);
			}
			
			/* Automation stone eating */
			/* If the stone is eaten, print it on the screen and increase the number of eaten stones. */
			if(flag != -1) e_n = max_white(board, from_x, from_y, 0);
			if(e_n != 0) {
				printf("\n----- After automation eating stones: -----");
				display_board(board);
				n += e_n;	
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
						display_board(board);
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
				display_board(board);
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
				display_board(board);
			}
			
			/* Automation stone eating */
			/* If the stone is eaten, print it on the screen and increase the number of eaten stones. */
			if(flag != -1) e_n = max_black(board, from_x, from_y, 0);
			if(e_n != 0) {
				printf("\n----- After automation eating stones: -----");
				display_board(board);
				n += e_n;	
			}	
		}
	}
	
	/* Rules of movements of the kingdoms : */
	else if(board[from_x][from_y] == white_king || board[from_x][from_y] == black_king)
	{
		flag = 0;
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
					display_board(board);
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i+1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i+1] == empty)) && from_y+i+1 <= 7)
				{
					board[from_x][from_y+i+1] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y+i] = empty;							/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					from_y = from_y+i+1;
					display_board(board);
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
					display_board(board);
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x][from_y+i] == black_man || board[from_x][from_y+i] == black_king) && board[from_x][from_y+i-1] == empty) || (p==black && (board[from_x][from_y+i] == white_man || board[from_x][from_y+i] == white_king) && board[from_x][from_y+i-1] == empty)) && from_y+i-1 >= 0)
				{
					board[from_x][from_y+i-1] = board[from_x][from_y];			/* stone moved to new location */
					board[from_x][from_y+i] = empty;							/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;								/* the first part where the stone was found was reset. */
					from_y = from_y+i-1;
					display_board(board);
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
					display_board(board);
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i+1][from_y] == empty) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i+1][from_y] == empty)) && from_x+i+1 <= 7)
				{
					board[from_x+i+1][from_y] = board[from_x][from_y];				/* stone moved to new location */
					board[from_x+i][from_y] = empty;								/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
					from_x = from_x+i+1;
					display_board(board);
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
					display_board(board);
					flag=-1;
				}
				
				/* If there is a stone It checks the right, left, and front to see that can be eaten. */
				else if(((p==white && (board[from_x+i][from_y] == black_man || board[from_x+i][from_y] == black_king) && board[from_x+i-1][from_y] == empty) || (p==black && (board[from_x+i][from_y] == white_man || board[from_x+i][from_y] == white_king) && board[from_x+i-1][from_y] == empty)) && from_x+i-1 >= 0)
				{
					board[from_x+i-1][from_y] = board[from_x][from_y];				/* stone moved to new location */
					board[from_x+i][from_y] = empty;								/* the part where the eaten stone was found was reset. */
					board[from_x][from_y] = empty;									/* the first part where the stone was found was reset. */
					from_x = from_x+i-1;
					display_board(board);
					n++;
				}
				else return -2;														/* wrong move was made */
			}
		}
		
		/* Automation stone eating for King stones. */
		/* If the stone is eaten, print it on the screen and increase the number of eaten stones. */
		if(flag != -1) e_n = max_king(board, from_x, from_y, 0, p);
		if(e_n != 0) {
			printf("\n----- After automation eating stones: -----");
			display_board(board);
			n += e_n;	
		}		
	}
	printf("%d stones were eaten\n\n", n);
	return n;
}


void sample_game_1()
{
	printf("\n\n----------------SAMPLE GAME 1-------------------------\n");
	/* My sample game Black is winner */
	player p;
	piece board[8][8];
	
	init_board(board);			/* initilaze and after display */
	display_board(board);
	
	/* Movements and Checking game*/
	if(check_end_of_game(board) == -1)
	move(board, 3, 3, 4, 3, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 6, 5, 5, 5, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 3, 5, 4, 5, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 5, 5, 3, 5, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 3, 7, 4, 7, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 6, 7, 5, 7, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 4, 7, 6, 7, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 6, 8, 5, 8, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 8, 5, 8, 8, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 6, 1, 5, 1, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 8, 8, 6, 8, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 5, 1, 4, 1, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 3, 1, 5, 1, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 1, 3, 5, 3, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 4, 8, 5, 8, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 7, 1, 6, 1, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 5, 8, 5, 7, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 7, 7, 7, 8, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 5, 7, 5, 2, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 6, 4, 5, 4, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 5, 1, 7, 1, black);

	if(check_end_of_game(board) == -1)
	move(board, 6, 2, 4, 2, white);

	if(check_end_of_game(board) == -1)
	move(board, 7, 1, 8, 1, black);

	if(check_end_of_game(board) == -1)
	move(board, 7, 2, 7 , 1, white);

	if(check_end_of_game(board) == -1)
	move(board, 3, 2, 5, 2, black);

	if(check_end_of_game(board) == -1)
	move(board, 7, 1, 6, 1, white);

	if(check_end_of_game(board) == -1)
	move(board, 8, 1, 5, 1, black);

	if(check_end_of_game(board) == -1)
	move(board, 5, 4, 5, 3, white);

	if(check_end_of_game(board) == -1)
	move(board, 5, 2, 5, 4, black);
	
	if(check_end_of_game(board) == -1)
	move(board, 7, 3, 7, 2, white);

	if(check_end_of_game(board) == -1)
	move(board, 5, 1, 7, 1, black);

	if(check_end_of_game(board) == -1)
	move(board, 6, 3, 6, 4, white);

	if(check_end_of_game(board) == -1)
	move(board, 7, 1, 7, 3, black);

	if(check_end_of_game(board) == -1)
	move(board, 7, 8, 7, 6, white);

	if(check_end_of_game(board) == -1)
	move(board, 5, 4, 7, 4, black);

	if(check_end_of_game(board) == -1)
	move(board, 7, 6, 7, 5, white);

	if(check_end_of_game(board) == -1)
	move(board, 7, 4, 7, 6, black);
	
	check_end_of_game(board);

}
void sample_game_2()
{
	printf("\n\n----------------SAMPLE GAME 2-------------------------\n");
	/* The example given in Gif is the same code exacuting. */
	player p;
	/* initilaze same gif */
	piece board[8][8]={{4,4,4,4,4,4,4,4},{4,4,1,1,1,1,4,4},{4,1,1,1,1,4,1,1},{1,1,1,4,4,1,4,1},{4,4,0,0,0,1,0,0},{0,0,0,0,0,4,0,0},{4,4,0,0,0,0,4,4},{4,4,4,4,4,4,4,4}};
	display_board(board);
	
	/* Movements in gif and Checking game */
	if(check_end_of_game(board) == -1)
	move(board, 6, 2, 5, 2, white);

	if(check_end_of_game(board) == -1)
	move(board, 4, 2, 6, 2, black);

	if(check_end_of_game(board) == -1)
	move(board, 5, 4, 4, 4, white);

	if(check_end_of_game(board) == -1)
	move(board, 5, 6, 5, 4, black);

	if(check_end_of_game(board) == -1)
	move(board, 4, 4, 4, 2, white);

	if(check_end_of_game(board) == -1)
	move(board, 2, 3, 2, 1, black);

	if(check_end_of_game(board) == -1)
	move(board, 6, 4, 5, 4, white);
	
	if(check_end_of_game(board) == -1)
	move(board, 6, 2, 6, 4, black);

	if(check_end_of_game(board) == -1)
	move(board, 5, 4, 4, 4, white);

	if(check_end_of_game(board) == -1)
	move(board, 3, 4, 5, 4, black);

	if(check_end_of_game(board) == -1)
	move(board, 6, 7, 6, 6, white);

	if(check_end_of_game(board) == -1)
	move(board, 8, 6, 5, 6, black);

	if(check_end_of_game(board) == -1)
	move(board, 5, 7, 5, 5, white);
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
		
		result = check_end_of_game(board);
		if(check >= 0)i++;
	} 
}

int main()
{
	sample_game_1();
	sample_game_2();
	/* double_play(); */ 
	return 0;
}
