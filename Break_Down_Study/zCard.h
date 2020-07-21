#ifndef zCARD
#define zCARD

#define CARD_COUNT 52



typedef struct card {
  int suit;
  int rank;
  int revealed;
} card;


typedef struct card_node {
  card *value;
  struct card_node *next;
} card_node;

typedef struct pile {
  card_node *head;
  int num_cards;
  char type;
} pile;

enum {
  SUIT_HEART,
  SUIT_SPADE,
  SUIT_CLUB,
  SUIT_DIAMOND,
  SUIT_COUNT // ♥♠♣♦
};

enum {
  RANK_A,
  RANK_2,
  RANK_3,
  RANK_4,
  RANK_5,
  RANK_6,
  RANK_7,
  RANK_8,
  RANK_9,
  RANK_10,
  RANK_J,
  RANK_Q,
  RANK_K,
  RANK_COUNT
};


const char *suit_to_charptr(int suit);


const char *rank_to_charptr(int rank);


card make_card(int suit, int rank) ;

card *make_card_ptr(int suit, int rank) ;

int is_black(card c) ;

int is_red(card c) ;

int is_ace(card c) ;

int is_alternate_color(card first, card second) ;

int is_in_sequence(card lower, card higher) ;

int can_be_placed_bottom(card parent, card child) ;

int is_same_suit(card first, card second) ;

int can_be_placed_on_foundation(card parent, card child) ;


//#endif

//  =======================================

//#ifndef PILE_LIST
//#define PILE_LIST




card_node *find_tail(pile *pile) ;

card_node *make_node(card *card) ;

int is_empty(pile *pile) ;

// remove a card from a pile, relinking the list
void delete (pile *pile, card *card) ;

// append to the end of the list
void push(pile *pile, card *card) ;

// remove a card from the end of the list
card *pop(pile *pile) ;

// append to the beginning of the list
void unshift(pile *pile, card *card) ;

// remove a card from the beginning of the list
card *shift(pile *pile) ;

card *peek_card_at(pile *pile, int index) ;

card *peek(pile *pile) ;
card *peek_last(pile *pile) ;

pile *make_pile() ;

void fill_deck(pile *pile) ;

// ---

void insert(pile *pile, card *card, int idx) ;

void shuffle_pile(pile *pile) ;

// returns 1 if a card was revealed
int reveal(card *card) ;

void hide(card *card) ;


#endif
