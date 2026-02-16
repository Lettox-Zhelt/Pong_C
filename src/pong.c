#include <pong.h>

int main() {
  Params params = {
      .ball = {40, 13, 1, 1, '*'},
      .field = {80, 25, '#'},
      .left_rocket = {5, 13, '|'},
      .right_rocket = {75, 13, '|'},
      .count = {0, 0},
  };

  ncurses_setup();

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

void game_start() {
  while (1) {
    char sym;
    // Delay
    for (int i = 0; i < 300000000; i++) {
    }
    // Crear screen & refresh it
    clear();
    refresh();

    // UNCOMMENT TO SHOW BALL POSION AND BALL STATE
    // printw("ball position: %d ", x_ball);
    // printw("%d    ", y_ball);
    // printw("state: %d ", stateX);
    // printw("%d\n", stateY);

    // Display players count
    printw("%20d%40d\n", count1, count2);
    // Drawing y line
    y_line_maker(x_field, y_field, x_ball, y_ball, x_racket1, y_racket1,
                 x_racket2, y_racket2);
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
          return 0;
          break;
        case ' ':
          break;
        case 'a':
          if (y_racket2 > (y_field - (y_field - 2))) {
            y_racket2--;
          }
          break;
        case 'z':
          if (y_racket2 < (y_field - 1)) {
            y_racket2++;
          }
          break;
        case 'k':
          if (y_racket1 > (y_field - (y_field - 2))) {
            y_racket1--;
          }
          break;
        case 'm':
          if (y_racket1 < (y_field - 1)) {
            y_racket1++;
          }
          break;
      }
    }
    // Processing ball collisions
    if ((x_ball == ((x_racket1 - 1)) &&
         (y_ball == y_racket1 || y_ball == y_racket1 - 1 ||
          y_ball == y_racket1 + 1)) ||
        ((x_ball == (x_racket2 + 1)) &&
         (y_ball == y_racket2 || y_ball == y_racket2 - 1 ||
          y_ball == y_racket2 + 1))) {
      stateX = stateX * (-1);
    }
    if (y_ball == (y_field) || (y_ball == 1)) {
      stateY = stateY * (-1);
    }

    // Moving ball
    x_ball = x_ball_mover(x_ball, stateX);
    y_ball = y_ball_mover(y_ball, stateY);

    // Processing players count
    if (x_ball == 1) {
      count2++;
      x_ball = 40, y_ball = 13;
    }
    if (x_ball == 80) {
      count1++;
      x_ball = 40, y_ball = 13;
    }
    if (count2 == 21) {
      nodelay(stdscr, FALSE);
      clear();
      refresh();
      printw("Congratulations, player 2!\nGame Over\n");
      refresh();
      getch();
      endwin();
      return 0;
    }
    if (count1 == 21) {
      nodelay(stdscr, FALSE);
      clear();
      refresh();
      printw("Congratulations, player 1!\nGame Over\n");
      refresh();
      getch();
      endwin();
      return 0;
    }
  }
}

// Functions definition
// This fuction creates x line
void x_line_maker(char ball_presence, char racket1_presence,
                  char racket2_presence, int x_field, int x_ball, int x_racket1,
                  int x_racket2) {
  printw("|");
  for (int i = 1; i <= x_field; i++) {
    if (i == x_ball && ball_presence == '1') {
      printw("@");
      continue;
    }
    if ((i == x_racket1 && racket1_presence == '1') ||
        (i == x_racket2 && racket2_presence == '1')) {
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
void y_line_maker(int x_field, int y_field, int x_ball, int y_ball,
                  int x_racket1, int y_racket1, int x_racket2, int y_racket2) {
  char ball_presence, racket1_presence, racket2_presence;

  for (int i = 1; i <= y_field; i++) {
    if (i == y_ball) {
      ball_presence = '1';
    } else {
      ball_presence = '0';
    }
    if (i == y_racket1 || i == y_racket1 - 1 || i == y_racket1 + 1) {
      racket1_presence = '1';
    } else {
      racket1_presence = '0';
    }
    if (i == y_racket2 || i == y_racket2 - 1 || i == y_racket2 + 1) {
      racket2_presence = '1';
    } else {
      racket2_presence = '0';
    }

    x_line_maker(ball_presence, racket1_presence, racket2_presence, x_field,
                 x_ball, x_racket1, x_racket2);
    printw("\n");
  }
  printw(
      "\nControlls:\nLeft racket: \"A/Z\" | Right racket: \"K/M\" | Quit: "
      "\"Q\"\n");
}

// Function to move ball at x axis
int x_ball_mover(int x_ball, int stateX) { return (x_ball + 1 * stateX); }
// Function to move ball at y axis
int y_ball_mover(int y_ball, int stateY) { return (y_ball + 1 * stateY); }