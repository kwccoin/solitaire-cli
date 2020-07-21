#ifndef zDISPLAY
#define zDISPLAY

#define COLUMN_COUNT 7
#define FOUNDATION_COUNT 4

enum {
  PILE_DECK,
  PILE_WASTE,
  PILE_FOUNDATION1,
  PILE_FOUNDATION2,
  PILE_FOUNDATION3,
  PILE_FOUNDATION4,
  PILE_COLUMN1,
  PILE_COLUMN2,
  PILE_COLUMN3,
  PILE_COLUMN4,
  PILE_COLUMN5,
  PILE_COLUMN6,
  PILE_COLUMN7,
  PILE_COUNT
};

#define BLACK_PAIR 1
#define RED_PAIR 2
#define DEFAULT_COLOR -1


void print_deck(pile *pile) ;

void print_card(card *c) ;

void print_card_ptr(card *c) ;

int rows, cols;


void init_curses() ;

void printw_card(card *c) ;

void printw_pile_size(pile *pile) ;

void end_curses() ;

void print_prompt(game_state *state) ;

void debug_print_pile(pile *pile, int row, int column) ;

void print_all_curses(game_state *state) ;


#endif

// depend upon Card & Game