#include <limits.h>
#include "rb_trees.h"

/**
 * is_bst - checks if a tree is a valid BST
 * @tree: pointer to root node
 * @min: minimum value
 * @max: maximum value
 * Return: 1 if valid BST, 0 otherwise
 */
int is_bst(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst(tree->left, min, tree->n) &&
		is_bst(tree->right, tree->n, max));
}

/**
 * count_black_nodes - counts black nodes from root to leaf
 * @tree: pointer to current node
 * Return: number of black nodes, -1 if invalid
 */
int count_black_nodes(const rb_tree_t *tree)
{
	int left_black, right_black;

	if (!tree)
		return (1);

	left_black = count_black_nodes(tree->left);
	right_black = count_black_nodes(tree->right);

	if (left_black == -1 || right_black == -1 || left_black != right_black)
		return (-1);

	return (left_black + (tree->color == BLACK ? 1 : 0));
}

/**
 * check_red_property - checks if red nodes don't have red children
 * @tree: pointer to current node
 * Return: 1 if valid, 0 otherwise
 */
int check_red_property(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->color == RED)
	{
		if ((tree->left && tree->left->color == RED) ||
			(tree->right && tree->right->color == RED))
			return (0);
	}

	return (check_red_property(tree->left) && check_red_property(tree->right));
}

/**
 * rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
 * @tree: pointer to the root node of the tree to check
 * Return: 1 if tree is a valid Red-Black Tree, 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	if (!tree)
		return (0);

	if (tree->color != BLACK)
		return (0);

	if (!is_bst(tree, INT_MIN, INT_MAX))
		return (0);

	if (!check_red_property(tree))
		return (0);

	if (count_black_nodes(tree) == -1)
		return (0);

	return (1);
}