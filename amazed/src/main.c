/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

int main(int argc, char **argv)
{
    maze_data_t *maze;
    int max_vertex;
    graph_s *graph;

    (void)argc;
    (void)argv;
    maze = read_input();
    if (maze == NULL) {
        return 84;
    }
    max_vertex = get_max_vertex(maze->lines);
    graph = init_maze_graph(max_vertex + 1);
    if (graph == NULL) {
        return 84;
    }
    build_graph_from_links(max_vertex + 1, maze->lines);
    free_maze(maze);
    free_graph(graph);
    return 0;
}
