#include <stdlib.h>
#include "rb_trees.h"

/**
 * rb_tree_node - Creates a new Red-Black tree node
 * @parent: Pointer to the parent node
 * @value: Integer value to be stored in the node
 * @color: Color of the node (RED or BLACK)
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{

	rb_tree_t *new_node = malloc(sizeof(rb_tree_t));

	if (!new_node)
		return (NULL);

	new_node->parent = parent;
	new_node->n = value;
	new_node->color = color;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
