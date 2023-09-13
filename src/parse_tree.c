#include "../include/parse_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../include/stack_str.h"


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
			buffer[idx++] = ' ';
			sp_count++;
		}
		else buffer[idx++] = read_char;
	}
	buffer[idx] = 0;
	return sp_count;
}
