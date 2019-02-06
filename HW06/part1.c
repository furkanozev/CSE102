/***
**** 	FURKAN ÖZEV
    	 161044036		****
     		   			***/

#include<stdio.h>
#define BUFFER 1024
void reverse_line(char line[], int line_lenght)
{
	char temp[BUFFER];
	int i;
	/* I copied the string to a new array. */
	for(i=0; i<line_lenght; i++)
	{
		temp[i]=line[i];
	}
	/* I copied the characters of the copy array starting from the end of copy array to the beginning of copy array into the line array. */
	for(i=0; i<line_lenght; i++)
	{
		line[i]=temp[line_lenght-i-1];
	}
}

int find_size_of_line(char line[])
{
	int counter;
	/*	I count characters up to the end of line character( '\n' ) or end file character.(NULL or '\0').
		There is a end of line character at the end of each line but in the last line there is no line end character( '\n' ), 
		there is end file character(NULL or '\0'). So I checked for both.	*/
	for(counter=0; line[counter] != '\n' && line[counter] != '\0'; counter++);
	return counter;
}

void encrypt_open_msg()
{
	/* I specify the file to be encrypted as an input file and open it with the read command. */
	FILE *fileinput = fopen("open_msg.txt","rt");
	/* I specify output file to hold the passwords, and open file with the write command. */
	FILE *fileoutput = fopen("secret_msg.txt","wt");
	/* I defined an array to hold lines in an array. */
	char line[BUFFER];
	int size_line,key,i,temp;
	
	/* get the key from user. */
	do
	{
		printf("\nEnter the number of key between 1 to 26.: ");
		scanf("%d", &key);
	}
	while(!(key>=1 && key <= 26));
	printf("\n");
	/* Get every line from the file until the end of the file. */
	while (fgets( line, BUFFER, fileinput ) != NULL)
    {
        size_line = find_size_of_line(line);		/* Get the size of line */
        reverse_line(line, size_line);				/* Reverse line */
        /* Encrypt each character until the end of the line. */
        for(i=0; i<size_line; i++)
        {
        	/* If the character is '.', put '*' instead. */
        	if(line[i] == '.')						
        	{
        		line[i] = '*';
			}
			/* If the character is ' ', put '_' instead. */
			else if(line[i] == ' ')
			{
				line[i] = '_';
			}
			/* If the character returns to the end of the alphabet, find the equivalent.
				Character must go back from 'z' as far as it goes back from 'a'. */
			else if(line[i] - key < 'a')
			{
				temp = line[i] - key;
				temp = 'a' - temp;
				temp = 'z' - temp + 1;
				line[i] = temp;
			}
			/* According to the alphabet, take back the character as far as key. */
			else
			{
				line[i] = line[i] - key;
			}
		}
		fputs(line, fileoutput);			/* Write line to file to be encrypted. */
		printf("%s",line);
    }
    printf("\n");
    /* The file has been closed. */
    fclose(fileinput);
    fclose(fileoutput);
}

void decrypt_secret_msg()
{
	/* I specify the file to be decrypted as an input file and open it with the read command. */
	FILE *fileinput = fopen("secret_msg.txt","rt");
	/* I specify output file to hold the messages, and open file with the write command. */
	FILE *fileoutput = fopen("open_msg.txt","wt");
	/* I defined an array to hold lines in an array. */
	char line[BUFFER];
	int size_line,key,i,temp;
	
	/* get the key from user. */
	do
	{
		printf("\nEnter the number of key between 1 to 26.: ");
		scanf("%d", &key);
	}
	while(!(key>=1 && key <= 26));
	printf("\n");
	/* Get every line from the file until the end of the file. */
	while (fgets ( line, BUFFER, fileinput ) != NULL)
    {
        size_line = find_size_of_line(line);			/* Get the size of line */
        reverse_line(line, size_line);					/* Reverse line */
        /* Eecrypt each character until the end of the line. */
        for(i=0; i<size_line; i++)
        {
        	/* If the character is '*', put '.' instead. */
        	if(line[i] == '*')
        	{
        		line[i] = '.';
			}
			/* If the character is '_', put ' ' instead. */
			else if(line[i] == '_')
			{
				line[i] = ' ';
			}
			/* If the character returns to the beginning of the alphabet, find the equivalent.
				Character must go next from 'a' as far as it goes next from 'z'. */
			else if(line[i] + key > 'z')
			{
				temp = line[i] + key;
				temp = temp - 'z';
				temp = 'a' + temp - 1;
				line[i] = temp;
			}
			/* According to the alphabet, take next the character as far as key. */
			else
			{
				line[i] = line[i] + key;
			}
		}
		fputs(line, fileoutput);			/* Write line to file to be encrypted. */
		printf("%s",line);
    }
    printf("\n");
    /* The file has been closed. */
    fclose(fileinput);
    fclose(fileoutput);
}

void menu()
{
	/* As long as the user does not enter 0, the menu will be displayed. 
		If the user enters 1 or 2, the desired action will be taken. 
		If the user enters something different, an error message will be given. */
	int choice;
	do
	{
		printf("\n1. Encrypt");
		printf("\n2. Decrypt");
		printf("\n0. Exit");
		printf("\nChoice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				encrypt_open_msg();
				break;
				
			case 2:
				decrypt_secret_msg();
				break;
				
			case 0:
				printf("\nSuccessfully exited.\n");
				break;
				
			default:
				printf("\nInput is invalid. Choice can be 0,1 or 2.\n");
				break;
		}
	}
	while(choice != 0);
}

int main()
{
	menu();
	return 0;
}
