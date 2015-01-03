#ifndef __actor_h
#define __actor_h

#include <ncurses.h>
#include "map.h"

typedef struct {
  map * place;
  int y;
  int x;
  char face;
  int color;
} actor;

void actor_move(actor * self, char c);
void actor_draw(actor * self);

#endif

