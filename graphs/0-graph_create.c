#include "graphs.h"
#include "stdlib.h"

/**
 * graph_create - create new graph
 * Return: new node
 */
graph_t *graph_create(void)
{
	graph_t *new_graph = NULL;

	new_graph = malloc(sizeof(graph_t));
	if (!new_graph)
		return (NULL);

	new_graph->nb_vertices = 0;
	new_graph->vertices = NULL;
	return (new_graph);
}
