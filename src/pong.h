#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

typedef struct ball_param {
  int x, y, state_x, state_y, ball_presence;
  char sym;
} Ball;

typedef struct field_param {
  int length, width;
  char sym;
} Field;

typedef struct rocket_param {
  int x, y, length, rocket_presence;
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
void game_start(Params*);
void draw_game(Params*);
void draw_line(Params*);
void y_line_maker(Params*);
void x_line_maker(Params*);
void ball_x_mover(Params*);
void ball_y_mover(Params*);