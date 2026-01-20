#ifndef NODE_H
#define NODE_H

/*
    Node in data structure (binary search tree)

    Ownership rules (rules for managing memory):
    - Nodes are always heap allocated with node_create
    - Nodes are always freed with node_destroy
    - The List owns the nodes NOT the caller (Caller = the code (func.) that calls another func.)
*/
typedef struct Node
{
    int data;
    // no need for parent if iterative (non recursive) algos are not used
    // struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

/*
    Allocates memory on the heap for a new Node
    Ownership of returned pointer is transferred to caller
*/
Node *node_create(int data); // (int data, Node *parent);

/*
    Frees memory allocated for a Node
    The pointer is INVALID after this call
*/
void node_destroy(Node *node);

#endif