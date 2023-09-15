#include "../include/parse_tree.h"
#include "../include/stack_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#define IS_ABSOLUTE(c) c[0] == '~' || c[0] == '/'

void exit_help()
{
    char help[] =
        "Usage:\n path-tree-file path-build-directory";

    errx(1, "%s", help);
}

int main(int argc, char** argv){
	if (argc != 3)
		exit_help();

	char tree_path[MAX_PATH]; 
	char build_path[MAX_PATH];


	if (IS_ABSOLUTE(argv[1]) && IS_ABSOLUTE(argv[2])){
		strcpy(tree_path,argv[1]);
		strcpy(build_path,argv[2]);
	}
	else {
		size_t i = 0, i2 = 0;
		char cwd[MAX_PATH];
		if (!getcwd(cwd,sizeof(cwd))){
			errx(2,"Error: Cannot retrieve current working directory\n");
		}
		if (!IS_ABSOLUTE(argv[1])){
			for(;cwd[i];tree_path[i] = cwd[i++]);
			tree_path[i++] = '/';
			for(;argv[1][i2];tree_path[i] = argv[1][i2]);
			if (tree_path[i-1] == '/') i--;
			tree_path[i] = 0;
	
		}
	}
	FILE *flux = fopen("/home/mathis/epita/auto-archi/tree","r");
	if (!flux){
		errx(1,"Error opening the file: %s\n",three_path);
	}
//	parse_tree(flux,buildpath);
}
