/********* Header files ************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/********* Macro for malloc ***********/
#define MALLOC(node) \
	node = malloc(sizeof(node_t *));	\
	if(node == NULL)	\
	{	\
		printf("Memory allocation failed.");	\
		return FAILURE;	\
	}

/******** Structure for node of linked list *********/
typedef struct node{
	int data;
	struct node *next;
}node_t;

/******** Enum ***********/
typedef enum status{
	FAILURE,
	SUCCESS
}status_t;

// Head of linked list
node_t *head = NULL;

// Create node for the linked list.
status_t create_node(int data)
{
	node_t *new_node = NULL;
	
	MALLOC(new_node);
	
	new_node->data = data;
	new_node->next = head;
	head = new_node;
	
	return SUCCESS;
}

// Create the linked list.
status_t create_linked_list()
{
	int data = 0;
	
	printf("\nEnter 0 when you want to stop entering values.");
	
	while(true)
	{
		printf("\nEnter the number : ");
		if(scanf("%d", &data) != 1)
		{
			printf("\nOnly numeric values allowed");
			continue;
		}
		
		if(data == 0)
			break;
		
		if(create_node(data) == FAILURE)
			printf("\nSomething went wrong.");
	}
	
	return SUCCESS;
}

// Display the content of list.
void display_list()
{
	node_t *node = head;
	
	printf("\nContent of linked list : ");
	
	while(node)
	{
		printf("\n%d", node->data);
		node = node->next;
	}
}

// Prints the middle element of the list.
/*void mid_of_list(node_t *node)
{
	static int length = 0;
	int index = 0;
	
	if(!node)
		return;
	
	index = ++length;
	
	mid_of_list(node->next);
	
	if(index == (length/2))
		printf("\nMid  of list = %d", node->data);
}*/

void mid_of_list()
{
	node_t *node_slow = head;
	node_t *node_fast = head ? head->next : head;
	
	while(node_slow && node_fast && node_fast->next)
	{
		node_slow = node_slow->next;
		node_fast = node_fast->next->next;
	}
	if(node_slow)
		printf("\nMid  of list = %d", node_slow->data);
}


// Driver function.
int main()
{
	if(create_linked_list() == FAILURE)
		printf("Creation of linked list failed.");
	
	display_list();
	
	mid_of_list();
	return 0;
}