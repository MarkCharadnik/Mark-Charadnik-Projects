/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#ifndef INPUT_H
#define INPUT_H

#include "map.h"

struct wolf_s;
struct player_s;

void handle_events(struct wolf_s *wolf);
void move_forward(struct player_s *p, struct map_s *map);
void move_backward(struct player_s *p, struct map_s *map);
void strafe_left(struct player_s *p, struct map_s *map);
void strafe_right(struct player_s *p, struct map_s *map);
void rotate_left(struct player_s *p);
void rotate_right(struct player_s *p);

#endif
