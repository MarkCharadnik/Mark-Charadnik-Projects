/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#ifndef AMAZED_COMBINED_H_
    #define AMAZED_COMBINED_H_

    #define _POSIX_C_SOURCE 200809L
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdbool.h>

typedef struct maze_data_s {
    int length;
    char **lines;
} maze_data_t;

typedef struct adjacency_node_s {
    int vertex;
    struct adjacency_node_s *next;
} adjacency_node_t;

typedef struct graph_s {
    int vertex_count;
    adjacency_node_t **adj_lists;
} graph_s;

int check_args_count(int argc, char **argv);
int is_digit_string(const char *str);
maze_data_t *read_input(void);
void free_graph(graph_s *graph);
void free_maze(maze_data_t *maze);
void strip_comments(char *line);
int my_getnbr_range(const char *str, int start, int end);
bool is_comment_line(char *line);
void output_data(maze_data_t *data);
void display_tunnels(maze_data_t *data);
void display_rooms(maze_data_t *data);
void output_robot_count(char *count);
int my_strcmp(const char *a, const char *b);
int my_strlen(const char *str);
char *my_strdup(const char *src);
char *my_strcpy(char *dest, const char *src);
int is_digit(char c);
int char_to_num(char c);
int is_room_format(char *str);
int is_tunnel_format(const char *str);
int get_max_vertex(char **arr);
int count_rooms_in_array(char **arr);
int parse_tunnel_verts(const char *line, int *src, int *dest);
graph_s *init_graph(int vertices);
graph_s *init_maze_graph(int vertices);
void insert_edge(graph_s *graph, int from, int to);
graph_s *build_graph_from_links(int size, char **input_lines);

#endif /* AMAZED_COMBINED_H_ */
