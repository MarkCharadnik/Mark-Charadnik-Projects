/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

static adjacency_node_t *new_adj_node(int vertex)
{
    adjacency_node_t *node;

    node = malloc(sizeof(adjacency_node_t));
    if (node == NULL)
        return NULL;
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

static int is_out_of_bounds(graph_s *graph, int from, int to)
{
    if (from < 0 || from >= graph->vertex_count)
        return 1;
    if (to < 0 || to >= graph->vertex_count)
        return 1;
    return 0;
}

static void append_node(graph_s *graph, int from, adjacency_node_t *node)
{
    adjacency_node_t *curr;

    curr = graph->adj_lists[from];
    if (curr == NULL)
        graph->adj_lists[from] = node;
    else {
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = node;
    }
}

void insert_edge(graph_s *graph, int from, int to)
{
    adjacency_node_t *node;

    if (is_out_of_bounds(graph, from, to) == 1)
        return;
    node = new_adj_node(to);
    if (node == NULL)
        return;
    append_node(graph, from, node);
}

graph_s *init_graph(int vertices)
{
    graph_s *graph;
    int i;

    graph = malloc(sizeof(graph_s));
    if (graph == NULL)
        return NULL;
    graph->vertex_count = vertices;
    graph->adj_lists = malloc(sizeof(adjacency_node_t *) * vertices);
    if (graph->adj_lists == NULL) {
        free(graph);
        return NULL;
    }
    for (i = 0; i < vertices; i = i + 1)
        graph->adj_lists[i] = NULL;
    return graph;
}

static int parse_tunnel_and_insert(graph_s *graph, char *line)
{
    int src;
    int dest;

    if (is_tunnel_format(line) != 1)
        return 0;
    src = char_to_num(line[0]);
    dest = char_to_num(line[2]);
    if (src < 0 || dest < 0)
        return 0;
    insert_edge(graph, src, dest);
    insert_edge(graph, dest, src);
    return 1;
}

graph_s *build_graph_from_links(__attribute__((unused)) int size, char **lines)
{
    int vertex_count;
    graph_s *graph;
    int i;

    vertex_count = count_rooms_in_array(lines);
    graph = init_graph(vertex_count);
    if (graph == NULL)
        return NULL;
    for (i = 0; lines[i] != NULL; i = i + 1) {
        parse_tunnel_and_insert(graph, lines[i]);
    }
    return graph;
}

graph_s *init_maze_graph(int vertices)
{
    graph_s *graph;
    int i;

    graph = malloc(sizeof(graph_s));
    if (graph == NULL)
        return NULL;
    graph->vertex_count = vertices;
    graph->adj_lists = malloc(sizeof(adjacency_node_t *) * vertices);
    if (graph->adj_lists == NULL) {
        free(graph);
        return NULL;
    }
    for (i = 0; i < vertices; i = i + 1)
        graph->adj_lists[i] = NULL;
    return graph;
}
