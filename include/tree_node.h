#ifndef TREENODE_H
#define NODE_H

/*
    TreeNode in data structure (binary search tree)

    Ownership rules (rules for managing memory):
    - TreeNodes are always heap allocated with node_create
    - TreeNodes are always freed with node_destroy
    - The List owns the nodes NOT the caller (Caller = the code (func.) that calls another func.)
*/
typedef struct TreeNode
{
    int data;
    // no need for parent if iterative (non recursive) algos are not used
    // struct TreeNode *parent;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
    Allocates memory on the heap for a new TreeNode
    Ownership of returned pointer is transferred to caller
*/
TreeNode *node_create(int data); // (int data, TreeNode *parent);

/*
    Frees memory allocated for a TreeNode
    The pointer is INVALID after this call
*/
void node_destroy(TreeNode *node);

#endif