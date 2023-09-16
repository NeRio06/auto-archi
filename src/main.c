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



static int file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp != NULL)
    {
        fclose(fp);
	return 1; 
    }
    return 0;
}

static int directory_exists(const char *path)
{
    struct stat stats;

    stat(path, &stats);

    // Check for file existence
    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

static void exit_help()
{
    char help[] =
        "Usage: "
	"archi [OPTIONS] tree-file-path [build-path]\n"
	"\t-a login\t Specify a login firstname.name for the operation (required if -a is used).\n"
	"\t-r      \t  Remove tree-file after the process.\n";

    errx(1, "%s", help);
}

static void valid_login(const char *login){
	size_t idx = 0;
	for(;login[idx] && login[idx] >= 'a' && login[idx] <= 'z';idx++);
	if(!idx || login[idx++] != '.') 
		errx(1,"Error: login invalid syntax, should be firstname.name /!\\ lowercase.\n");
	size_t idx2 = idx;
	for(;login[idx] && login[idx] >= 'a' && login[idx] <= 'z';idx++);
	if (idx == idx2 || login[idx]) 
		errx(1,"Error: login invalid syntax, should be firstname.name /!\\ lowercase.\n");
	
}

static void parse_path(char* buffer,char *input){
	if (*input && IS_ABSOLUTE(input)){
                strcpy(buffer,input);
                size_t len = strlen(buffer);
                if (buffer[len-1] == '/')
                        buffer[len-1] = 0;
	}
	else {
		if (!*input){
                	if (!getcwd(buffer,MAX_PATH)){
                        	errx(2,"Error: Cannot retrieve current working directory.\n");
			}
                }
		else{
			size_t i = 0, i2 = 0;
                	char cwd[MAX_PATH];
                	if (!getcwd(cwd,sizeof(cwd))){
                        	errx(2,"Error: Cannot retrieve current working directory.\n");
                	}
                        	
			for(;cwd[i];i++){
                                buffer[i] = cwd[i];
                        }
                        buffer[i++] = '/';
                        for(;input[i2];i++,i2++){
                                buffer[i] = input[i2];
                        }
                        if (buffer[i-1] == '/') i--;
                        buffer[i] = 0;
                }
	}
}

int main(int argc, char** argv){
	if (argc == 1)
		exit_help();
	int rm = 0;	
	char* login = NULL;
	char* tree_path = malloc(MAX_PATH); 
	char* build_path = malloc(MAX_PATH);
	build_path[0] = tree_path[0] = 0;

	if (!tree_path || ! build_path){
		errx(1,"Error: Memory allocation failed.\n");
	}
	
	for (int i = 1; i < argc;i++){
		if (!login && strcmp(argv[i],"-a") == 0){
			if (i + 1 < argc){
				valid_login(argv[i+1]);
				login = argv[i+1];
				i++;
			}
			else errx(1,"Error: -a option is always followed by login,should be -a firstname.name /!\\ lowercase.\n");
		}
		else if (!rm && strcmp(argv[i],"-r") == 0)
			rm = 1;
		else if (tree_path[0] == 0)
			parse_path(tree_path,argv[i]);
		else if (build_path[0] == 0) 
			parse_path(build_path,argv[i]);
		else exit_help();
	}
	if (!build_path[0]){
		parse_path(build_path,"");
	}
	
	if (!file_exists(tree_path)){
		errx(1,"Error: The file %s does not exist.\n",tree_path);
	}
	if (!directory_exists(build_path)){
		errx(1,"Error : The directory %s does not exist.\n",build_path);
	}
	FILE* flux = fopen(tree_path,"r");
	if (flux == NULL){
		errx(1,"Error : Cannot open the file %s\n",tree_path);
	}
	parse_tree(flux,build_path,login);
	if (rm) 
		remove(tree_path);
	fclose(flux);
	free(tree_path);
	free(build_path);
}

