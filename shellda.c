#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"
#include "actor.h"

#define COLOR_WARN 300
#define RED_ON attron(COLOR_PAIR(COLOR_WARN))
#define RED_OFF attroff(COLOR_PAIR(COLOR_WARN))
#define SCHEME(c,fg,bg) (init_pair(c, COLOR_##fg, COLOR_##bg))

/* Global variables */

map room_1 = {
  {
    "################################################",
    "                                                ",
    "                                                ",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                          000                 #",
    "#                          00|                 #",
    "#~~~                       ||                  #",
    "#~~~~                                          #",
    "################################################"
  }
};

actor hero_struct = {NULL,0,0,'@'};
actor * hero = &hero_struct;

/* Update */

void update() {
  char c = getch();
  if (c=='q') {
    endwin(); exit(0);
  }
  actor_move(hero,c);
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
    map_draw(hero->place);
    actor_draw(hero);
  } else {
    space_warning();
  }
  refresh();
}

/* Colors */

void ensure_colors() {
  if (has_colors()==TRUE) {
    start_color();
    SCHEME('@', GREEN, BLACK);
    SCHEME('#', BLACK, YELLOW);
    SCHEME('~', WHITE, CYAN);
    SCHEME('|', YELLOW, BLACK);
    SCHEME('0', GREEN, GREEN);
    SCHEME(COLOR_WARN, RED, BLACK);
  }
}

/* Main */

int main(int argc, const char *argv[]) {
  initscr();
  noecho(); cbreak();
  curs_set(FALSE);
  ensure_colors();
  hero->place = &room_1;
  hero->y = 10;
  hero->x = 10;
  while(1) {
    draw();
    update();
  }
  endwin();
  return 0;
}

