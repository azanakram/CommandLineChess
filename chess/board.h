#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>
#include <string>
#include <memory>

#include "piece.h"
#include "empty.h"
#include "knight.h"
#include "pawn.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"

#include "boarddisplay.h"

class BoardDisplay;

class Piece;


class Board {
  std::vector<std::vector<std::shared_ptr<Piece>>> theBoard;  // The actual board.
  std::shared_ptr<BoardDisplay> bd = nullptr; // The board display.
  std::pair<int, int> whiteKing = std::pair<int,int>(-1,-1); // Stores the position of the White King
  std::pair<int, int> blackKing = std::pair<int,int>(-1,-1); // Stores the position of the Black King
  int boardRowNum = 8;
  int boardColNum = 8;
  bool hints = false;
 public:
  Board();
  
  std::shared_ptr<Piece> getPiece(std::pair<int,int> coord); // returns a pointer to a piece on the board
  bool spaceOccupied(std::pair<int, int> coord); // checks to see if a square on the board is occupied by a non-empty piece
  bool isCheck(char colour); // checks to see if the king of the specified colour is in Check
  bool isStalemate(char colour); // checks to see if the game is currently in a stalemate
  bool isCheckmate(char colour); // checks to see if the opposing king is in checkmate
  void move(std::pair<int,int> startCoord, std::pair<int,int> endCoord); // attempts to move piece at startCoord to endCoord
  std::string coordToBoard(int row, int col); // converts the number coordinates to board coordinates
  void promotePawn(std::pair<int, int> coord, char piece); // promotes a pawn to a new piece once it reaches the opposing last row of the board
  void place(std::pair<int,int> coordOld, std::pair<int,int> coordNew, char colour, char piece); // places a piece on the board specified by coord, of the indicated colour
  void remove(std::pair<int, int> coord); // removes the piece on the board that is specified by row and col
  bool validBoard(); // checks to see if the board is valid, that is exactly one king of each colour, no pawns on the first or last row, and neither king is in check
  std::vector<std::pair<int,int>> findMoves(std::pair<int,int> coord, char colour, char piece); // returns a vector of all possible coordinates a piece can move to
  void moveStraight(std::pair<int,int> coord, char colour, char piece, std::vector<std::pair<int,int>> &moves); // adds all the valid moves in a diagonal direction
  void moveDiag(std::pair<int,int> coord, char colour, char piece, std::vector<std::pair<int,int>> &moves); // adds all the valid moves in a diagonal direction
  void init(); // sets up the 8x8 chess board
  void clear(); // clears the board, and fills it with empty pieces
  bool inBound(std::pair<int,int> coord); // checks if coord is within the bounds of the board
  bool addMove(std::pair<int,int> oldCoord, std::pair<int,int> newCoord, char colour, char piece); // returns a boolean value if the move is legal
  void setBoardPtr(std::pair<int,int> coord, std::shared_ptr<Piece> pce); // used for computer.cc to generate moves
  void toggleHints(); // toggles the hints variable
  bool isHintsOn();  // turns the boolean value of hints
  void getHint(std::pair<int,int> coord); // prints out the possible moves of a piece
  bool tryCastling(char colour, std::string direction); // attempts to perform castling on the specified King and direction


  friend std::ostream &operator<<(std::ostream &out, const Board &board);
};

#endif
