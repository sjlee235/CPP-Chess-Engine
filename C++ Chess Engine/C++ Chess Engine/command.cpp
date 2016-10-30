#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <array>
#include "board.h"
#include "movegen.h"
#include "timer.h"
#include "evaluation.h"
#include "pgn.h"

#include "debug.h"

void printMenu() {
     printf("--------------------------------------------------\n");
     printf("%d: Make move\n", MOVE);
     printf("%d: Display Board\n", DISPLAY_BOARD);
     printf("%d: Display FEN\n", DISPLAY_FEN);
     printf("%d: Reset Board\n", BOARD_RESET);
     printf("%d: Quit\n", QUIT);
     printf("%d: Undo move\n", UNDO_MOVE);
     printf("%d: Computer Make Move\n", COM_MAKE_MOVE);
     printf("A: Print Possible Moves\n");
     printf("C: Evaluate Board\n");
     printf("--------------------------------------------------\n");
     printf("Please choose command: ");
}