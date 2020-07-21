#include <memory.h> //size_t and NULL ??!! what
//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>

//#include <locale.h>
//#include <ncurses.h>
#include "zCardGameUtility.h"
#include "zCard.h"
#include "zGame.h"
#include "zInput.h"
#include "zDisplay.h"




game_state *make_game_state() {
  char pile_types[] = "dwffffccccccc";  // not sure what is this??

  game_state *state = mallocz(sizeof(game_state));
  state->piles = mallocz(sizeof(pile *) * PILE_COUNT);
  for (int pile_idx = 0; pile_idx < PILE_COUNT; pile_idx++) {
    state->piles[pile_idx] = make_pile();
    state->piles[pile_idx]->type = pile_types[pile_idx];
  }
  return state;
}

pile *stock(game_state *state) { return state->piles[PILE_DECK]; }

pile *waste(game_state *state) { return state->piles[PILE_WASTE]; }

pile *column(game_state *state, int index_one_based) {
  return state->piles[PILE_COLUMN1 + index_one_based - 1];
}

pile *foundation(game_state *state, int index_one_based) {
  return state->piles[PILE_FOUNDATION1 + index_one_based - 1];
}



void turn(game_state *state) {
  // moves 1 card from stock to waste
  card *revealed_card = shift(stock(state));
  reveal(revealed_card);
  push(state->piles[PILE_WASTE], revealed_card);
}

void deal(game_state *state) {
  // assuming a shuffled deck
  pile *deck = state->piles[PILE_DECK];
  // deal columns
  for (int i = 0; i < COLUMN_COUNT; i++) {
    int column_idx = i + 1;
    pile *column = state->piles[PILE_COLUMN1 + i];
    // deal N cards in Nth column
    for (int card_num = 0; card_num < column_idx; card_num++) {
      card *card = shift(deck);
      push(column, card);
      // reveal last card from the column
      if (card_num == column_idx - 1) {
        reveal(card);
      }
    }
  }
  // reveal 1 card
  turn(state);
}


void prepare_game(game_state *state) {
  pile *stock_pile = stock(state);
  fill_deck(stock_pile);
  shuffle_pile(stock_pile);
  deal(state);
  state->score = 0;
}

// --

void redeal(game_state *state) {
  while (!is_empty(waste(state))) {
    card *card = shift(waste(state));
    hide(card);
    push(stock(state), card);
  }
  add_score(state, -100);
}

