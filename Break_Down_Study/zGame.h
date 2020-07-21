#ifndef zGAME
#define zGAME


typedef struct game_state {
  pile **piles;
  int pile_count;
  int score;
} game_state;


int  HIGH_SCORE ;

enum {
  MOVE_OK,
  MOVE_INVALID_COMMAND,
  MOVE_SOURCE_EMPTY,
  MOVE_INVALID_MOVE,
  MOVE_TOO_MANY_CARDS,
  MOVE_CANNOT_REDEAL,
  MOVE_INVALID_DESTINATION,
  MOVE_INVALID_SOURCE,
  MOVE_HELP,
  MOVE_REFRESH,
  MOVE_QUIT
};


void add_score(game_state *state, int score) ;

game_state *make_game_state() ;

pile *stock(game_state *state) ;

pile *waste(game_state *state) ;

pile *column(game_state *state, int index_one_based) ;

pile *foundation(game_state *state, int index_one_based) ;


void turn(game_state *state) ;

void deal(game_state *state) ;


void prepare_game(game_state *state) ;

int attempt_move(game_state *state, char *command) ;

void redeal(game_state *state);

pile *get_pile(game_state *state, char pile_prefix, 
                int pile_index_one_based);

void move_card(game_state *state, card *card, pile *source_pile,
               pile *destination_pile);


#endif