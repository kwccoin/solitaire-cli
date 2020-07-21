//#include <memory.h>
#include <stddef.h> // 'size_t' and NULL
//#include <stdio.h>
#include <stdlib.h> // free and rand
//#include <time.h>

//#include <locale.h>
//#include <ncurses.h>
#include "zCard.h"
#include "zCardGameUtility.h"



#ifdef UNICODE
const char *suit_to_charptr(int suit) {
  switch (suit) {
  case SUIT_HEART:
    return "\u2665"; // 2665  BLACK HEART SUIT
  case SUIT_SPADE:
    return "\u2660"; // 2660  BLACK SPADE SUIT
  case SUIT_CLUB:
    return "\u2663"; // 2663  BLACK CLUB SUIT
  case SUIT_DIAMOND:
    return "\u2666"; // 2666  BLACK DIAMOND SUIT
  default:
    return "?";
  }
}

#else
const char *suit_to_charptr(int suit) {
  switch (suit) {
  case SUIT_HEART:
    return "~H";
  case SUIT_SPADE:
    return "~S";
  case SUIT_CLUB:
    return "-c";
  case SUIT_DIAMOND:
    return "-d";
  default:
    return "?";
  }
}
#endif


const char *rank_to_charptr(int rank) {
  switch (rank) {
  case RANK_A:
    return "A";
  case RANK_2:
    return "2";
  case RANK_3:
    return "3";
  case RANK_4:
    return "4";
  case RANK_5:
    return "5";
  case RANK_6:
    return "6";
  case RANK_7:
    return "7";
  case RANK_8:
    return "8";
  case RANK_9:
    return "9";
  case RANK_10:
    return "10";
  case RANK_J:
    return "J";
  case RANK_Q:
    return "Q";
  case RANK_K:
    return "K";
  default:
    return "?";
  }
}


card make_card(int suit, int rank) {
  card c;
  c.suit = suit;
  c.rank = rank;
  return c;
}

card *make_card_ptr(int suit, int rank) {
  card *c = mallocz(sizeof(card));
  c->suit = suit;
  c->rank = rank;
  return c;
}

int is_black(card c) { return c.suit == SUIT_CLUB || c.suit == SUIT_SPADE; }

int is_red(card c) { return c.suit == SUIT_HEART || c.suit == SUIT_DIAMOND; }

int is_ace(card c) { return c.rank == RANK_A; }

int is_alternate_color(card first, card second) {
  return is_black(first) != is_black(second);
}

int is_in_sequence(card lower, card higher) {
  return higher.rank == lower.rank + 1;
}

int can_be_placed_bottom(card parent, card child) {
  return is_alternate_color(parent, child) && is_in_sequence(child, parent);
}

int is_same_suit(card first, card second) { return first.suit == second.suit; }

int can_be_placed_on_foundation(card parent, card child) {
  return is_same_suit(parent, child) && is_in_sequence(parent, child);
}


card_node *find_tail(pile *pile) {
  card_node *tail = pile->head;
  if (tail == 0)
    return 0;
  while (tail->next != 0) {
    tail = tail->next;
  }
  return tail;
}

card_node *make_node(card *card) {
  card_node *node = mallocz(sizeof(card_node));
  node->value = card;
  node->next = 0;
  return node;
}

int is_empty(pile *pile) { return pile->num_cards == 0; }

// remove a card from a pile, relinking the list
void delete (pile *pile, card *card) {
  if (is_empty(pile)) {
    return;
  }
  // no previous node for the first item
  card_node *prev = NULL;
  card_node *current;
  for (current = pile->head; current != NULL;
       prev = current, current = current->next) {
    if (current->value == card) {
      // special case if the first item was found
      if (prev == NULL) {
        pile->head = current->next;
      } else {
        // skip the current item in the list
        prev->next = current->next;
      }
      pile->num_cards--;
      free(current);
      return;
    }
  }
}

// append to the end of the list
void push(pile *pile, card *card) {
  card_node *tail = find_tail(pile);
  if (tail == NULL) {
    pile->head = make_node(card);
  } else {
    tail->next = make_node(card);
  }
  pile->num_cards++;
}

// remove a card from the end of the list
card *pop(pile *pile) {
  pile->num_cards--;
  // find the (n-1)th card
  card_node *pre_tail = pile->head;
  for (int i = 0; i < pile->num_cards - 1; i++)
    pre_tail = pre_tail->next;
  card_node *tail = pre_tail->next;
  card *card = tail->value;
  pre_tail->next = 0;
  free(tail);
  return card;
}

// append to the beginning of the list
void unshift(pile *pile, card *card) {
  card_node *new_head = make_node(card);
  new_head->next = pile->head;
  pile->head = new_head;
  pile->num_cards++;
}

// remove a card from the beginning of the list
card *shift(pile *pile) {
  pile->num_cards--;
  card_node *old_head = pile->head;
  pile->head = old_head->next;

  card *card = old_head->value;
  free(old_head);
  return card;
}

card *peek_card_at(pile *pile, int index) {
  card_node *head = pile->head;
  for (int i = 0; i < index; i++)
    head = head->next;
  return head->value;
}

card *peek(pile *pile) {
  if (pile->head == NULL) {
    return NULL;
  }
  return pile->head->value;
}

card *peek_last(pile *pile) {
  if (pile->head == NULL) {
    return NULL;
  }
  return peek_card_at(pile, pile->num_cards - 1);
}

pile *make_pile() {
  pile *pile_ptr = mallocz(sizeof(pile));
  pile_ptr->num_cards = 0;
  return pile_ptr;
}

void fill_deck(pile *pile) {
  for (int rank = 0; rank < RANK_COUNT; rank++) {
    for (int suit = 0; suit < SUIT_COUNT; suit++) {
      push(pile, make_card_ptr(suit, rank));
    }
  }
}

void insert(pile *pile, card *card, int idx) {
  card_node *pre_tail = pile->head;
  for (int i = 0; i < idx; i++)
    pre_tail = pre_tail->next;
  card_node *card_node = make_node(card);
  card_node->next = pre_tail->next;
  pre_tail->next = card_node;
  pile->num_cards++;
}

void shuffle_pile(pile *pile) {
  int shuffle_times = pile->num_cards * 10;
  for (int i = 0; i < shuffle_times; i++) {
    // unshift a card and insert to random place
    int idx = rand() % pile->num_cards - 1;
    card *card = shift(pile);
    insert(pile, card, idx);
  }
}

// returns 1 if a card was revealed
int reveal(card *card) {
  if (card == NULL)
    return 0;
  card->revealed = 1;
  return 1;
}

void hide(card *card) {
  if (card == NULL)
    return;
  card->revealed = 0;
}