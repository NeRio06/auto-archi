#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <stdio.h>

size_t read_line(FILE *flux,char* buffer);

void parse_tree(FILE *flux,char* build_path,char *login);

#endif
