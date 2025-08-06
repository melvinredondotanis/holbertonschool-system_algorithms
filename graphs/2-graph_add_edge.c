#include "graphs.h"
#include <stdlib.h>
#include <string.h>

int graph_add_edge(graph_t *graph, const char *src, const char *dest,
	edge_type_t type)
{
	vertex_t *src_vertex, *dest_vertex;
	edge_t *new_edge, *edge_ptr;

	if (!graph || !src || !dest ||
		(type != UNIDIRECTIONAL && type != BIDIRECTIONAL))
		return (0);
	src_vertex = graph->vertices;
	while (src_vertex && strcmp(src_vertex->content, src) != 0)
		src_vertex = src_vertex->next;
	dest_vertex = graph->vertices;
	while (dest_vertex && strcmp(dest_vertex->content, dest) != 0)
		dest_vertex = dest_vertex->next;
	if (!src_vertex || !dest_vertex)
		return (0);
	new_edge = calloc(1, sizeof(edge_t));
	if (!new_edge)
		return (0);
	new_edge->dest = dest_vertex;
	if (src_vertex->edges == NULL)
		src_vertex->edges = new_edge;
	else
	{
		edge_ptr = src_vertex->edges;
		while (edge_ptr->next)
			edge_ptr = edge_ptr->next;
		edge_ptr->next = new_edge;
	}
	if (type == BIDIRECTIONAL)
	{
		edge_t *reverse_edge = calloc(1, sizeof(edge_t));

		if (!reverse_edge)
		{
			free(new_edge);
			return (0);
		}
		reverse_edge->dest = src_vertex;
		if (dest_vertex->edges == NULL)
			dest_vertex->edges = reverse_edge;
		else
		{
			edge_ptr = dest_vertex->edges;
			while (edge_ptr->next)
				edge_ptr = edge_ptr->next;
			edge_ptr->next = reverse_edge;
		}
	}
	return (1);
}
