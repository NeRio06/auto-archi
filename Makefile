CC = gcc
CFLAGS = -Wall -Wextra

SRCS = src/main.c src/parse_tree.c src/stack_str.c
OBJS = $(SRCS:.c=.o)
EXEC = archi

INSTALL_PATH ?= /usr/local/bin

all : $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

install : all 
	cp $(EXEC) $(INSTALL_PATH)
	echo '$(INSTALL_PATH)' > .install_path

uninstall :
	rm $(shell cat .install_path)/$(EXEC)
	

clean :
	rm -f $(OBJS) $(EXEC)
