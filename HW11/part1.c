/***** FURKAN ÖZEV *****/
/***	161044036	***/


#include <stdio.h>
#include <stdlib.h>			/* To use malloc */

/* The lists were created using the following functions. */

/* Creating customer structure like pdf. */
typedef struct customers
{
	char surname[20];
	char name[20];
	char gender[10];
	int age;
	int number_room;
	struct customers *next_customer;	/* This pointer type keep next customer's address. So customers is dynamic */
}customers;

/* Creating room structure like pdf. */
typedef struct rooms
{
	int number;
	int capacity;
	int floor;
	customers *customer;				/* This pointer type holds the origin address of the customer. */
	struct rooms *next_room;			/* This pointer type keep next room's address. So rooms is dynamic */
}rooms;


/* Show used functions */
int add_room_to_end(rooms** room_list, rooms** new_room);
int add_room_after_room_number(rooms** room_list, rooms** new_room, int room_no);
int add_customer_to_end(rooms** room_list, customers** customer);
int link_customers_to_room(rooms** room_list, customers** customer);
int remove_room(rooms** room_list, int room_no);
int show_vacancy(rooms* room_list);
int get_by_floor(rooms* room_list, int floor_no);
int print_list(rooms* room_list);
void free_memory(rooms** room_list);


int main()
{
	/* Open files. */
	FILE* filerooms;
	filerooms = fopen("rooms.txt","rt");
	
	FILE* filecustomers;
	filecustomers = fopen("customers.txt","rt");
	
	rooms *head=NULL, *new_room, *temp=NULL;
	customers *customer, *new_customer;
	int counter = 0;
	char line[100];				/* to read the line of data from the room file. */
	
	while(fgets(line, 1024, filerooms) != NULL)		/*If fgets return NULL, this means that it was read until the end of the file. */
	{
		/* Read the line of data from the room file into line array. Allocate memory for new room. Then put the read data into a struct. */
		new_room = (rooms *) malloc(sizeof(rooms));
		sscanf(line,"%d,%d,%d", &new_room->number, &new_room->capacity, &new_room->floor);
		new_room->customer = NULL;
		new_room->next_room = NULL;
		/* Adds the new room to the end of the list. */
		add_room_to_end(&head, &new_room);
	}
	
	int flag = 0, flag2 = 0, i , number[250];
	char end;
	/* flag is used to check whether the file is finished or not. flag2, checks whether the any customer is connected to the room number. */
	/* The number array holds the numbers of the customer-connected rooms., end variable get the '\n' or 'EOF' in customer file. */
	while(flag != -1)
	{
		customer = (customers *) malloc(sizeof(customers));
		customer->next_customer = NULL;
		fscanf(filecustomers, "%d", &customer->number_room);
		fgetc(filecustomers);
		fscanf(filecustomers, "%s", customer->name);
		fgetc(filecustomers);
		fscanf(filecustomers, "%[^,]s", customer->surname);
		fgetc(filecustomers);
		fscanf(filecustomers, "%d", &customer->age);
		fgetc(filecustomers);
		fscanf(filecustomers, "%s", customer->gender);
		end = fgetc(filecustomers);
		
		/* Check if any customers have been connected to that room before. If connected, flag2 will be 1. */
		flag2=0;
		for(i=0; i<counter; i++)
		{
			if(number[i] == customer->number_room)
			{
				flag2 = 1;
			}
		}
		
		temp = head;		/* take top of the list. */
		if(flag2 == 0)
		{
			/* No customers are connected to this room yet. Write the room number in the number sequence and use the link function to connect. */
			number[i] = customer->number_room;
			link_customers_to_room(&temp, &customer);
		}
		
		else
		{
			/* Add a new customer to the end of the previous one by using this function, because it is associated with any customer. */
			add_customer_to_end(&temp, &customer);
		}
		
		counter++;
		if(end == EOF) flag = -1;			/* If it comes to the end of the file, the flag will be -1, and the customer process will be finished. */
	}
	
	/* Close file */
	fclose(filerooms);
	fclose(filecustomers);
	
	
	/* It is menu for check my programs and functions */
	int choice, room_no, floor_no, res;
	rooms* list;
	do
	{
		res = 0;
		list = head;			/* take top of the list. */
		printf("\n\n------------------MENU------------------\n");
		printf("1.) Add a room to the end of the room list.\n");
		printf("2.) Add a room to after the given room number.\n");
		printf("3.) Add a customer to the end of the partial customer list.\n");
		printf("4.) Add partial customer list to a room.\n");
		printf("5.) Remove the room indicated by the room number.\n");
		printf("6.) List all available rooms that don't have any customer.\n");
		printf("7.) List the rooms with the given floor number.\n");
		printf("8.) Print the room list with customers.\n");
		printf("If you want to terminate the program enter -1.\n");
		printf("\n\nPlease enter your choice: ");
		scanf("%d", &choice);
		printf("\n\n");
		switch(choice)
		{
			case -1:
				printf("\nThe program was successfully terminated.\n");
				break;
				
			case 1:
				/* Allocate memory for new room and get the information of the new room from the user */
				new_room = (rooms *) malloc(sizeof(rooms));
				printf("\nEnter the new room's number: ");
				scanf("%d", &new_room->number);
				printf("\nEnter the new room's floor: ");
				scanf("%d", &new_room->floor);
				printf("\nEnter the new room's capacity: ");
				scanf("%d", &new_room->capacity);
				new_room->next_room = NULL;
				new_room->customer = NULL;
			
				res = add_room_to_end(&list, &new_room);
				break;
				
			case 2:
				/* Allocate memory for new room and get the information of the new room from the user */
				new_room = (rooms *) malloc(sizeof(rooms));
				printf("\nEnter the new room's number: ");
				scanf("%d", &new_room->number);
				printf("\nEnter the new room's floor: ");
				scanf("%d", &new_room->floor);
				printf("\nEnter the new room's capacity: ");
				scanf("%d", &new_room->capacity);
				new_room->next_room = NULL;
				new_room->customer = NULL;
				
				printf("\nEnter the after room number: ");
				scanf("%d", &room_no);
				res = add_room_after_room_number(&list, &new_room, room_no);
				break;
				
			case 3:
				/* Allocate memory for new customer and get the information of the new customer from the user */
				new_customer = (customers *) malloc(sizeof(customers));
				printf("\nEnter the new customer's room number: ");
				scanf("%d", &new_customer->number_room);
				printf("\nEnter the new customer's name: ");
				scanf("%s", new_customer->name);
				printf("\nEnter the new customer's surname: ");
				scanf("%s", new_customer->surname);
				printf("\nEnter the new customer's age: ");
				scanf("%d", &new_customer->age);
				printf("\nEnter the new customer's gender: ");
				scanf("%s", new_customer->gender);
				new_customer->next_customer = NULL;

				res = add_customer_to_end(&list, &new_customer);
				break;
				
			case 4:
				/* Allocate memory for new customer and get the information of the new customer from the user */
				new_customer = (customers *) malloc(sizeof(customers));
				printf("\nEnter the new customer's room number: ");
				scanf("%d", &new_customer->number_room);
				printf("\nEnter the new customer's name: ");
				scanf("%s", new_customer->name);
				printf("\nEnter the new customer's surname: ");
				scanf("%s", new_customer->surname);
				printf("\nEnter the new customer's age: ");
				scanf("%d", &new_customer->age);
				printf("\nEnter the new customer's gender: ");
				scanf("%s", new_customer->gender);
				new_customer->next_customer = NULL;
				
				res = link_customers_to_room(&list, &new_customer);
				break;
				
			case 5:
				/* Get the room number to delete from the user. */
				printf("\nEnter the room number you want to delete: ");
				scanf("%d", &room_no);
				
				res = remove_room(&head, room_no);
				break;
				
			case 6:
				res = show_vacancy(list);
				break;
				
			case 7:
				/* Get the floor number to list from the user. */
				printf("\nEnter the floor number: ");
				scanf("%d", &floor_no);
				
				res = get_by_floor(list, floor_no);
				break;
				
			case 8:
				res = print_list(list);
				break;
				
			default:
				printf("\nIncorrect entry was made, please try again.\n");
		}
		/* The functions used return 1 if successful, 0 if failed. */
		if(res == 1) printf("\nThe operation was successful.\n");
	}
	while(choice != -1);
	
	/* Free memory */
	free_memory(&head);
	
	
	return 0;
}


