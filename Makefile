#    $ gcc -Wall -Wextra -Werror -fsanitize=address -g main.c src/tree.c \
#        src/tree_node.c lib/singly_linked/src/list.c lib/singly_linked/src/list_node.c\
#        -o binary_search_tree_test

# $ make
# $ make all
# ^ runs default target ("all" which is why its the same) which builds the exec file
# any updated .c file is recompiled and relinked
#
# after this we can run 
# $ ./binary_search_tree_test
#
# $ make clean
# ^ removes all .o files and the exec file
#
# $ make clean && make 
# ^ cleans and rebuilds everything from scratch

# compiler
CC = gcc
# enable "all" warning, extra warnings, treat warnings as errors, address sanitizer, and debug info
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g 

# exec name
TARGET = binary_search_tree_test

####################################################################################################
# preprocessing (src) -> compiler (expand code) -> assembler (asm) -> linker (libs and obj) > exec #
####################################################################################################


# for header files
INCLUDES = -I./include -I./lib/singly_linked/include

# source files
BST_SRC = main.c src/tree.c src/tree_node.c
SLL_SRC = lib/singly_linked/src/list.c lib/singly_linked/src/list_node.c

# object files
BST_OBJ = $(BST_SRC:.c=.o) 
SLL_OBJ = $(SLL_SRC:.c=.o)

OBJS = $(BST_OBJ) $(SLL_OBJ)

# build all (default target)
all: $(TARGET)

# linker (link .o -> exec)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# compiler (.c -> .o)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean up
.PHONY: all clean
# imagine a file called clean exists. without .PHONY, typing "make clean" would not work because
# make would think the "clean" file (if smth like that exists) is up to date and would not run the 
# commands. With .PHONY, make knows "clean" is not a file but a command to run.
clean:
	rm -f $(OBJS) $(TARGET)

# memory test (NOT if -fsanitize=address is used)
# valgrind: $(TARGET)
# 	valgrind --leak-check=full ./$(TARGET)