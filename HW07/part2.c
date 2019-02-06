/***--------------------***\
-*****------FURKAN ÖZEV----*
-*****-----------------****-
/***--------------------***/

#include <stdio.h>
void input_date();
void get_date(int *day, int *month, int *year);
int check_date(int day, int month, int year);
int check_possible(int st_day , int st_month, int st_year, int fin_day , int fin_month, int fin_year);
void input_date_write(int st_day, int st_month, int st_year, int fin_day, int fin_month , int fin_year);
void next_date(int *day, int *month, int *year);

void new_date();
int calculate_date(const char date[12], int *day, int *month, int *year);

int main()
{
	input_date();
	new_date();
}

/* The main function used to create the dates to be written to the input_date.txt file. */
void input_date()
{
	int st_day , st_month, st_year;
	int fin_day , fin_month, fin_year;
	do
	{
		/* Get the start date from user. If this date is wrong , get new date again from user. */
		printf("\nEnter the start date: dd/mm/yyyy\n");
		get_date(&st_day, &st_month, &st_year);
		while(check_date(st_day, st_month, st_year) == 0)
		{
			printf("\nPlease enter again \n");
			get_date(&st_day, &st_month, &st_year);
		}
		
		/* Get the finish date from user. If this date is wrong , get new date again from user. */
		printf("\nEnter the finish date: dd/mm/yyyy\n");
		get_date(&fin_day, &fin_month, &fin_year);
		while(check_date(fin_day, fin_month, fin_year) == 0)
		{
			printf("\nPlease enter again \n");
			get_date(&fin_day, &fin_month, &fin_year);
		}
	}
	/* The start date must be before the end date. */
	while(check_possible(st_day , st_month, st_year, fin_day , fin_month, fin_year) != 1);
	
	/* This function was used to print the days in the file. */
	input_date_write(st_day, st_month, st_year, fin_day, fin_month , fin_year);
	printf("\nStart date: %02d/%02d/%04d \t Finish date: %02d/%02d/%04d", st_day, st_month, st_year, fin_day, fin_month, fin_year);
	printf("\nThe input_date.txt file successfully created\n");
}

/* The function used to get dates from the user. */
void get_date(int *day, int *month, int *year)
{
	char date[11]={' '};
	scanf("%s", date);
	/* Check whether the user entered in dd / mm / yyyy format. */
	while(date[2] != '/' || date[5] != '/')
	{
		printf("Please enter the this format: dd/mm/yyyy\n");
		scanf("%s", date);
	}
	/* The digits in the string are kept as characters so that the characters are converted to ascii counter.
		After that calculate day , month and year */
	*day = (date[0] - 48) * 10 + (date[1] - 48);
	*month = (date[3] - 48) * 10 + (date[4] - 48);
	*year = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + (date[9] - 48);
}

/* Checks whether the entered date corresponds to a correct date. */
int check_date(int day, int month, int year)
{
	/* Returns 0 if there is a problem with the date entered, 1 otherwise. */
	int r = 1;
	/* Year can not be smaller than 1. */
	if(year < 1)
	{
		printf("\n You entered the wrong year.");
		r = 0;
	}
	/* The month, can not be less than 1 and greater than 12. */
	if(month < 1 || month > 12)
	{
		printf("\n You entered the wrong month.");
		r = 0;
	}
	/* The day, can not be less than 1 and greater than 31. */
	if(day < 1 || day > 31)
	{
		printf("\n You entered the wrong day.");
		r = 0;
	}
	/* February is 29 days every 4 years and 28 days for other years. */
	if(month == 2)
	{
		if(year % 4 == 0 && day > 29)
		{
			printf("\n You entered the wrong date.");
			r = 0;	
		}
		else if(year % 4 != 0 && day > 28)
		{
			printf("\n You entered the wrong date.");
			r = 0;
		}
	}
	/* April, June, September, November are 30 days every years. Other months are 31 days every years. */
	else if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
		printf("\n You entered the wrong date.");
		r = 0;
	}
	return r;
}

/* Checks that the start date can not be after the end date. If possible, function return 1 otherwise return 0.*/
int check_possible(int st_day , int st_month, int st_year, int fin_day , int fin_month, int fin_year)
{
	/* First, compare the years, if there is equality, compare the months, then compare the days if there is equality again. */
	int r;
	if(fin_year > st_year) r = 1;
	else if(fin_year < st_year) r = 0;
	else if(fin_year == st_year)
	{
		if(fin_month > st_month) r = 1;
		else if(fin_month < st_month) r = 0;
		else if(fin_month == st_month)
		{
			if(fin_day > st_day) r = 1;
			else if(fin_day < st_day) r = 0;
			else r = 0;
		}
	}
	if(r == 0)
	{
		printf("\nThe start date can not be after the end date. Please enter the dates again: \n");	
	} 
	return r;
	
}

/*The date is used to write the file in dd / mm / yyyy format. */
void input_date_write(int st_day, int st_month, int st_year, int fin_day, int fin_month , int fin_year)
{
	FILE *finput = fopen("input_date.txt","wt");
	/* it increments the number of days by 1 until the start date equals the end date, 
		sets the new date, and then writes the date line dd / mm / yyyy format to the file.*/
	while(!(st_day == fin_day && st_month == fin_month && st_year == fin_year))
	{
		fprintf(finput,"%02d/%02d/%04d\n", st_day, st_month, st_year);
		st_day++;
		next_date(&st_day, &st_month, &st_year);
	}
	fprintf(finput,"%02d/%02d/%04d", st_day, st_month, st_year);
	
	fclose(finput);
}

