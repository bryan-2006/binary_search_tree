#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/tree.h"
#include "lib/singly_linked/include/list.h"

/*
    $ gcc -Wall -Wextra -Werror -fsanitize=address -g main.c src/tree.c \
        src/tree_node.c lib/singly_linked/src/list.c lib/singly_linked/src/list_node.c\
        -o binary_search_tree_test

    if using

    $ valgrind --leak-check=full ./binary_search_tree_test

    dont compile with -fsanitize=address because valgrind and ASan conflicts with each other.
    -fsanitize=address is a runtime memory checker.
    Not sure the difference as of now.
*/

static int fill_array_from_list(List *list, int **out_array) // pointer to pointer
{                                                            //  ^ allows func to change the pointer passed in
    int count = 0;
    ListNode *current = list->head;
    while (current)
    {
        count++;
        current = current->next;
    }

    int *values = malloc(count * sizeof(int));
    current = list->head;
    for (int i = 0; i < count; i++)
    {
        values[i] = current->data;
        current = current->next;
    }

    *out_array = values; // we change the argument pointer to pointer to *values

    // so the pointer to the pointer (value in main) is changed to value (the one we declared w/in func)
    return count;
}

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

        if (sscanf(input, "add %d", &data) == 1)
        {
            if (!tree_add(tree, data))
            {
                fprintf(stderr, "Allocation failed (make sure value is not a duplicate)\n");
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
            List *list = tree_preorder(tree);

            // THIS WILL PRINT BACKWARDS (tail to head)

            // ListNode *current = list->head;

            // while (current)
            // {
            //     printf("%d -> ", current->data);
            //     current = current->next;
            // }

            // TO PREVENT THIS:

            int *values;
            int count = fill_array_from_list(list, &values);
            //                                     ^ "get the address of values"
            for (int i = count - 1; i >= 0; i--)
            {
                printf("%d -> ", values[i]);
            }
            free(values);
            list_destroy(list);
            printf("NULL\n");
        }
        else if (strcmp(input, "inorder") == 0)
        {
            List *list = tree_inorder(tree);
            int *values;
            int count = fill_array_from_list(list, &values);
            //                                     ^ "get the address of values"
            for (int i = count - 1; i >= 0; i--)
            {
                printf("%d -> ", values[i]);
            }
            free(values);
            list_destroy(list);
            printf("NULL\n");
        }
        else if (strcmp(input, "postorder") == 0)
        {
            List *list = tree_postorder(tree);
            int *values;
            int count = fill_array_from_list(list, &values);
            //                                     ^ "get the address of values"
            for (int i = count - 1; i >= 0; i--)
            {
                printf("%d -> ", values[i]);
            }
            free(values);
            list_destroy(list);
            printf("NULL\n");
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

    tree_destroy(tree); // Free the tree and its nodes
}

// Tried this but to print I need count so that's why the new static function exists
// (to fill out array aka the stack, return the count of nodes, and have the stack pointer returned via double pointer)
//
// static int *reverse_linked(List *list)
// {
//     int count = 0; // get count of nodes in list

//     ListNode *current = list->head;
//     while (current)
//     {
//         count++;
//         current = current->next;
//     }

//     int *values = malloc(count * sizeof(int)); // make "stack" for data from linked list

//     current = list->head;

//     for (int i = 0; i < count; i++) // start from the back of the array...
//     {
//         values[i] = current->data;
//         current = current->next; // ...move to the front
//     }

//     for (int i = count - 1; i >= 0; i--) // print stack from front to back)
//     {
//         printf("%d -> ", values[i]);
//     }

//     // free(values);
//     return values;
// }
