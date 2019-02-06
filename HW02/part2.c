#include <stdio.h>
int main()
{
	int number=0,fifth,fourth,third,second,first;
	/* I have created a while loop to keep getting new numbers as long as the user does not enter a number between 23 and 98760 */
	while(number <= 23 || number >= 98760)
	{
		printf("\n Enter the number: ");
		scanf("%d", &number);
		if(number <= 23 || number >= 98760)
		{
			printf("\n Number must be between 23 and 98760 (23,98760)");
		}
	}
	
	/* To find the digit place, I split numbers into multiples of 10 and got the mod for 10. */
	fifth = (number / 10000) % 10; 			/* for example abcde / 10000 = a.bcde but it is integer value so equal a .  a mod 10 = a */
	fourth = (number / 1000) % 10;
	third = (number / 100) % 10;
	second = (number / 10) % 10;
	first = number % 10;
	
	/* The fifth number can not be zero. for example 0bcde can not be 5 digits it is 4 digits like that bcde */
	if ( fifth != 0 )
	{
		printf("\n The fifth digit is %d", fifth);
	}
	
	/* If the fifth numbers are 0, the fourth number can not be zero. But if the fifth number is not 0, the fourth number can be 0. */
	if ( fifth != 0 || ( fifth == 0 && fourth != 0 ) )
	{
		printf("\n The fourth digit is %d", fourth);
	}
	
	/* If the fifth and fourth numbers are 0, the third number can not be zero. 
		But if the fifth number is not 0 or the fifth number is 0 but fourth number is not 0, the third number can be 0. */
	if ( fifth != 0 || ( fourth != 0 || ( fourth == 0 && third != 0 ) ) )
	{
		printf("\n The third digit is %d", third);
	}
	
	/* the number entered is greater than 23, so there is at least 2 digits, so there is no need for any control. */
	printf("\n The second digit is %d", second);
	
	printf("\n The first digit is %d \n", first);
	
	
	return 0;
}
