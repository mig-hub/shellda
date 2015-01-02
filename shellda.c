#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define MAP_W 48
#define MAP_H 12
#define SPEED 30000
#define RED_ON attron(COLOR_PAIR(1))
#define RED_OFF attroff(COLOR_PAIR(1))

/* Maps */

typedef struct {
  char sprites[MAP_H][MAP_W];
} map;

void map_draw(map * self) {
  int y, x;
  for (y = 0; y < MAP_H; y++) {
    for (x = 0; x < MAP_W; x++) {
      mvaddch(y,x,self->sprites[y][x]);
    }
  }
}

int map_walkable_q(map * self, int y, int x) {
  if (y<0||x<0) return 0;
  if (y>=MAP_H) return 0;
  if (x>=MAP_W) return 0;
  return self->sprites[y][x]==' ';
}

map room_1 = {
  {
    "################################################",
    "                                                ",
    "                                                ",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "################################################"
  }
};

map * current_map = &room_1;

/* Actors */

typedef struct {
  int y;
  int x;
  char face;
  int color;
} actor;

void actor_move(actor * self, char c) {
  int x = self->x, y = self->y;
  if (c=='h') x -= 1;
  if (c=='j') y += 1;
  if (c=='k') y -= 1;
  if (c=='l') x += 1;
  if (map_walkable_q(current_map,y,x)) {
    self->x = x;
    self->y = y;
  }
}

void actor_draw(actor * self) {
  attron(COLOR_PAIR(self->color));
  mvaddch(self->y,self->x,self->face);
  attroff(COLOR_PAIR(self->color));
}

actor hero = {10,10,'@',2};

/* Update */

void update() {
  char c = getch();
  if (c=='q') {
    endwin(); exit(0);
  }
  actor_move(&hero,c);
}

/* Draw */

int space_big_enough_q() {
  int maxx = 0, maxy = 0;
  getmaxyx(stdscr,maxy,maxx);
  return ((maxy>=MAP_H)&&(maxx>=MAP_W));
}

void space_warning() {
  RED_ON;
  mvprintw(0,0,"The space is not big enough to play this game. You need at least %dx%d.",MAP_W,MAP_H);
  RED_OFF;
}

void draw() {
  clear();
  if (space_big_enough_q()) {
    map_draw(current_map);
    actor_draw(&hero);
  } else {
    space_warning();
  }
  refresh();
}

/* Colors */

void ensure_colors() {
  if (has_colors()==FALSE) {
    endwin();
    printf("Your terminal does not support colors.\nWTF?!?\n");
    exit(1);
  }
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

/* Main */

int main(int argc, const char *argv[]) {
  initscr();
  noecho(); cbreak();
  curs_set(FALSE);
  ensure_colors();
  while(1) {
    draw();
    update();
    usleep(SPEED);
  }
  endwin();
  return 0;
}