/* It determines the next day. */
void next_date(int *day, int *month, int *year)
{
	/* The day, month, and year values are continuously sent to this function after a 1 day increase. */
	/* If the number of days is full for the month in which they are, the beginning of the next month begins. */
	if(*month == 2)
	{
		if(*year % 4 == 0 && *day > 29)
		{
			*day = 1;
			*month = *month + 1;
		}
		else if(*year % 4 != 0 && *day > 28)
		{
			*day = 1;
			*month = *month + 1;
		}
	}
	else if((*month == 4 || *month == 6 || *month == 9 || *month == 11) && *day > 30)
	{
		*day = 1;
		*month = *month + 1;
	}
	else if(*day > 31)
	{
		*day = 1;
		*month = *month + 1;
	}
	/*If the number of months and days is full for the year in which they are, the beginning of the next year begins. */
	if(*month > 12)
	{
		*month = 1;
		*year = *year + 1;
	}
}

/* The main function take the dates from input_date.txt file and to be written be new format to the new_date.txt file. */
void new_date()
{
	char month_name[12][10]={{'J','a','n','u','a','r','y'}, {'F','e','b','r','u','a','r','y'}, {'M','a','r','c','h'}, {'A','p','r','i','l'}, {'M','a','y'}, {'J','u','n','e'}, {'J','u','l','y'}, {'A','u','g','u','s','t'}, {'S','e','p','t','e','m','b','e','r'}, {'O','c','t','o','b','e','r'}, {'N','o','v','e','m','b','e','r'}, {'D','e','c','e','m','b','e','r'}};
	char day_name[7][15]={{'M','o','n','d','a','y'}, {'T','u','e','s','d','a','y'}, {'W','e','d','n','e','s','d','a','y'}, {'T','h','u','r','s','d','a','y'}, {'F','r','i','d','a','y'}, {'S','a','t','u','r','d','a','y'}, {'S','u','n','d','a','y'}};
	char date[12];
	int day, month, year, day_code;
	/* day_code, keeps days corresponds to which date. */
	
	/* The dates will be read line by line from the input_date.txt file, 
		then the day and month will be calculated and written to the new_date.txt file in the new format. */
	FILE *finput = fopen("input_date.txt","rt");
	FILE *fnew = fopen("new_date.txt","wt");
	
	/* It takes the individual lines from the file until the last line is empty. */
	while (fgets( date, 12, finput ) != NULL)
	{
		day_code = calculate_date(date, &day, &month, &year);
		fprintf(fnew,"%s,%s %02d,%04d\n", day_name[day_code-1], month_name[month-1], day, year);
	}
	printf("The new_date.txt file successfully created\n");
	fclose(finput);
	fclose(fnew);
}

/* Calculates the date and the day and month on which the date correspond. */
int calculate_date(const char date[12], int *day, int *month, int *year)
{
	/* The digits in the string are kept as characters so that the characters are converted to ascii counter.
		After that calculate day , month and year */
	*day = (date[0] - 48) * 10 + date[1] - 48;
	*month = (date[3] - 48) * 10 + date[4] - 48;
	*year = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + date[9] - 48;
	
	/* I fixed a fixed day. It will calculate according to this date which day the entered date corresponds to. */
	int c_day = 1, c_month = 1, c_year = 1920, c_dcode = 4, total_d = 0;
	/* c_day => constant day , c_month => constant month , c_year => constant year , c_dcode => constant day code */
	
	/* It calculates how many days distance from the fixed date. */
	
	total_d += (*day - c_day); /* Calculate distance of days. */
	
	 /* Calculate distance of months, after that months distance convert to days distance. */
	 /* If the month is increasing. */
	if(*month > c_month)
	{
		while(*month - c_month != 0)
		{
			if(c_month == 2)
			{
				if(*year % 4 == 0) total_d += 29;
				else total_d += 28;
			}
			else if(c_month == 4 || c_month == 6 || c_month == 9 || c_month == 11) total_d += 30;
			else total_d += 31;
			c_month++;
		}
	}
	/* If the month is decreasing. The important point here is that you must check the previous month because it is back. */
	else
	{
		while(*month - c_month != 0)
		{
			if(c_month == 3)
			{
				if(*year % 4 == 0) total_d -= 29;
				else total_d -= 28;
			}
			else if(c_month == 5 || c_month == 7 || c_month == 10 || c_month == 12) total_d -= 30;
			else total_d -= 31;
			c_month--;
		}
	}
	
	/* Calculate distance of years. after that years distance convert to days distance. */
	/* If the year is increasing. */
	if(*year - c_year > 0)
	{
		while(*year - c_year!=0)
		{
			if(c_year % 4 == 0) total_d += 366;
			else total_d += 365;
			c_year++;
		}
	}
	/* If the year is decreasing. The important point here is that you must check the previous year because it is back.*/
	else
	{
		while(*year - c_year!=0)
		{
			if((c_year-1) % 4 == 0) total_d -= 366;
			else total_d -= 365;
			c_year--;
		}
	}

	/* Add the total day to c_dcode and get mod according to 7. 
	If the result is negative, 7 is added and it is found which day of the week corresponds. */
	c_dcode += total_d;
	c_dcode = c_dcode % 7;
	if(c_dcode <= 0) c_dcode += 7;
	return c_dcode;
}
