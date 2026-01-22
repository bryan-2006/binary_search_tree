#include <stdlib.h>
#include "tree_node.h"

TreeNode *node_create(int data, TreeNode *parent)
{
    TreeNode *node = malloc(sizeof(TreeNode)); // allocate memory for a TreeNode

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

void node_destroy(TreeNode *node)
{
    free(node);
}