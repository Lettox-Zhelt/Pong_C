#include "pong.h"

int main() {
  Params params = {
      .ball = {40, 13, 1, 1, '*'},
      .field = {80, 25, '#'},
      .left_rocket = {75, 13, '|'},
      .right_rocket = {5, 13, '|'},
      .count = {0, 0},
  };

  ncurses_setup();
  game_start(&params);
  // Game start
  endwin();
  return 0;
}

void ncurses_setup() {
  // Game start
  initscr();
  // Hide cursor
  curs_set(0);
  // No showing input key
  noecho();
  // Not to wait user input
  nodelay(stdscr, TRUE);
}

void game_start(Params* params) {
  while (1) {
    char sym;
    // Delay
    usleep(200000);
    // Crear screen & refresh it
    clear();
    // refresh();

    // Display players count
    printw("%20d%40d\n", params->count.player_1, params->count.player_2);
    // Drawing y line
    y_line_maker(params);
    // Getting user input
    sym = getch();
    // Validating user input
    if (sym == 'q' || sym == 'a' || sym == 'z' || sym == 'k' || sym == 'm' ||
        sym == ' ') {
      // Processing user input
      switch (sym) {
        case 'q':
          // Exit
          endwin();
          return;
          break;
        case ' ':
          break;
        case 'a':
          if (params->right_rocket.y >
              (params->field.width - (params->field.width - 2))) {
            params->right_rocket.y--;
          }
          break;
        case 'z':
          if (params->right_rocket.y < (params->field.width - 1)) {
            params->right_rocket.y++;
          }
          break;
        case 'k':
          if (params->left_rocket.y >
              (params->field.width - (params->field.width - 2))) {
            params->left_rocket.y--;
          }
          break;
        case 'm':
          if (params->left_rocket.y < (params->field.width - 1)) {
            params->left_rocket.y++;
          }
          break;
      }
    }
    // Processing ball collisions
    if ((params->ball.x == ((params->left_rocket.x - 1)) &&
         (params->ball.y == params->left_rocket.y ||
          params->ball.y == params->left_rocket.y - 1 ||
          params->ball.y == params->left_rocket.y + 1)) ||
        ((params->ball.x == (params->right_rocket.x + 1)) &&
         (params->ball.y == params->right_rocket.y ||
          params->ball.y == params->right_rocket.y - 1 ||
          params->ball.y == params->right_rocket.y + 1))) {
      params->ball.state_x = params->ball.state_x * (-1);
    }
    if (params->ball.y == (params->field.width) || (params->ball.y == 1)) {
      params->ball.state_y = params->ball.state_y * (-1);
    }

    // Moving ball
    ball_x_mover(params);
    ball_y_mover(params);

    // Processing players count
    if (params->ball.x == 1) {
      params->count.player_2++;
      params->ball.x = 40, params->ball.y = 13;
    }
    if (params->ball.x == 80) {
      params->count.player_1++;
      params->ball.x = 40, params->ball.y = 13;
    }
    if (params->count.player_2 == 21) {
      nodelay(stdscr, FALSE);
      clear();
      refresh();
      printw("Congratulations, player 2!\nGame Over\n");
      refresh();
      getch();
      endwin();
      return;
    }
    if (params->count.player_1 == 21) {
      nodelay(stdscr, FALSE);
      clear();
      refresh();
      printw("Congratulations, player 1!\nGame Over\n");
      refresh();
      getch();
      endwin();
      return;
    }
  }
}

// Functions definition
// This fuction creates x line
void x_line_maker(Params* params) {
  printw("|");
  for (int i = 1; i <= params->field.length; i++) {
    if (i == params->ball.x && params->ball.ball_presence == 1) {
      printw("@");
      continue;
    }
    if ((i == params->left_rocket.x &&
         params->left_rocket.rocket_presence == 1) ||
        (i == params->right_rocket.x &&
         params->right_rocket.rocket_presence == 1)) {
      printw("|");
      continue;
    } else {
      if (i == 40) {
        printw(".");
      } else {
        printw("%c", ' ');
      }
    }
  }
  printw("|");
}

// This function creates y line and invoke function to create x line
void y_line_maker(Params* params) {
  for (int i = 1; i <= params->field.width; i++) {
    if (i == params->ball.y) {
      params->ball.ball_presence = 1;
    } else {
      params->ball.ball_presence = 0;
    }
    if (i == params->left_rocket.y || i == params->left_rocket.y - 1 ||
        i == params->left_rocket.y + 1) {
      params->left_rocket.rocket_presence = 1;
    } else {
      params->left_rocket.rocket_presence = 0;
    }
    if (i == params->right_rocket.y || i == params->right_rocket.y - 1 ||
        i == params->right_rocket.y + 1) {
      params->right_rocket.rocket_presence = 1;
    } else {
      params->right_rocket.rocket_presence = 0;
    }

    x_line_maker(params);
    printw("\n");
  }
  printw(
      "\nControlls:\nLeft racket: \"A/Z\" | Right racket: \"K/M\" | Quit: "
      "\"Q\"\n");
}

// Function to move ball at x axis
void ball_x_mover(Params* params) {
  params->ball.x += 1 * params->ball.state_x;
}
// Function to move ball at y axis
void ball_y_mover(Params* params) {
  params->ball.y += 1 * params->ball.state_y;
}