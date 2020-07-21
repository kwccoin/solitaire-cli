CC=gcc

common:*.c
	$(CC) -g -Wall -c zCardGameUtility.c
	#$(CC) -g -DUNICODE -Wall -c zCard.c
	$(CC) -g -Wall -c zDisplay.c
	$(CC) -g -Wall -c zInput.c
	$(CC) -g -Wall -c zMain.c
	$(CC) -g -Wall -c zGame.c
	#$(CC) -g -o aS -Wall -lncurses zCardGameUtility.o zCard.o zDisplay.o zInput.o zGame.o zMain.o 

# default apple version - so far Mac ok with UNICODE
aS:*.c 
	$(CC) -g -Wall -c zCardGameUtility.c
	$(CC) -g -DUNICODE -Wall -c zCard.c
	$(CC) -g -Wall -c zDisplay.c
	$(CC) -g -Wall -c zInput.c
	$(CC) -g -Wall -c zMain.c
	$(CC) -g -Wall -c zGame.c
	$(CC) -g -o aS -Wall -lncurses zCardGameUtility.o zCard.o zDisplay.o zInput.o zGame.o zMain.o 

# linux verson (UNICODE) - ubuntu? Windows-ubuntu?
lS:*.c 

	$(CC) -g -Wall -c zCardGameUtility.c
	$(CC) -g -DUNICODE -Wall -c zCard.c
	$(CC) -g -Wall -c zDisplay.c
	$(CC) -g -Wall -c zInput.c
	$(CC) -g -Wall -c zMain.c
	$(CC) -g -Wall -c zGame.c
	$(CC) -g -o lS  -Wall  -lncursesw -ltinfo zCardGameUtility.o zCard.o zDisplay.o zInput.o zGame.o zMain.o -lncurses

# docker ascii version so far docker cannot handle UNICODE just ?
dS: 

	$(CC) -g -Wall -c zCardGameUtility.c
	$(CC) -g -Wall -c zCard.c
	$(CC) -g -Wall -c zDisplay.c
	$(CC) -g -Wall -c zInput.c
	$(CC) -g -Wall -c zMain.c
	$(CC) -g -Wall -c zGame.c
	$(CC) -g -o dS  -Wall  -lncursesw -ltinfo zCardGameUtility.o zCard.o zDisplay.o zInput.o zGame.o zMain.o -lncurses

# all debug

#mac:
#	$(CC) -g -o solitaire -DUNICODE -Wall main.c -lncurses
#debug:
#	$(CC) -g -o solitaire -DUNICODE -Wall main.c -lncursesw -ltinfo
#dascii:
#	$(CC) -g -o solitaire           -Wall main.c -lncursesw -ltinfo
#ascii:
#	$(CC)    -o solitaire           -Wall main.c -lncursesw -ltinfo

v:
	valgrind --log-file=log/vlogMMd1.txt -v -s --leak-check=full --show-leak-kinds=all ./dS

u:
	$(CC) -g -o uctest    -DUNICODE -Wall unicode_test.c -lncursesw -ltinfo

clean:
	rm -Rf aS* lS* dS* uctest *.o
