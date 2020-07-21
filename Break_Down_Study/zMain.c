//#include <memory.h>
//#include <stddef.h>
//#include <stdio.h>
#include <stdlib.h> //srand and exit
#include <time.h>

#include <locale.h>
#include <ncurses.h>
#include "zCard.h"
#include "zGame.h"    // depend upon Card
#include "zDisplay.h" // depend upon Card & Game
//#include "zCardGameUtility.h"
//#include "zInput.h"



int main() {

  FILE *fptr;

  fptr = fopen("highScore.txt","r");

  if(fptr == NULL){
    HIGH_SCORE =0;
  } else {
    fscanf(fptr, "%i",&HIGH_SCORE);
    fclose(fptr); // kwc?1: need to close only if NOT NULL
  }

  char *move_results[] = {"OK",
                        "Invalid command",
                        "Source pile empty",
                        "Invalid move",
                        "Too many cards to move!",
                        "Cannot redeal, stock pile empty",
                        "Invalid destination",
                         "Invalid source",
                         "h, s, #s, wc#, wf#, ##, c#c#, c#f#, #c#c#, r, quit",
                         "refresh",
                         "quit"};


  srand(time(NULL));
  //  srand(3);
  setlocale(LC_ALL, "");
  init_curses();

  // prepare the game state
  game_state *state = make_game_state();
  prepare_game(state);

  char buffer[80];
  print_all_curses(state);

  // game loop
  while (1) {
    getstr(buffer);
    erase();
    // pick up the source, destination and attempt the move
    int result = attempt_move(state, buffer); // (gdb) b attempt_move:60 Breakpoint 1 at 0x2b03: file zGame.c, line 92.
    mvprintw(rows - 2, 0, "Move status: %s", move_results[result]);
    // show new status in the status bar
    if (result == MOVE_REFRESH){
      erase();
      refresh();
      print_all_curses(state);
    } else if (result == MOVE_QUIT) {
      // add these seems cannot save the command line
      // print_all_curses(state);
      //end_curses();
      //initscr(); // visual mode, no need if not
      //erase() 
      refresh();
      getch();
      endwin();
      printf("high score is %d\n", state->score);       // may save and launch with the overall high score ???
      fptr = fopen("highScore.txt","w");
      if(fptr == NULL){
        printf("Error write HIGH_SCORE");
        exit(1);
      } else {
        if (state->score < HIGH_SCORE){
          state->score = HIGH_SCORE;
        }
        fprintf(fptr, "%i",state->score);
      }
      fclose(fptr);
      exit(0); 
    } else {
      print_all_curses(state);
    }
  }
  getch();      // not sure about these 2 lines
  end_curses(); // add this but still not ok; the command line broken
}
