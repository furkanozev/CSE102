#include <stdio.h>
#include <math.h>		/* I used the math.h library to use Pow and Sqrt functions. */
#define PI 3.14			/* I defined PI = 3.14 to use in all functions. */
/* I have defined all the functions that I used. */
double circle_area(double radius);
double calc_hypotenuse(int side1, int side2);
double calc_radius_of_smallest_circle(int side1, int side2);
double calc_radius_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_circle(int side1, int side2);
double calc_area_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_square(int side1, int side2);
double calc_area_of_largest_square(int side1, int side2);
double calc_area_of_square (int side);
void display_results( double largest_circle, double largest_square, double smallest_circle, double smallest_square );

int main()
{
	int side1,side2;
	double largest_circle,smallest_circle,largest_square,smallest_square;
	
	/* I'll get the side lengths of the rectangle from the user. */
	printf("-----Please enter the side lengths of the rectangle-----");
	printf("\n Enter first side for rectangle: ");
	scanf("%d",&side1);
	printf("\n Enter second side for rectangle: ");
	scanf("%d",&side2);
		
	/* I assigned the functions that fulfill calculations to variables and print them on the screen with display_results funciton. */
	largest_circle = calc_area_of_largest_circle(side1, side2);
	smallest_circle = calc_area_of_smallest_circle(side1, side2);
	largest_square = calc_area_of_largest_square(side1, side2);
	smallest_square = calc_area_of_smallest_square(side1, side2);
	
	display_results( largest_circle, largest_square, smallest_circle, smallest_square );
	
	return 0;
}

void display_results( double largest_circle, double largest_square, double smallest_circle, double smallest_square )
{
	/* Print *result */
	printf("\nThe area of the largest circle that fits inside a rectangle: \t\t %.2f",largest_circle);
	printf("\nThe area of the largest square that fits inside the rectangle: \t\t %.2f",largest_square);
	printf("\nThe area of the smallest circle that surrounds the same rectangle: \t %.2f",smallest_circle);
	printf("\nThe area of the smallest square that surrounds the same rectangle: \t %.2f\n",smallest_square);
}

double calc_area_of_largest_circle(int side1, int side2)
{
	/* After computing the radius with the calc_radius_of_largest_circle function, I computed the area of the circle with the circle_area function. */
	double radius,area_of_circle;
	radius = calc_radius_of_largest_circle(side1, side2);
	area_of_circle = circle_area(radius);
	
	return area_of_circle;
}

double calc_radius_of_largest_circle(int side1, int side2)
{
	double radius;
	double side1_d = side1;
	double side2_d = side2;
	
	/* The diameter of largest circle that can fits inside the rectangle is equal to the shortest side of the rectangle. */
	/* First of all, I have identified the shortest side of rectangle then, I divide the diameter by 2 and calculate the radius. */
	if(side1_d>=side2_d)
	{
		radius=side2_d/2;
	}
	else
	{
		radius=side1_d/2;
	}
	
	return radius;
}

double calc_area_of_smallest_circle(int side1, int side2)
{
	/* After computing the radius with the calc_radius_of_smallest_circle function, I computed the area of the circle with the circle_area function. */
	double radius,area_of_circle;
	radius = calc_radius_of_smallest_circle(side1, side2);
	area_of_circle = circle_area(radius);
	
	return area_of_circle;
}

double calc_radius_of_smallest_circle(int side1, int side2)
{
	/* The diameter of the smallest circle surrounding the rectangle is calculated by the pythagorean theorem. */
	/* The sum of the squares of the side lengths are equal to the diameter. x^2 + y^2 = D^2  D/2=r (D>> diameter r>> radius)*/
	/* I used the calc_hypotenuse function to make this calculate. */
	double radius,temple;
	radius = calc_hypotenuse(side1, side2) / 2;
	
	return radius;
}

double calc_hypotenuse(int side1, int side2)
{
	/* x^2 + y^2 = H^2 (H >> Hypotenus) */
	double hypotenuse,temple;
	temple = pow(side1,2)+pow(side2,2);
	temple = sqrt(temple);
	hypotenuse = temple;

	return hypotenuse;
}

double circle_area(double radius)
{
	/* Area of the circle = PI * radius ^ 2 */
	double circle_area;
	circle_area = PI * pow(radius,2);
	
	return circle_area;
}

double calc_area_of_largest_square(int side1, int side2)
{
	/* The side of the largest square that fits inside the rectangle equal to the smallest side of the rectangle. */
	/* I determined the side of the square and calculated the area with calc_area_of_square function. */
	double side,area_square;
	double side1_d = side1;
	double side2_d = side2;
	if(side1_d>=side2_d)
	{
		side=side2_d;
	}
	else
	{
		side=side1_d;
	}
	area_square = calc_area_of_square (side);
	
	return area_square;
}

double calc_area_of_smallest_square(int side1, int side2)
{
	/* The side of the smallest square that fits inside the rectangle equal to the largest side of the rectangle. */
	/* I determined the side of the square and calculated the area with calc_area_of_square function. */
	double side,area_square;
	double side1_d = side1;
	double side2_d = side2;
	if(side1_d>=side2_d)
	{
		side=side1_d;
	}
	else
	{
		side=side2_d;
	}
	area_square = calc_area_of_square (side);

	return area_square;
}

double calc_area_of_square (int side)
{
	/* The area of square is equal to the multiple of the sides. x * x = Area */
	double area_square;
	area_square = pow(side,2);
	
	return area_square;
}
