#include <stdlib.h>
#include "rb_trees.h"

/**
 * rotate_left - Performs left rotation
 * @tree: Double pointer to root
 * @node: Node to rotate
 */
void rotate_left(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *right_child = node->right;

    node->right = right_child->left;
    if (right_child->left)
        right_child->left->parent = node;

    right_child->parent = node->parent;
    if (!node->parent)
        *tree = right_child;
    else if (node == node->parent->left)
        node->parent->left = right_child;
    else
        node->parent->right = right_child;

    right_child->left = node;
    node->parent = right_child;
}

/**
 * rotate_right - Performs right rotation
 * @tree: Double pointer to root
 * @node: Node to rotate
 */
void rotate_right(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *left_child = node->left;

    node->left = left_child->right;
    if (left_child->right)
        left_child->right->parent = node;

    left_child->parent = node->parent;
    if (!node->parent)
        *tree = left_child;
    else if (node == node->parent->right)
        node->parent->right = left_child;
    else
        node->parent->left = left_child;

    left_child->right = node;
    node->parent = left_child;
}

/**
 * fix_insertion - Fixes Red-Black Tree violations after insertion
 * @tree: Double pointer to root
 * @node: Node that was inserted
 */
void fix_insertion(rb_tree_t **tree, rb_tree_t *node)
{
    rb_tree_t *parent, *grandparent, *uncle;

    while (node->parent && node->parent->color == RED)
    {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (uncle && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    node = parent;
                    rotate_left(tree, node);
                    parent = node->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotate_right(tree, grandparent);
            }
        }
        else
        {
            uncle = grandparent->left;
            if (uncle && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    node = parent;
                    rotate_right(tree, node);
                    parent = node->parent;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                rotate_left(tree, grandparent);
            }
        }
    }
    (*tree)->color = BLACK;
}

/**
 * bst_insert - Inserts node using BST rules
 * @tree: Double pointer to root
 * @value: Value to insert
 *
 * Return: Pointer to inserted node, or NULL on failure
 */
rb_tree_t *bst_insert(rb_tree_t **tree, int value)
{
    rb_tree_t *current, *parent = NULL, *new_node;

    if (!*tree)
    {
        *tree = rb_tree_node(NULL, value, BLACK);
        return (*tree);
    }

    current = *tree;
    while (current)
    {
        parent = current;
        if (value < current->n)
            current = current->left;
        else if (value > current->n)
            current = current->right;
        else
            return (NULL); /* Value already exists */
    }

    new_node = rb_tree_node(parent, value, RED);
    if (!new_node)
        return (NULL);

    if (value < parent->n)
        parent->left = new_node;
    else
        parent->right = new_node;

    return (new_node);
}

/**
 * rb_tree_insert - Inserts a value in a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black tree
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
    rb_tree_t *new_node;

    if (!tree)
        return (NULL);

    new_node = bst_insert(tree, value);
    if (!new_node)
        return (NULL);

    if (new_node->parent)
        fix_insertion(tree, new_node);

    return (new_node);
}