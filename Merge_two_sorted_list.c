#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h> 

#define TEN 10

typedef struct Node {
	uint8_t data;
	struct Node* next;
}node;

void display_list(node* list)
{
	while(list)
	{
		printf("%d\t", list->data);
		list = list->next;
	}
	
	printf("\n");
}

void add_node_at_end(node** head, node** node_to_add)
{
	node* temp_node = *head;

	if(NULL == (*head))
	{
		*head = *node_to_add;
		return;
	}
	
	while(NULL != temp_node->next)
		temp_node = temp_node->next;
	
	temp_node->next = *node_to_add;
}

void add_node_at_beginning(node** head, node** node_to_add)
{
	(*node_to_add)->next = *head;
	*head = *node_to_add;
}

node* create_node(uint8_t data)
{
	node* temp_node = NULL;
	
	temp_node = malloc(sizeof(node*));
	if(!temp_node)
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}
	
	temp_node->data = data;
	temp_node->next = NULL;
	
	return temp_node;
}

void add_node(node** head, uint8_t data)
{
	node* temp_node = create_node(data);
	add_node_at_end(&(*head), &temp_node);
}

node* merge_list(node* list_1, node* list_2)
{	
	if(!list_1)
		return list_2;
	
	if(!list_2)
		return list_1;
	
	node* head = NULL;
	node* main_list = NULL;
	node* list = NULL;
	node* next = NULL;
	
	if( (list_1->data) <= (list_2->data) )
	{
		head = list_1;
		list = list_2;
	}
	else
	{
		head = list_2;
		list = list_1;
	}
	
	main_list = head;
	next = main_list->next;
	
	while(list)
	{
		if(!next)
		{
			main_list->next = list;
			break;
		}
		else if(next->data <= list->data)
		{
			main_list = next;
			next   = main_list->next;
		}
		else
		{
			main_list->next = list;
			main_list = list;
			list = next;
			next = main_list->next;
		}
	}
		
	return head;
}

int main()
{
    node* list_1 = NULL;
	node* list_2  = NULL;
	
	add_node(&list_1,2);
	add_node(&list_1,4);
	add_node(&list_1,7);
	
	printf("First list :\n");
	display_list(list_1);
	
	add_node(&list_2,1);
	add_node(&list_2,2);
	add_node(&list_2,6);
	add_node(&list_2,8);
	
	printf("Second list :\n");
	display_list(list_2);
	
	list_1 = merge_list(list_1, list_2);
	
	printf("Final list :\n");
	display_list(list_1);
	
    return 0;
}
