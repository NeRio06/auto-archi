#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include "../include/stack_str.h"
#include <stdlib.h>

t_stack_str *init_stack_str(void){
	t_stack_str* new_list;
	
	if ((new_list = malloc(sizeof(t_stack_str)))){
		new_list->lenght = 0;
		new_list->head = NULL;
	}
	return new_list;
	
}

void stack_peek_str(t_stack_str* stk,char *buffer){
	if (!stack_empty_str(stk)){
		strcpy(buffer,stk->head->data);
	}
}

void stack_push_str(t_stack_str* stk,char *data){
	t_node_str * new_node;
	
	if ((new_node = malloc(sizeof(t_node_str)))){
		if ((new_node->data = malloc(sizeof(strlen(data))))){
			new_node->next = stk->head;
			stk->head = new_node;
			strcpy(new_node->data,data);
			stk->lenght++;
		}
	}
}

void stack_pop_str(t_stack_str* stk){
	if (!stack_empty_str(stk)){
		t_node_str* head = stk->head;
		stk->head = head->next;
		free(head->data);
		free(head);
		stk->lenght--;
	}
}

int stack_empty_str(t_stack_str* stk){
	return stk->lenght == 0;
}

void free_node_str(t_node_str* node){
        if (node){
                free_node_str(node->next);
                free(node->data);
                free(node);
        }
}

void free_stack_str(t_stack_str* stk){
	free_node_str(stk->head);
	free(stk);
}

