//#include <memory.h>
//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>

//#include <locale.h>
#include <ncurses.h>
#include "zCard.h"
#include "zGame.h"
#include "zDisplay.h"
//#include "zInput.h"
// #include "zUtility.h"

void print_card(card *c) {
  printf("%s%s", rank_to_charptr(c->rank), suit_to_charptr(c->suit));
}

void print_card_ptr(card *c) { printf("%p", c); }

/* kwc: not sure why it is here
#define PRINTCARD(x)                                                           \
  print_card(x);                                                               \
  printf(" ");                                                                 \
  print_card_ptr(x);                                                           \
  printf("\n");
*/

void print_deck(pile *pile) {
  printf("[");
  card_node *head = pile->head;
  for (int i = 0; i < pile->num_cards; i++) {
    card *c = head->value;
    print_card(c);
    printf(" ");
    head = head->next;
  }
  printf("] (%d)\n", pile->num_cards);
}


void init_curses() {
  initscr();
  keypad(stdscr, TRUE);
  use_default_colors();
  start_color();
  getmaxyx(stdscr, rows, cols);
  init_pair(BLACK_PAIR, DEFAULT_COLOR, DEFAULT_COLOR);
  init_pair(RED_PAIR, COLOR_RED, DEFAULT_COLOR);
}

void printw_card(card *c) {
  if (c == NULL) {
    printw("[     ]");
    return;
  }
  if (c->revealed) {
    int color_pair = is_black(*c) ? BLACK_PAIR : RED_PAIR;
    attron(COLOR_PAIR(color_pair));
    printw("%s%s", rank_to_charptr(c->rank), suit_to_charptr(c->suit));
    attroff(COLOR_PAIR(color_pair));
  } else {
#ifdef DEBUG_PRINT
    printw("(%s%s)", rank_to_charptr(c->rank), suit_to_charptr(c->suit));
#else
    printw("[ ]");
#endif
  }
}

void printw_pile_size(pile *pile) { printw("(%d cards)", pile->num_cards); }

void end_curses() { endwin(); }

char *first_row_headers[] = {"Stock",        "Waste",        "",
                             "Foundation 1", "Foundation 2", "Foundation 3",
                             "Foundation 4"};
char *second_row_headers[] = {"Column 1", "Column 2", "Column 3", "Column 4",
                              "Column 5", "Column 6", "Column 7"};

void print_prompt(game_state *state) {
  move(rows - 3, 0);
  printw("Current Score: %d (Last High Score is %i)", state->score, HIGH_SCORE);
  move(rows - 1, 0);
  printw("solitaire-cli (h for help)> ");
}

void debug_print_pile(pile *pile, int row, int column) {
  for (int i = 0; i < pile->num_cards; i++) {
    move(row + i, column);
    printw_card(peek_card_at(pile, i));
  }
}

void print_all_curses(game_state *state) {
  // 2 rows, 7 columns
  // top row has a fixed height of 1 card
  // bottom row can have up to 13 cards
  move(0, 0);
  // first row header
  // let's assume 100 characters terminal
  int column_size = 14;
  for (int i = 0; i < 7; i++) {
    move(0, column_size * i);
    printw("%s", first_row_headers[i]);
  }
  pile *stock_pile = stock(state);
  pile *waste_pile = waste(state);
  // first row content
  move(1, 0);
  printw_card(peek(stock_pile));
  move(2, 0);
  printw_pile_size(stock_pile);
  move(1, column_size);
  printw_card(peek_last(waste_pile));
  move(2, column_size);
  printw_pile_size(waste_pile);

  // foundations
  for (int f = 0; f < FOUNDATION_COUNT; f++) {
    int foundation_1_column = 3;
    move(1, (foundation_1_column + f) * column_size);
    printw_card(peek_last(foundation(state, f + 1)));
    move(2, (foundation_1_column + f) * column_size);
    printw_pile_size(foundation(state, f + 1));
  }

  // second row header
  for (int i = 0; i < COLUMN_COUNT; i++) {
    move(4, column_size * i);
    printw("%s", second_row_headers[i]);
    move(5, column_size * i);
    printw_pile_size(column(state, i + 1));
  }

  for (int i = 0; i < COLUMN_COUNT; i++) {
    pile *col = column(state, i + 1);
    int base_row = 6;
    for (int c = 0; c < col->num_cards; c++) {
      move(base_row + c, column_size * i);
      printw_card(peek_card_at(col, c));
    }
  }

#ifdef DEBUG_PRINT
  // debug: stock, waste
  mvprintw(17, 0, "stock:");
  debug_print_pile(stock_pile, 18, 0);
  mvprintw(17, 16, "waste:");
  debug_print_pile(waste_pile, 18, 16);
  mvprintw(17, 32, "foundation 1:");
  debug_print_pile(foundation(state, 1), 18, 32);
  mvprintw(17, 48, "foundation 2:");
  debug_print_pile(foundation(state, 2), 18, 48);
  mvprintw(17, 64, "foundation 3:");
  debug_print_pile(foundation(state, 3), 18, 64);
  mvprintw(17, 80, "foundation 4:");
  debug_print_pile(foundation(state, 4), 18, 80);
#endif

  // status bar for the commands
  print_prompt(state);
}
