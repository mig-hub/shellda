#include "actor.h"

void actor_move(actor * self, char c) {
  int x = self->x, y = self->y;
  if (c=='h') x -= 1;
  if (c=='j') y += 1;
  if (c=='k') y -= 1;
  if (c=='l') x += 1;
  if (map_walkable_q(self->place,y,x)) {
    self->x = x;
    self->y = y;
  }
}

void actor_draw(actor * self) {
  attron(COLOR_PAIR(self->color));
  mvaddch(self->y,self->x,self->face);
  attroff(COLOR_PAIR(self->color));
}

