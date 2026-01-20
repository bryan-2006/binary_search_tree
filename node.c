#include <stdlib.h>
#include "node.h"

Node *node_create(int data, Node *parent)
{
    Node *node = malloc(sizeof(Node)); // allocate memory for a Node

    if (!node)
    {
        return NULL; // return NULL if memory allocation fails
    }

    node->data = data;  // set the data
    node->left = NULL;  // initialize left to NULL
    node->right = NULL; // initialize right to NULL
    // no need for parent if iterative (non recursive) algos are not used
    // node->parent = parent; // initialize parent to *pointer or NULL
    return node; // return pointer to the newly created node
}

void node_destroy(Node *node)
{
    free(node);
}