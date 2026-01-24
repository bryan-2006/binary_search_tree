#include <stdlib.h>
#include "../include/tree.h"

Tree *tree_create(void)
{
    Tree *tree = malloc(sizeof(Tree)); // allocate memory for a Tree

    if (!tree)
    {
        return NULL; // return NULL if memory allocation fails
    }

    tree->root = NULL; // initialize root to NULL
    tree->size = 0;    // initialize size to 0
    return tree;       // return pointer to the newly created tree
}

static void destroy_subtree(TreeNode *node)
{
    if (node == NULL)
    {
        return;
    }

    destroy_subtree(node->left);
    destroy_subtree(node->right);
    tree_node_destroy(node);
}

void tree_destroy(Tree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    destroy_subtree(tree->root);
    free(tree);
}

static TreeNode *insert_node(TreeNode *node, int data, bool *inserted)
{
    // root and when nonexistent child of a leaf
    if (node == NULL)
    {
        *inserted = true;
        return tree_node_create(data);
    }

    // traverse down tree to get to a spot that data can be placed
    if (data < node->data)
    { // if data is smaller then move to left of parent
        node->left = insert_node(node->left, data, inserted);
    }
    else if (data > node->data)
    { // data is bigger so traverse to right subtree
        node->right = insert_node(node->right, data, inserted);
    }
    else
    {                      // duplicate so don't add
        *inserted = false; // value set to false with dereferencing op.
    }

    return node;
}

bool tree_add(Tree *tree, int data)
{
    if (tree == NULL)
    {
        return false;
    }

    bool inserted = false;
    tree->root = insert_node(tree->root, data, &inserted);
    // addr of operator (eval. to mem address) ^
    if (inserted)
    {
        tree->size++;
    }
    return inserted;
}

TreeNode *find_min(TreeNode *node)
{
    if (node == NULL) // not needed because always called with valid node, but good practice
    {
        return NULL;
    }

    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

static TreeNode *remove_node(TreeNode *node, int data, bool *removed)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (data < node->data)
    { // if data is smaller then move to left of parent
        node->left = remove_node(node->left, data, removed);
    }
    else if (data > node->data)
    { // data is bigger so traverse to right subtree
        node->right = remove_node(node->right, data, removed);
    }
    else
    { // found the node to remove
        *removed = true;

        // node to remove is a leaf or only has 1 child
        if (node->left == NULL)
        {                                  // since there is nothing to the left save right so it replaces the nodes place
            TreeNode *right = node->right; // save so that it can be returned
            tree_node_destroy(node);
            return right;
        }
        if (node->right == NULL)
        {
            TreeNode *left = node->left; // save so that it can be returned
            tree_node_destroy(node);
            return left;
        }

        // node to remove has 2 children
        // find the inorder successor (smallest in the right subtree)
        TreeNode *successor = find_min(node->right);
        node->data = successor->data; // copy the successor's data to this node

        // remove the successor node from the right subtree (the original which is a dupe as of now)
        node->right = remove_node(node->right, successor->data, removed);
    }

    return node;
}

bool tree_remove(Tree *tree, int data)
{
    if (tree == NULL)
    {
        return false;
    }

    bool removed = false;
    tree->root = remove_node(tree->root, data, &removed);
    if (removed)
    {
        tree->size--;
    }
    return removed;
}

static void preorder_helper(TreeNode *node, List *list)
{
    if (node == NULL)
    {
        return;
    }

    // move from root to left to right
    list_push(list, node->data);
    preorder_helper(node->left, list);
    preorder_helper(node->right, list);
}

List *tree_preorder(Tree *tree)
{
    List *list = list_create();

    preorder_helper(tree->root, list);

    return list;
};

static void inorder_helper(TreeNode *node, List *list)
{
    if (node == NULL)
    {
        return;
    }

    // move from left to root to right
    inorder_helper(node->left, list);
    list_push(list, node->data);
    inorder_helper(node->right, list);
}

List *tree_inorder(Tree *tree)
{
    List *list = list_create();

    inorder_helper(tree->root, list);

    return list;
};

static void postorder_helper(TreeNode *node, List *list)
{
    if (node == NULL)
    {
        return;
    }

    // move from right to left to root
    postorder_helper(node->left, list);
    postorder_helper(node->right, list);
    list_push(list, node->data);
}

List *tree_postorder(Tree *tree)
{
    List *list = list_create();

    postorder_helper(tree->root, list);

    return list;
};