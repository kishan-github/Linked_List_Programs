#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h> 

#define TEN 10

typedef struct Node {
	uint8_t digit;
	struct Node* next;
}node;

typedef enum state
{
	DIVISION_POSSIBLE,
	DIVISION_NOT_POSSIBLE,
	UNKNOWN
}state_t;

void display_list(node* list)
{
	while(list)
	{
		printf("%d\t", list->digit);
		list = list->next;
	}
	
	printf("\n");
}

node* reverse_list(node* list)
{
	node* curr = list;
	node* prev = NULL;
	node* next = list;
	
	while(curr)
	{
		next = curr->next;
		
		curr->next = prev;
		prev = curr;
		curr = next;
		//next = next->next;
	}
	
	return prev;
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

node* create_node(uint8_t digit)
{
	node* temp_node = NULL;
	
	temp_node = malloc(sizeof(node*));
	if(!temp_node)
	{
		printf("Memory allocation failed.\n");
		return NULL;
	}
	
	temp_node->digit = digit;
	temp_node->next = NULL;
	
	return temp_node;
}

void add_node(node** head, uint8_t digit)
{
	node* temp_node = create_node(digit);
	add_node_at_end(&(*head), &temp_node);
}

node* create_reversed_list(node* list)
{
	node* reversed_list = NULL;
	node* temp_node     = NULL;
	
	while(list)
	{
		temp_node = create_node(list->digit);
		add_node_at_beginning(&reversed_list, &temp_node);
		list = list->next;
	}
	
	return reversed_list;
}

uint32_t length(node* list)
{
	uint32_t len = 0;
	
	while(list)
	{
		len++;
		list = list->next;
	}
	
	return len;
}

state_t is_division_finished(node* dividend, node* divisor)
{
	state_t curr_state = UNKNOWN;
	
	if(!dividend)
		return UNKNOWN;
	
	if(!(dividend->next) && (!divisor) && (dividend->digit))
		return DIVISION_POSSIBLE;
	
	if(divisor)
		curr_state = is_division_finished(dividend->next, divisor->next);
	else
		curr_state = is_division_finished(dividend->next, divisor);
	
	if(UNKNOWN == curr_state)
	{
		if(!divisor)
		{	if(dividend->digit)
				return DIVISION_POSSIBLE;
			else
				return UNKNOWN;
		}
		if((dividend->digit) < (divisor->digit))
			return DIVISION_NOT_POSSIBLE;
		if((dividend->digit) == (divisor->digit))
			return UNKNOWN;
		else
			return DIVISION_POSSIBLE;
	}
	
	return curr_state;
}

uint32_t calculate_quotient(node* dividend, node* divisor)
{
	uint8_t carry = 0;
	uint32_t subtraction_count = 0;
	node* start_node_dividend = dividend;
	node* start_node_divisor = divisor;
	
	while(1)
	{
		dividend = start_node_dividend;
		divisor  = start_node_divisor;
		while(dividend)
		{
			do 
			{
				if(carry)
				{
					if(!(dividend->digit))
						dividend->digit = TEN - 1;
					else
					{
						carry = 0;
						(dividend->digit)--;
					}
				}
				
				if(divisor)
					break;
				
				dividend = dividend->next;
			}while(carry && dividend);
			
			if(!divisor)
				break;
			
			if(dividend->digit < divisor->digit)
			{
				carry = 1;
				dividend->digit = dividend->digit + TEN;
			}	
			
			dividend->digit = dividend->digit - divisor->digit;
			
			dividend = dividend->next;
			divisor  = divisor->next;
		}
		subtraction_count++;

		state_t curr_state = is_division_finished(start_node_dividend, start_node_divisor);
		if(DIVISION_NOT_POSSIBLE == curr_state)
			break;
	}
	
	return subtraction_count;
}

void find_quotient(node* dividend, node* divisor)
{
	node* reverse_dividend = create_reversed_list(dividend);
	node* reverse_divisor  = create_reversed_list(divisor);
	
	printf("Reversed dividend :\n");
	display_list(reverse_dividend);
	
	printf("Reversed divisor :\n");
	display_list(reverse_divisor);
	
	if(DIVISION_NOT_POSSIBLE == is_division_finished(reverse_dividend, reverse_divisor))
	{
		printf("Division not possible.\n");
		return;
	}
	
	printf("Quotient = %u\n",calculate_quotient(reverse_dividend, reverse_divisor));
	
	printf("Remainder :\n");
	reverse_dividend = reverse_list(reverse_dividend);
	display_list(reverse_dividend);
}

int main()
{
    node* dividend = NULL;
	node* divisor  = NULL;
	
	add_node(&dividend,1);
	add_node(&dividend,2);
	add_node(&dividend,0);
	
	printf("Dividend list :\n");
	display_list(dividend);
	
	add_node(&divisor,2);
	add_node(&divisor,5);
	
	printf("Divisor list :\n");
	display_list(divisor);
	
	find_quotient(dividend, divisor);
	
    return 0;
}
