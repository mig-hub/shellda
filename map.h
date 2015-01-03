#ifndef __map_h
#define __map_h

#include <ncurses.h>

#define MAP_W 48
#define MAP_H 12

typedef struct {
  char sprites[MAP_H][MAP_W];
} map;

void map_draw(map * self);
void map_draw_sprite(map * self, int y, int x);
int map_walkable_q(map * self, int y, int x);

#endif

