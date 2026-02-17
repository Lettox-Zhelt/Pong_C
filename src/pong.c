#include "pong.h"

int main() {
  Params params = {
      .ball = {40, 13, 1, 1},
      .field = {80, 25},
      .left_rocket = {75, 13},
      .right_rocket = {5, 13},
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
  int mover = 0;
  while (1) {
    if (mover == 50) mover = 0;
    // 1. Ввод (без задержки)
    char sym = getch();
    if (sym == 'q' || sym == 'a' || sym == 'z' || sym == 'k' || sym == 'm' ||
        sym == ' ') {
      switch (sym) {
        case 'q':
          endwin();
          return;
        case 'a':
          if (params->right_rocket.y > 2) params->right_rocket.y--;
          break;
        case 'z':
          if (params->right_rocket.y < params->field.width - 1)
            params->right_rocket.y++;
          break;
        case 'k':
          if (params->left_rocket.y > 2) params->left_rocket.y--;
          break;
        case 'm':
          if (params->left_rocket.y < params->field.width - 1)
            params->left_rocket.y++;
          break;
      }
    }

    // 2. Физика (столкновения и движение мяча)
    if ((params->ball.x == params->left_rocket.x - 1 &&
         (params->ball.y == params->left_rocket.y ||
          params->ball.y == params->left_rocket.y - 1 ||
          params->ball.y == params->left_rocket.y + 1)) ||
        (params->ball.x == params->right_rocket.x + 1 &&
         (params->ball.y == params->right_rocket.y ||
          params->ball.y == params->right_rocket.y - 1 ||
          params->ball.y == params->right_rocket.y + 1))) {
      params->ball.state_x *= -1;
    }
    if (params->ball.y == params->field.width || params->ball.y == 1) {
      params->ball.state_y *= -1;
    }
    if (mover % 5 == 0) {
      ball_x_mover(params);
      ball_y_mover(params);
    }

    // 3. Счёт и условия победы
    if (params->ball.x == 1) {
      params->count.player_2++;
      params->ball.x = 40;
      params->ball.y = 13;
    }
    if (params->ball.x == 80) {
      params->count.player_1++;
      params->ball.x = 40;
      params->ball.y = 13;
    }
    if (params->count.player_1 == 21 || params->count.player_2 == 21) {
      nodelay(stdscr, FALSE);
      clear();
      printw(params->count.player_1 == 21
                 ? "Congratulations, player 1!\nGame Over\n"
                 : "Congratulations, player 2!\nGame Over\n");
      refresh();
      getch();
      endwin();
      return;
    }

    // 4. Отрисовка кадра
    clear();
    printw("%20d%40d\n", params->count.player_1, params->count.player_2);
    y_line_maker(params);
    refresh();

    // 5. Задержка для управления FPS (20 мс ≈ 50 кадров/с)
    usleep(20000);
    mover++;
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
      "\nControls:\nLeft racket: \"A/Z\" | Right racket: \"K/M\" | Quit: "
      "\"Q\"\n");
  refresh();
}

// Function to move ball at x axis
void ball_x_mover(Params* params) {
  params->ball.x += 1 * params->ball.state_x;
}
// Function to move ball at y axis
void ball_y_mover(Params* params) {
  params->ball.y += 1 * params->ball.state_y;
}