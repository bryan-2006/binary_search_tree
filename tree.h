#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include <stdbool.h>

/*
    A Tree is container that owns multiple Nodes which have parent/child relationships

    Ownership rules:
    - Tree is heap allocated with tree_create
    - Destoying tree (with tree_destroy) frees all owned Nodes
    - Owns all Nodes reachable from its root
*/
typedef struct
{
    TreeNode *root; // Pointer to the root node of the Tree (or NULL if empty)
    int size;
} Tree;

/*
    Allocates memory on the heap for a new Tree
    Ownership of returned pointer is transferred to caller
*/
Tree *tree_create(void);

/*
    Frees memory allocated for a Tree and all its owned Nodes
    The pointer is INVALID after this call
*/
void tree_destroy(Tree *tree);

/*
    Adds a new Node with the given data to the Tree.
    Return false if memory allocation fails.
*/
bool tree_add(Tree *tree, int data);

/*
    Removes the Node that contains the given data.
    Frees removed Node's memory.
*/
bool tree_remove(Tree *tree, int data);

#endif