/* The function add a room to the end of the room list. */
int add_room_to_end(rooms** room_list, rooms** new_room)
{
	rooms *temp_list = (*room_list);
	rooms *temp_new_room = (*new_room);
	/* If no room is registered yet, the new room will be the head of the list. */
	if(temp_list == NULL)
	{
		(*room_list) = temp_new_room;
	}
	else
	{
		/* Finds the last room after that, connects the new room to the room at the end of the list. */
		while(temp_list->next_room != NULL)
		{
			temp_list = temp_list->next_room;
		}
		
		temp_new_room->next_room = NULL;
		temp_new_room->customer = NULL;
		temp_list->next_room = temp_new_room;
	}
	return 1;
}


/* The function add a room to after the given room number. If the given room does not exists, add it to the end of the list. */
int add_room_after_room_number(rooms** room_list, rooms** new_room, int room_no)
{
	rooms *temp_list = (*room_list);
	rooms *temp_new_room = (*new_room);
	rooms *temp_room = (*room_list);
	
	/* From the top of the list to pass the next room until reaches the end of the list or until the room number is reached. */
	while(!(temp_list->number == room_no || temp_list->next_room == NULL))
	{
		temp_room = temp_list;
		temp_list = temp_list->next_room;
	}
	
	/* Add the new room to the end if it has come to the end of room list. */
	if(temp_list->next_room == NULL)
	{
		temp_new_room->next_room = NULL;
		temp_room->next_room = temp_new_room;
	}
	/* Add the new room to the room next to the entered room number. I took the newly created room between 2 rooms.*/
	else if(temp_list->number == room_no)
	{
		temp_room = temp_list->next_room;
		temp_new_room->next_room = temp_room;
		temp_list->next_room = temp_new_room;
	}
	return 1;
}


