#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * graph_add_vertex - Add a new vertex to the graph
 * @graph: Pointer to the graph structure
 * @str: Content of the new vertex
 * Return: Pointer to the new vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *vertex;

	if (!graph || !str)
		return (NULL);

	vertex = graph->vertices;
	while (vertex)
	{
		if (!strcmp(vertex->content, str))
			return (NULL);
		if (!vertex->next)
			break;
		vertex = vertex->next;
	}

	new_vertex = calloc(1, sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index = graph->nb_vertices++;
	if (vertex)
	{
		vertex->next = new_vertex;
		return (new_vertex);
	}
	graph->vertices = new_vertex;
	return (new_vertex);
}
