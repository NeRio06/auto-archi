#include "../include/parse_tree.h"
#include "../include/stack_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#define IS_ABSOLUTE(c) (c[0] == '~' || c[0] == '/')
#include <string.h>
#include <malloc.h>
#include<sys/stat.h>



int file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp != NULL)
    {
        fclose(fp);
	return 1; 
    }
    return 0;
}

int directory_exists(const char *path)
{
    struct stat stats;

    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

void exit_help()
{
    char help[] =
        "\nUsage:\n tree-file path-build-directory";

    errx(1, "%s", help);
}

int main(int argc, char** argv){
	if (argc != 3)
		exit_help();

	char* tree_path = malloc(MAX_PATH); 
	char* build_path = malloc(MAX_PATH);

	if (!tree_path || ! build_path){
		errx(1,"Error: Memory allocatio failed.\n");
	}	

	if (IS_ABSOLUTE(argv[1]) && IS_ABSOLUTE(argv[2])){
		strcpy(tree_path,argv[1]);
		size_t len_tree = strlen(tree_path);
		if (tree_path[len_tree-1] == '/')
			tree_path[len_tree-1] = 0;

		strcpy(build_path,argv[2]);
		size_t len_build = strlen(build_path);
		if (build_path[len_build-1] == '/')
			build_path[len_build-1] = 0;
	}
	else {
		size_t i = 0, i2 = 0;
		char cwd[MAX_PATH];
		if (!getcwd(cwd,sizeof(cwd))){
			errx(2,"Error: Cannot retrieve current working directory.\n");
		}
		if (!IS_ABSOLUTE(argv[1])){
			for(;cwd[i];i++){
				tree_path[i] = cwd[i];	
			}
			tree_path[i++] = '/';
			for(;argv[1][i2];i++,i2++){
				tree_path[i] = argv[1][i2];
			}
			if (tree_path[i-1] == '/') i--;
			tree_path[i] = 0;
	
		}
		if (!IS_ABSOLUTE(argv[2])){
                        for(i = 0;cwd[i];i++){
				build_path[i] = cwd[i];
			}
                        build_path[i++] = '/';
                        for(i2 = 0;argv[2][i2];i++,i2++){
				build_path[i] = argv[2][i2];
			}
                        if (build_path[i-1] == '/') i--;
                        build_path[i] = 0;
		}
        }
	if (!file_exists(tree_path)){
		errx(3,"Error: The file %s does not exist.\n",tree_path);
	}
	if (!directory_exists(build_path)){
		errx(4,"Error : The directory %s does not exist.\n",build_path);
	}
	FILE* flux = fopen(tree_path,"r");
	if (flux == NULL){
		errx(5,"Error : Cannot open the file %s\n",tree_path);
	}
	parse_tree(flux,build_path);
	//remove(tree_path);
}