/* The function add a customer to the end of the partial customer list. */
int add_customer_to_end(rooms** room_list, customers** customer)
{
	int counter = 1;
	rooms *temp_room = (*room_list);
	customers *temp_customer = (*customer);
	customers *free_customer = NULL;
	
	/* From the top of the list to pass the next room until reaches the end of the list or until the room number is reached. */
	while(!(temp_room->number == temp_customer->number_room || temp_room == NULL))
	{
		temp_room = temp_room->next_room;
	}
	
	/* If it has come to the end of room list, this room is not yet registered. */
	if(temp_room == NULL && temp_room->number != temp_customer->number_room)
	{
		printf("\nThe requested number is not available in the room. Please create the room first.\n");
		return 0;
	}
	
	/* If the partial customer of the room, ie the first customer is not connected, the new customer can not be connected. */
	free_customer = temp_room->customer;
	if(free_customer == NULL)
	{
		printf("\nFirstly, Add partial customer list to a room because there is no partial customer list in the requested room number.\n");
		return 0;
	}
	
	/* Find the end of the room's customer list. */
	while(free_customer->next_customer != NULL)
	{
		counter++;
		free_customer = free_customer->next_customer;
	}
	
	/* If there is a quota, add the new customer to the end of the customer list of the room. */
	if(temp_room->capacity > counter)
	{	
		temp_customer->next_customer = NULL;
		free_customer->next_customer = temp_customer;
		return 1;	
	}
	else printf("\nThe room's quota is full. Please try for a different room number.\n");
	return 0;
}



/* The function adds partial customer list to a room. */
int link_customers_to_room(rooms** room_list, customers** customer)
{
	rooms *temp_room = (*room_list);
	customers *temp_customer = (*customer);
	
	/* From the top of the list to pass the next room until reaches the end of the list or until the room number is reached. */
	while(!(temp_room->number == temp_customer->number_room || temp_room->next_room == NULL))
	{
		temp_room = temp_room->next_room;
	}
	
	/* If it has come to the end of room list, this room is not yet registered. */
	if(temp_room->next_room == NULL && temp_room->number != temp_customer->number_room)
	{
		printf("\nThe requested number is not available in the room. Please create the room first.\n");
		return 0;
	}
	
	/* If there is a quota, add the new and first customer to the head of room's customer list. */
	if(temp_room->customer == NULL)
	{
		if(temp_room->capacity > 0)
		{
			temp_room->customer = temp_customer;
			temp_room->customer->next_customer = NULL;
			return 1;
		}
		else printf("\nThe capacity of the room is insufficient.\n");
	}
	
	else printf("\nCurrently there is a list of customers connected to the room. Please add at the end of the customer list.\n");
	return 0;
}

