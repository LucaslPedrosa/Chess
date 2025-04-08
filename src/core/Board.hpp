// Board.h
#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>


// Board representation using 4 uint64_t (64 squares, 4 bits per square)
// Each square can hold a piece type (0-12) or be empty (0)
// The board is represented as follows:

// 56 57 58 59 60 61 62 63
// 48 49 50 51 52 53 54 55
// 40 41 42 43 44 45 46 47
// 32 33 34 35 36 37 38 39
// 24 25 26 27 28 29 30 31
// 16 17 18 19 20 21 22 23
//  8  9 10 11 12 13 14 15
//  0  1  2  3  4  5  6  7

class Board
{
public:
  // Board represented as 4 uint64_t => 64 squares, 4 bits per square
  uint64_t board[4];

  // Each piece is represented by a number from 0 to 12, where 0 is empty
  // and 1-12 represent different pieces (e.g., 1 for white pawn, 2 for black pawn, etc.)
  // The pieces are represented as follows:
  enum class Piece : uint8_t
  {
    EMPTY = 0,
    WHITE_PAWN = 1,
    BLACK_PAWN = 2,
    WHITE_KNIGHT = 3,
    BLACK_KNIGHT = 4,
    WHITE_BISHOP = 5,
    BLACK_BISHOP = 6,
    WHITE_ROOK = 7,
    BLACK_ROOK = 8,
    WHITE_QUEEN = 9,  
    BLACK_QUEEN = 10,
    WHITE_KING = 11,
    BLACK_KING = 12
  };

  Board();

  void initialize();
  Piece getPieceAt(int square) const;
  void setPieceAt(int square, Piece piece);
  void printBoard() const;
};

// Helper functions to convert between square numbers and algebraic notation
namespace BoardHelper
{
  std::string squareToString(int square);
  int stringToSquare(const std::string &squareStr);
  std::string pieceToString(Board::Piece piece);
}

#endif // BOARD_H