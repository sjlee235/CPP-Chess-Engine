#pragma once
#include "defs.h"
#include <Windows.h>

class Board {
private:
     std::array<int, 120> board;
     std::array<bool, 4> castlingCheck;
     color turn;
     int enpassantSquare;
     int fiftyMoveCount;
     int moveNumber;

public:
     
     // Default Constructor
     Board() {}
     /*
     Board() {
          for (int i = 0; i < 120; i++) {
               board[i] = ERRORSQUARE;
          }
          for (int i = 2; i < 10; i++) {
               for (int j = 1; j < 9; j++) {
                    board[i * 8 + j] = EMPTYSQUARE;
               }
          }

          turn = WHITE;
          enpassantSquare = 0;
          fiftyMoveCount = 0;
          moveNumber = 1;
     }
     */

     // Constructor adding all content at once
     Board(std::array<int, 120> b, std::array<bool, 4> cc, color t, int e, int f, int m) {
          board = b;
          castlingCheck = cc;
          turn = t;
          enpassantSquare = e;
          fiftyMoveCount = f;
          moveNumber = m;
     }
     
     //  Clone Method
     Board(const Board& originalBoard) {
          board = originalBoard.getBoard();
          castlingCheck = originalBoard.getCastlingArray();
          turn = originalBoard.getTurn();
          enpassantSquare = originalBoard.getEnpassantSquare();
          fiftyMoveCount = originalBoard.getFiftyMoveCount();
          moveNumber = originalBoard.getMoveNumber();
     }

     //  isEqual Method
     bool isEqual(const Board& thatBoard) {
          if (this == &thatBoard) {
               return true;
          }
          if (board == thatBoard.board &&
               castlingCheck == thatBoard.castlingCheck &&
               turn == thatBoard.turn &&
               enpassantSquare == thatBoard.enpassantSquare &&
               fiftyMoveCount == thatBoard.fiftyMoveCount &&
               moveNumber && thatBoard.moveNumber) {
               return true;
          }
          else {
               return false;
          }
     }

     //  isAlmostEqual Method (for threefold repetition checking)
     bool isAlmostEqual(const Board& thatBoard) {
          if (this == &thatBoard) {
               return true;
          }
          if (board == thatBoard.board &&
               castlingCheck == thatBoard.castlingCheck &&
               enpassantSquare == thatBoard.enpassantSquare) {
               return true;
          }
          else {
               return false;
          }
     }

     //  Mutators
     void setBoard(const std::array<int, 120> b) { board = b; }
     void setSquare(const int square, const int value) { board.at(square) = value; }
     void setCastlingArray(const std::array<bool, 4> cc) { castlingCheck = cc; }
     void setCastling(const int index, const bool value) { castlingCheck.at(index) = value; }
     void setTurn(const color t) { turn = t; }
     void setEnpassantSquare(const int e) { enpassantSquare = e; }
     void setFiftyMoveCount(const int f) { fiftyMoveCount = f; }
     void setMoveNumber(const int m) { moveNumber = m; }

     //  Accessors
     const std::array<int, 120> getBoard() const { return board; }
     const int getSquare(int square) const { return board.at(square); }
     const std::array<bool, 4> getCastlingArray() const { return castlingCheck; }
     const bool getCastling(int index) const { return castlingCheck.at(index); }
     const color getTurn() const { return turn; }
     const int getEnpassantSquare() const { return enpassantSquare; }
     const int getFiftyMoveCount() const { return fiftyMoveCount; }
     const int getMoveNumber() const { return moveNumber; }

     //  Other Functions
     void changeTurn() { turn = (color)-turn; }
     void fiftyMoveCountDecrement() { fiftyMoveCount--; }
     void fiftyMoveCountIncrement() { fiftyMoveCount++; }
     void moveNumberDecrement() { moveNumber--; }
     void moveNumberIncrement() { moveNumber++; }
};
class Move {
private:
     int initialSquare;
     int terminalSquare;
     int moveType;
public:
     // Constructors
     Move() {}
     Move(int i, int t, int m) {
          initialSquare = i;
          terminalSquare = t;
          moveType = m;
     }

     // Clone Methods
     Move(const Move& originalMove) {
          initialSquare = originalMove.getInitial();
          terminalSquare = originalMove.getTerminal();
          moveType = originalMove.getType();
     }
     Move(int originalMove[3]) {
          initialSquare = originalMove[0];
          terminalSquare = originalMove[1];
          moveType = originalMove[2];
     }

