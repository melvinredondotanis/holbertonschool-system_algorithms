#include "heap.h"
#include <stdlib.h>

binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new_node = calloc(1, sizeof(*new_node));

	if (!new_node)
		return (NULL);

	new_node->parent = parent;
	new_node->data = data;
	return (new_node);
}
