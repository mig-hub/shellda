#include "map.h"

void map_draw(map * self) {
  int y, x;
  for (y = 0; y < MAP_H; y++) {
    for (x = 0; x < MAP_W; x++) {
      map_draw_sprite(self,y,x);
    }
  }
}

void map_draw_sprite(map * self, int y, int x) {
  char sprite = self->sprites[y][x];
  if (has_colors()==TRUE) attron(COLOR_PAIR(sprite));
  mvaddch(y,x,sprite);
  if (has_colors()==TRUE) attroff(COLOR_PAIR(sprite));
}

int map_walkable_q(map * self, int y, int x) {
  if (y<0||x<0) return 0;
  if (y>=MAP_H) return 0;
  if (x>=MAP_W) return 0;
  return self->sprites[y][x]==' ';
}

