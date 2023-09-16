#ifndef STACK_STR_H
#define STACK_STR_H

#include <stddef.h>
#define MAX_PATH 256
typedef struct s_node_str{
        char* data;
        struct s_node_str *next;
} t_node_str;

typedef struct s_stack_str{
        size_t lenght;
        t_node_str *head;
} t_stack_str;

t_stack_str *init_stack_str(void);

void stack_peek_str(t_stack_str* stk,char *buffer);

void stack_push_str(t_stack_str* stk,char *data);

void stack_pop_str(t_stack_str* stk);

int stack_empty_str(t_stack_str* stk);

void free_stack_str(t_stack_str* stk);

#endif
