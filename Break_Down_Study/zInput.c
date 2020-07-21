#include <memory.h>  // surprise need this for strcmp as well!!
//#include <stddef.h>
#include <stdio.h>   // sscanf
#include <stdlib.h>  // strcmp
//#include <time.h>

//#include <locale.h>
//#include <ncurses.h>
//#include "zCard.h"
//#include "zGame.h"
#include "zInput.h"

parsed_input parse_input(char *command) {
  parsed_input parsed;
  parsed.success = 1;
  parsed.source_amount = 1;
  // parser patterns
  char *pattern_multi_move = "%dc%d c%d";  //kwc: #c#c#
  char *pattern_single_move = "c%d %c%d";  //kwc: c#c#
  char *pattern_single_move2 = "%d %d";    //kwc: ##
  char *pattern_waste_move = "w %c%d";     //kwc: wf# or wc#
  char *pattern_multi_stock = "%ds";       //kwc: #s
  char *pattern_stock = "s";               //kwc: s
  char *pattern_help = "h";                //kwc: h
  char *pattern_quit = "quit";             //kwc: quit
  char *pattern_refresh = "r";             //kwc: refresh
  if (sscanf(command, pattern_multi_move, &parsed.source_amount,
             &parsed.source_index, &parsed.destination_index) == 3) {
    parsed.source = 'c';
    parsed.destination = 'c';
  } else if (sscanf(command, pattern_single_move, &parsed.source_index,
                    &parsed.destination, &parsed.destination_index) == 3) {
    parsed.source = 'c';
  } else if (sscanf(command, pattern_waste_move, &parsed.destination,
                    &parsed.destination_index) == 2) {
    parsed.source = 'w';
  } else if (sscanf(command, pattern_single_move2, &parsed.source_index,
                    &parsed.destination_index) == 2) {
    parsed.source = 'c';
    parsed.destination = 'c';
  } else if (sscanf(command, pattern_multi_stock, &parsed.source_amount) == 1) {
    parsed.source = 's';
  } else if (strcmp(command, pattern_stock) == 0) {
    parsed.source = 's';
  } else if (strcmp(command, pattern_help) == 0) {
    parsed.source = 'h';  
  } else if (strcmp(command, pattern_refresh) == 0) {
    parsed.source = 'r';
  } else if (strcmp(command, pattern_quit) == 0) {
    parsed.source = 'q';
  } else {
    parsed.success = 0;
  }
  return parsed;
}






