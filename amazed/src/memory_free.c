/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

void free_maze(maze_data_t *maze)
{
    int i = 0;

    if (!maze)
        return;
    while (maze->lines && maze->lines[i]) {
        free(maze->lines[i]);
        i = i + 1;
    }
    free(maze->lines);
    free(maze);
}

void free_graph(graph_s *graph)
{
    int i = 0;
    adjacency_node_t *curr;
    adjacency_node_t *next;

    if (!graph)
        return;
    for (i = 0; i < graph->vertex_count; i++) {
        curr = graph->adj_lists[i];
        while (curr != NULL) {
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->adj_lists);
    free(graph);
}