int attempt_move(game_state *state, char *command) {
  // format: c6 f3
  parsed_input parsed = parse_input(command); // b parse_input:94 Breakpoint 2 at 0x559ec4308572: file zInput.c, line 13.
  if (parsed.success != 1) {
    return MOVE_INVALID_COMMAND;
  }

  
  /* kwc: checking why valgrind said there are uninitated :
  
    printf("parsed: %c %c %i %i %i %i $i\t\t", 
    parsed.source, 
    parsed.destination,
    parsed.source_index,
    parsed.destination_index,
    parsed.source_amount,
    parsed.success) ; */

    /* rsed: s  48 28 1 1 $i		
    parsed: r  48 28 1 1 $i		parsed: s  48 28 1 1 $i		
    parsed: w c 48 5 1 1 $i		parsed: w f 48 4 1 1 $i		
    parsed: c f 4 4 1 1 $i		parsed: w f 48 4 1 1 $i		
    parsed: c f 7 4 1 1 $i		parsed: c f 7 2 1 1 $i		
    parsed: c c 4 7 5 1 $i		parsed: c c 6 4 1 1 $i		
    parsed: c c 6 3 1 1 $i		parsed: c f 6 1 1 1 $i		
    parsed: c f 6 3 1 1 $i		parsed: c f 6 4 1 1 $i		
    parsed: c f 7 1 1 1 $i		parsed: s  48 28 1 1 $i		
    parsed: w f 48 2 1 1 $i		parsed: c f 7 2 1 1 $i		
    parsed: s  48 28 1 1 $i		parsed: w f 48 1 1 1 $i		
    parsed: r  48 28 1 1 $i		parsed: q  48 28 1 1 $i		
    high score is 210
    
    command like s has no destination and 
                 w has no source
                 r (mine) has no either

    But only the s has issues as one of the s command check destination
    
    */


/*#ifdef DEBUG_PRINT
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
//#endif */

  //catch source is help
  if(parsed.source == 'h' )
  {
    return MOVE_HELP;
  }

  if(parsed.source == 'r' )
  {
    return MOVE_REFRESH;
  }

  //catch source is quit - just display message for the moment
  if(parsed.source == 'q' )
  {
    return MOVE_QUIT;
  }

  // kwc: move some sources here seems to solve the problem of valgrind unitiated alert
  // source_index can also be broken

  if(parsed.source == 'c' 
  && ((parsed.source_index >= COLUMN_COUNT + 1) 
  || (parsed.source_index < 1))){
    return MOVE_INVALID_SOURCE;
  }

  // figure out destination
  if (parsed.source == 's') {
    for (int i = 0; i < parsed.source_amount; i++) { 
      if (is_empty(stock(state))) {
        // try to redeal
        if (is_empty(waste(state))) {
          return MOVE_CANNOT_REDEAL;
        }
        redeal(state);
      }
      turn(state);
    }
    return MOVE_OK;
  }
  //catch source / destination too high // kwc: these should last to avoid unitiated
  if(
      (parsed.destination == 'c' // kwc: unitiated value detected

      && ((parsed.destination_index >= COLUMN_COUNT + 1) 

          || (parsed.destination_index < 1)))
    || 
      (parsed.destination == 'f' // kwc: unitiated value detected

       && ((parsed.destination_index >= FOUNDATION_COUNT + 1) 

           ||  (parsed.destination_index < 1))))
  {
    return MOVE_INVALID_DESTINATION;
  }

  pile *source_pile = get_pile(state, parsed.source, parsed.source_index);
  pile *destination_pile =
      get_pile(state, parsed.destination, parsed.destination_index);

  // check if the move is valid
  if (is_empty(source_pile)) {
    return MOVE_SOURCE_EMPTY;
  }

  if (source_pile->num_cards < parsed.source_amount) {
    return MOVE_TOO_MANY_CARDS;
  }

  int first_card_index = source_pile->num_cards - parsed.source_amount;
  // multi-card move
  if (parsed.source_amount > 1) {
    // check if all cards have been revealed
    card *c = peek_card_at(source_pile, first_card_index);
    if (c->revealed == 0) {
      return MOVE_TOO_MANY_CARDS;
    }
  }

  for (int card_index = 0; card_index < parsed.source_amount; card_index++) {

    // card index doesn't move - the card is always at the same index
    card *source_card = peek_card_at(source_pile, first_card_index);

    // check if the move is valid based on the destination type
    if (parsed.destination == 'f') {
      // only ace goes if the destination is empty
      if (is_empty(destination_pile)) {
        if (source_card->rank == RANK_A) {
          move_card(state, source_card, source_pile, destination_pile);
        } else {
          return MOVE_INVALID_MOVE;
        }
      } else {
        // non-empty foundation, pick up the first card
        card *top_foundation_card = peek_last(destination_pile);
        if (can_be_placed_on_foundation(*top_foundation_card, *source_card)) {
          move_card(state, source_card, source_pile, destination_pile);
        } else {
          return MOVE_INVALID_MOVE;
        }
      }
    } else if (parsed.destination == 'c') {
      // king can go in an empty column
      if (is_empty(destination_pile)) {
        if (source_card->rank == RANK_K) {
          move_card(state, source_card, source_pile, destination_pile);
        } else {
          return MOVE_INVALID_MOVE;
        }
      } else {
        card *bottom_column_card = peek_last(destination_pile);
        if (can_be_placed_bottom(*bottom_column_card, *source_card)) {
          move_card(state, source_card, source_pile, destination_pile);
        } else {
          return MOVE_INVALID_MOVE;
        }
      }
    } else {
      return MOVE_INVALID_DESTINATION;
    }
  }

  // set the return code
  return MOVE_OK;
}

pile *get_pile(game_state *state, char pile_prefix, int pile_index_one_based) {
  switch (pile_prefix) {
  case 's':
    return stock(state);
  case 'w':
    return waste(state);
  case 'f':
    return foundation(state, pile_index_one_based);
  case 'c':
    return column(state, pile_index_one_based);
  default:
    return NULL;
  }
}

void add_score(game_state *state, int score) {
  state->score += score;
  if (state->score < 0) {
    state->score = 0;
  }
}

void move_card(game_state *state, card *card, pile *source_pile,
               pile *destination_pile) {
  delete (source_pile, card);
  if (reveal(peek_last(source_pile))) {
    add_score(state, 5); // turn over column card
  }
  push(destination_pile, card);

  // add score for the moves
  if (destination_pile->type == 'f') {
    add_score(state, 10);
  }
  if (source_pile->type == 'w' && destination_pile->type == 'c') {
    add_score(state, 5);
  }
}
