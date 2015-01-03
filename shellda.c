#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"
#include "actor.h"

#define RED_ON attron(COLOR_PAIR(1))
#define RED_OFF attroff(COLOR_PAIR(1))

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
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "#                                              #",
    "################################################"
  }
};

actor hero_struct = {NULL,0,0,'@',2};
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