/* The function removes the room indicated by the room number. */
int remove_room(rooms** room_list, int room_no)
{
	int counter = 0;
	rooms *before_room = (*room_list);
	rooms *room = (*room_list);
	
	/* From the top of the list to pass the next room until reaches the end of the list or until the room number is reached. */
	while(!(room->number == room_no || room->next_room == NULL))
	{
		counter++;
		before_room = room;
		room = room->next_room;
	}
	
	if(room->number == room_no)
	{
		/* For head of list */
		if(counter == 0)
		{
			before_room = room;
			(*room_list) = room->next_room;
			free(before_room);
		}
		/* from anywhere in the list */
		else
		{
			before_room->next_room = room->next_room;
			free(room);	
		}
		return 1;
	}
	
	else
	{
		printf("\nThere is no room on the list.\n");
		return 0;
	}
}

/* The function list all available rooms that don’t have any customer. */
int show_vacancy(rooms* room_list)
{
	int counter = 0;
	rooms *temp_room = room_list;
	
	/* Check it from the beginning to the end. */
	while(temp_room != NULL)
	{
		/* If the customer's list of rooms is empty, print the room. */
		if(temp_room->customer == NULL)
		{
			counter++;
			printf("Room %d (Floor %d - capacity %dx)\n", temp_room->number, temp_room->floor, temp_room->capacity);
		}
		/* Pass the next room until end of room list */
		temp_room= temp_room->next_room;
	}
	
	if(counter == 0){
		printf("\nThere are no non-customer rooms.\n");
		return 0;	}
	else printf("\nThere are %d non-customer rooms.\n",counter);
	return 1;	
}

/* The function lists the rooms with the given floor number. */
int get_by_floor(rooms* room_list, int floor_no)
{
	int counter = 0;
	rooms *temp_room = room_list;
	
	/* Check it from the beginning to the end. */
	while(temp_room != NULL)
	{
		/* If the floor number of the room is the same as the entered floor number, print it on the screen. */
		if(temp_room->floor == floor_no)
		{
			counter++;
			printf("Room %d (Floor %d - capacity %dx)\n", temp_room->number, temp_room->floor, temp_room->capacity);
		}
		/* Pass the next room until end of room list */
		temp_room= temp_room->next_room;
	}
	
	if(counter == 0){
		printf("\nThere are no rooms on this floor.\n");
		return 0;	}
	else printf("\nThere are %d rooms on this floor.\n",counter);
	return 1;
}

/* The function prints the room list with customers */
int print_list(rooms* room_list)
{
	int counter = 0;
	rooms *temp_room = room_list;
	customers *temp_customer = NULL;
	
	/* Check it from the beginning to the end of the room list. */
	while(temp_room != NULL)
	{
		counter++;
		temp_customer = temp_room->customer;
		/* If there is a customer, print room's details */
		printf("\nRoom %d (Floor %d - capacity %dx)\n", temp_room->number, temp_room->floor, temp_room->capacity);
		while(temp_customer != NULL)
		{
			/* Print customer's details. */
			printf("\t-> %s %s (%d - %s)\n", temp_customer->name, temp_customer->surname, temp_customer->age, temp_customer->gender);
			/* Pass the next customer until end of customer list */
			temp_customer = temp_customer->next_customer;
		}
		/* Pass the next room until end of room list */
		temp_room= temp_room->next_room;
	}
	
	if(counter == 0){
		printf("\nThere are no rooms on the list.\n");
		return 0;	}
	else printf("\nThere are %d rooms on the list.\n",counter);
	return 1;
}

/* Free all memory */
void free_memory(rooms** room_list)
{
	/* From the beginning of the room list to the end of the list, first free the customer memory, 
		then free the room memory to the other room and do the same. */
	rooms *temp_room = (*room_list);
	customers *temp_customer = NULL;
	customers *customer = NULL;
	
	while((*room_list) != NULL)
	{
		customer = (*room_list)->customer;
		/* If there is a customer, firstly free them. */
		while(customer != NULL)
		{
			temp_customer = customer;
			customer = customer->next_customer;
			free(temp_customer);
		}
		/* Free room memory. */
		temp_room = (*room_list);
		(*room_list) = (*room_list)->next_room;
		free(temp_room);
	}
}
