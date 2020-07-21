
## File convention on making latter

Pull Request 1

* Remark

Your bug fix need +1 to fix the error about range of destination and source.

The issue is that some commands also check the source/destination index e.g. 798-813 (my adjusted source).  They should be the last as u has no src/dest, w has no src, c may use f etc.  Hence a change would avoid valgrind alert use of uninitiated variables.  Minor as it does no cause bug as the comparison is alway false, just showed up in report of valgrind.

* Further, I add some commands

- r: for refresh as some debugging in valgrind of print out better to have refresh command
- q: with high score
- h: for help message (and a hint at least h)

Further action:

A. Doc

A1. Sample document or readme to figure out c1c3 ... etc.

B. Input

B1. May try to avoid c/f by using abcd for f so 
- 12 is c1c2 
- [2-c]12 is 2to12c1c2
- 1a is c1f1 
- wa is wf1
- w1 is wc1
- s, h, r, no change
B2. above but with no return needed
B3. (See Pull Request 2 for Geek version, just use the home key + w (and other usual commands, may add a change keyboard opt.)

C. Source

C1. The source is great as it is one page
C2. But I have tried in this branch to try to reorganise it so that it is card/input/ncurses-output to make the source ... not sure

D. May try to do the Clojure one like the video about using, surprisingly not Clojure, JS to do 3 ways to do programming i.e. try
 
D1. command mode see C above; 
D2. object mode not sure (use objective C); and 
D3. function mode by passing state

Mostly D3 as that is the Real Game I want to try

E. GUI

E1. python version
E2. iOS version
E3. JS version
E4. Not sure I will do Clojure, but may try Lisp

BTW, never pay solitaire (perhaps once in Windows 95 after installation using floppy), I am not sure as I play bridge in Turbo Bridge in 1987 I think.  One of the objective here is to learn enough of ncurses to reimplement that and all a Cantonese game called Sky 9.  In any case your game is quit addictive, partially because one page C with a fast text game without using mouse.  

F. Finally

Great work as said.  Hope I am not too annoying.

---

Pull Request 1b

Fix a bug as the file closure need a file!

G. Geek Version

I wonder 

? Why Unicode not work under docker

And work on 2 better imprvoment

G1. use   asdf gh jkl;'
         1234 56 7shcd
G2. this is keyboard based (ncureses is as well)
G3. and fixed foundation to spade-heart-clubs-diamond to ease memory and in case of ASCII
G4. I also want to add a command call auto for end game i.e. random check any one card or check all cards are revealed that mean it should be solvable (?) i.e. if can move to foundation move it and continues move it until it cannot  (i.e. save the end game time wastage of my life to get score)

H. High Score for programming

H1. once we have the highScore.txt on the github
H2. may need myHigh vs Github high
H3. Need a history to avoid cheating ... :-)

----

To have 3 version for Mac, linux (Ubuntu 20 under Windows and real one, well a powerline only Lenovo come down from wife) and a docker version; I am not sure whether there would be need for my Arm Development Mac and real windows :-)

That need different Makefile and whilst it is faster to use those @ < ... I always not sure what they are doing and need to think :-)

aS for Apple
lS for linux
dS for docker

Could run under docker using gdb and valgrind; but not Apple (run but ...) linux need power up the old thing ...

Better do useful stuff and stop for awhile.  But playing the game I would.  

==== P.S.

Just stop to have more idea ... like multi user ... AI study etc. and touching for awhile.  A new branch is developed as a base for my future self to work with.  Need to do more serious work for my lovely fallen place.  In the mean time, I guess I understand why again those hacker in the 70s doing text game (and also one on cathode tube) using the Internet then.  It is all addictive.  Have to stop :-)