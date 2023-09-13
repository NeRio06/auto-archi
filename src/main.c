#include "../include/parse_tree.h"
#include "../include/stack_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>

int main(){
	FILE *flux = fopen("/home/mathis/epita/auto-archi/tree","r");
	if (!flux){
		errx(1,"Cant open the tree file\n");
	}
	char tab[255] = {0};
	size_t step = 0;
	while ((step = read_line(flux,tab)) > 0){
		printf("step : %zu\n tab : %s\n",step,tab);
	}
	return 0;
}
