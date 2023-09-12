#include <stdio.h>
#include "../include/stack_str.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	t_stack_str* stk = init_stack_str();
	stack_push_str(stk,"Jeune");
	stack_push_str(stk,"Homme");
	stack_push_str(stk,"Le");
	stack_push_str(stk,"Masque");
	stack_push_str(stk,"C'est sur le nez");
	while (!stack_empty_str(stk)){
		char tab[255];
		stack_peek_str(stk,tab);
		printf("%s ",tab);
		stack_pop_str(stk);
	}
	return 0;
}
