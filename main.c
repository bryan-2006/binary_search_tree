#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// $ gcc -Wall -Wextra -Werror -fsanitize=address -g \
        main.c tree.c node.c -o binary_search_tree_test

// $ ./binary_search_tree_test

int main(void)
{
    Tree *tree = tree_create();
    if (!tree)
    {
        fprintf(stderr, "Failed to create tree\n");
        return 1;
    }

    char input[16];

    printf("Binary Search Tree Interactive Test\n");
    printf("Commands: add <int>, remove <int>, <pre/in/post>order, exit\n");

    while (1)
    {
        printf("> ");

        // Read a full line from stdin
        if (!fgets(input, sizeof(input), stdin))
        {
            // EOF or error -> exit loop safely
            break;
        }

        input[strcspn(input, "\n")] = 0; // Remove newline character if present

        int data;

        if (sscanf(input, "push %d", &data) == 1)
        {
            if (!tree_add(tree, data))
            {
                fprintf(stderr, "Allocation failed\n");
            }
        }
        else if (sscanf(input, "remove %d", &data) == 1)
        {
            if (!tree_remove(tree, data))
            {
                printf("Value not found\n");
            }
        }
        else if (strcmp(input, "preorder") == 0)
        {
        }
        else if (strcmp(input, "inorder") == 0)
        {
        }
        else if (strcmp(input, "postorder") == 0)
        {
        }
        else if (strcmp(input, "exit") == 0)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Unknown command\n");
        }
    }

    list_destroy(tree); // Free the list and its nodes
}