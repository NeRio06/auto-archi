#include "../include/parse_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../include/stack_str.h"
#include <string.h>
#include <err.h>
#define MAX_PATH 256
#include <sys/stat.h>

size_t read_line(FILE *flux,char *buffer){
	size_t idx =  0;
	size_t sp_count = 0;
	char read_char;
	while ((read_char = fgetc(flux)) && read_char != -1 && read_char != '\n'){
		if (read_char < 0 || read_char == ' '){
			size_t read_needed = 0;
			switch(read_char){
				case -62:
				case 32:
					read_needed = 0;
					break;
				case -30:
				case -96:
				case -108:
					read_needed = 2;
					break;
				default :
					read_needed = 0;
					break;
			}
			for(size_t i = 0; i < read_needed;i++){
				read_char = fgetc(flux);
			}
			sp_count++;
		}
		else buffer[idx++] = read_char;
	}
	buffer[idx] = 0;
	return sp_count;
}

void sum_path(char *path,char *add){
	size_t i = 0;
	for(;path[i];i++);
	path[i++] = '/';
	for(size_t j = 0;add[j];path[i++] = add[j++]);
	path[i] = 0;
}

void parse_tree(FILE *flux,char* build_path){
	t_stack_str* stk = init_stack_str();
	if (!stk) {
		errx(5,"Error : Creation of stack failed.\n");
	}
	stack_push_str(stk,build_path);
					
	char current_line[MAX_PATH];
	char next_line[MAX_PATH];
	char current_path[MAX_PATH];
	
	size_t current_step = 0, next_step = 0;
	current_step = read_line(flux,current_line);
	while(!stack_empty_str(stk)){
		if (current_step == 0) goto finish;
		next_step = read_line(flux,next_line);

	
		stack_peek_str(stk,current_path);
		sum_path(current_path,current_line);
		printf("current path : %s\n",current_path);
		if (next_step <= current_step){//FILE
			FILE *new_file = fopen(current_path,"w");
			if (new_file){
				fclose(new_file);
			}
			else errx(6,"Error creating the file: %s\n",current_path);
			if (next_step < current_step){
				for(size_t k = 0; k < (current_step-next_step)/4;k++){
					stack_pop_str(stk);
				}
			}
		}
		else {//DIR
			if (mkdir(current_path, 0777)){
				errx(7,"Error creating the directory: %s\n",current_path);
			}
			stack_push_str(stk,current_path);
		}
		current_step = next_step;
		strcpy(current_line,next_line);	
	}
finish:
	free_stack_str(stk);
}