     // Mutators
     void setInitial(const int i) { initialSquare = i; }
     void setTerminal(const int t) { terminalSquare = t; }
     void setType(const int t) { moveType = t; }
     // Accessors
     const int getInitial() const { return initialSquare; }
     const int getTerminal() const { return terminalSquare; }
     const int getType() const { return moveType; }

};
class MoveList {
private:
     std::array<Move, MAX_MOVEGEN_COUNT> movelist;
     int moveCounter;
public:
     // Construcctor
     MoveList() {
          moveCounter = 0;
     }

     // Accessor
     inline std::array<Move, MAX_MOVEGEN_COUNT> getList() { return movelist; }
     inline Move getMove(int index) { return movelist[index]; }
     inline int getCounter() { return moveCounter; }

     void addMove(Move& move) {
          movelist[moveCounter] = move;
          moveCounter++;
     }
};

/*                                  BOARD SETUP                               */
/// <summary>
/// This function sets the given board to the initial state.
/// </summary>
/// <param name="board">The board that will be changed to initial state.</param>
void board120Setup(Board& board);
/// <summary>
/// This function sets the given board according to the FEN.
/// </summary>
/// <param name="board">The board that will be changed to initial state.</param>
/// <param name="FEN">The desired board in FEN notation.</param>
void FENboardSetup(Board& board, const std::string FEN);
/// <summary>
/// This function converts the given board to FEN notation.
/// </summary>
/// <param name="board">The board that will be converted to FEN notation.</param>
/// <returns>FEN notation of the given board.</returns>
std::string boardToFEN(const Board& board);
/// <summary>
/// This function prints the given board to console.
/// </summary>
/// <param name="board">The board that will be printed to console.</param>
void printBoard(const Board& board);
/// <summary>
/// This function prints the given board to console excluding the error squares.
/// </summary>
/// <param name="board">The board that will be printed to console.</param>
void printSimpleBoard(const Board& board);

/// <summary>
/// This function returns the color of the given piece type
/// </summary>
/// <param name="pieceType">The piece that will be checked its color</param>
/// <returns>The color of the given piece</returns>
int checkColor(int pieceType);
/// <summary>
/// This function returns the column character (file) of a given square.
/// </summary>
/// <param name="position">The square that the function will give its file</param>
/// <returns>The file of the given square</returns>
char numberToFile(int position);
/// <summary>
/// This function returns the row number (rank) of a given square.
/// </summary>
/// <param name="position">The square that the function will give its rank</param>
/// <returns>The rank of the given square</returns>
int numberToRank(int position);
/// <summary>
/// This function converts the file and rank notation to array index of a board. 
/// </summary>
/// <param name="file">The file of the square</param>
/// <param name="rank">The rank of the square</param>
/// <returns>The array index notation of the square</returns>
int filerankToNumber(char file, int rank);
/// <summary>
/// This function converts a position's notation from array index to file rank.
/// </summary>
/// <param name="position">The square in array index notation.</param>
/// <returns>A two-letter string with file rank notation of the given square.</returns>
std::string numberToFilerank(int position);
/// <summary>
/// This function prints the given move to console in filerank-filerank notation.
/// </summary>
/// <param name="move">The move that will be printed to console</param>
void printMove(const Move& move);



/*                                BOARD EVALUATION                            */
//  Returns evaluation score based on parameter board given.
int boardEvaluation(const Board& board);
//  Gets a position number and returns the row-reversed position number
int reversePosition(int position);
//  negaMax implemented for board evaluation
int negaMax(int depth, Board& board);
//  function to call negaMax. bestMoves is the output
int rootNegaMax(int depth, Board& board, Move& bestMove);
//  negaMax with alphaBeta pruning implemented for board evaluation
int alphabeta(int depth, Board& board, int alpha, int beta);
int rootAlphabeta(int maxDepth, Board board, int alpha, int beta, Move& bestMove);


/*                                   GAME CYCLE                               */
bool checkGameEnd(const Board& board);
bool checkEndgame(const Board& board);


/*                                   RECURSION                                */
u64 divide(int depth, int maxDepth, Board& board, bool showOutput);
u64 divide2(int depth, int maxDepth, Board& board, bool showOutput);
// Makes the given move and changes turn
int makeMove(Board &board, Move& move);
// Undos the given move and changes turn
void undoMove(Board &board, Move& move, int terminalValue);


/*                                  MISC                                      */
// Helper function that updates castling array inside board based on given move
// TODO: Check if this can be integrated inside makeMove
void castlingUpdate(Board& board, const Move& move);
// Checks if the board is at the end state: returns -1 if false, return board value otherwise
int isTerminalNode(Board& board);
void printMenu();
void printDebugMenu();