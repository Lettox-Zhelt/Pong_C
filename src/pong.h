#include <ncurses.h>
#include <stdio.h>

typedef struct ball_param {
  int x, y, state_x, state_y;
  char sym;
} Ball;

typedef struct field_param {
  int length, width;
  char sym;
} Field;

typedef struct rocket_param {
  int x, y, length;
  char sym;
} Rocket;

typedef struct players_count {
  int player_1, player_2;
} Count;

typedef struct game_params {
  Ball ball;
  Field field;
  Rocket left_rocket;
  Rocket right_rocket;
  Count count;
} Params;

void ncurses_setup();
void draw_game(Params*);
void draw_line(Params*);
